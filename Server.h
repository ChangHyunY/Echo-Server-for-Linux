#ifndef SERVER_H
#define SERVER_H

#include "Stdafx.h"
#include "Session.h"
#include "Database.h"
#include "FileIOSystem.h"

class Server
{
public:
	Server(boost::asio::io_context& io_context) : m_acceptor(io_context, tcp::endpoint(tcp::v4(), PORT_NUMBER))
	{
		m_bIsAccepting = false;
	}

	~Server()
	{
		for (size_t i = 0; i < m_SessionList.size(); ++i)
		{
			if (m_SessionList[i]->Socket().is_open())
			{
				m_SessionList[i]->Socket().close();
			}

			delete m_SessionList[i];
		}
	}

	void Init(const int nMaxSessionCount)
	{
		for (int i = 0, loop = nMaxSessionCount; i < loop; ++i)
		{
			Session* pSession = new Session(i, (boost::asio::io_context&)m_acceptor.get_executor().context(), this);

			m_SessionList.push_back(pSession);

			m_SessionQueue.push_back(i);
		}
	}

	void Start()
	{
		cout << "server starting....." << endl;

		PostAccept();
	}

	void CloseSession(const int nSessionID)
	{
		cout << "Client connection termination. Session ID: " << nSessionID << endl;

		m_SessionList[nSessionID]->Socket().close();

		m_SessionQueue.push_back(nSessionID);

		if (m_bIsAccepting == false)
		{
			PostAccept();
		}
	}

	void ProcessPacket(const int nSessionID, const char* pData)
	{
		PACKET_HEADER* pheader = (PACKET_HEADER*)pData;

		switch (pheader->nID)
		{
			case REQ_IN:
			{
				PKT_REQ_IN* pPacket = (PKT_REQ_IN*)pData;

				PKT_RES_IN SendPkt;
				SendPkt.Init();
				SendPkt.nIsSuccess = Database::GetInstance()->Check_User(pPacket->uniqueCode, string(pPacket->gameCode).substr(0, 8).c_str());
				if(SendPkt.nIsSuccess)
				{
					m_SessionList[nSessionID]->SetName(Database::GetInstance()->get_last_unique_code().c_str());
					m_SessionList[nSessionID]->SetSEQ(stoi(Database::GetInstance()->get_seq_num(m_SessionList[nSessionID]->GetName())));
					sprintf(SendPkt.uniqueCode, "%s", m_SessionList[nSessionID]->GetName());
					m_SessionList[nSessionID]->PostSend(false, SendPkt.nSize, (char*)&SendPkt);

					PKT_RES_SCORE SendScore;
					SendScore.Init();
					Database::GetInstance()->get_user_score(m_SessionList[nSessionID]->GetSEQ(), SendScore.nScore);
					m_SessionList[nSessionID]->PostSend(false, SendScore.nSize, (char*)&SendScore);

					Database::GetInstance()->update_date(m_SessionList[nSessionID]->GetSEQ());
				}
			}
			break;

			case REQ_SCORE :
			{
				PKT_REQ_SCORE* pPacket = (PKT_REQ_SCORE*)pData;
				
				Database::GetInstance()->update_score(pPacket->nScore, m_SessionList[nSessionID]->GetSEQ());
			}
			break;

			case REQ_ABM_RECODE:
			{
				cout << "Switch ABM" << endl;

				PKT_REQ_ABM_RECODE* pPacket = (PKT_REQ_ABM_RECODE*)pData;

				cout << "Save pPacket Data : " << m_SessionList[nSessionID]->GetName() << endl;

				IOSystem::GetInstance()->StructToString(*pPacket, m_SessionList[nSessionID]->GetName());
			}
			break;

			case REQ_GNG_RECODE:
			{
				PKT_REQ_GNG_RECODE* pPacket = (PKT_REQ_GNG_RECODE*)pData;

				IOSystem::GetInstance()->StructToString(*pPacket, m_SessionList[nSessionID]->GetName());
			}
			break;

			case REQ_AAT_RECODE:
			{
				PKT_REQ_AAT_RECODE* pPacket = (PKT_REQ_AAT_RECODE*)pData;

				IOSystem::GetInstance()->StructToString(*pPacket, m_SessionList[nSessionID]->GetName());
			}
			break;

			case REQ_INFO:
			{
				PKT_REQ_INFO* pPacket = (PKT_REQ_INFO*)pData;

				Database::GetInstance()->update_info(m_SessionList[nSessionID]->GetSEQ(), pPacket->level, pPacket->exp);
			}
			break;

			case REQ_TEST:
			{
				MsgTest* pPacket = (MsgTest*)pData;

				pPacket->Print();
			}
			break;
		}

		return;
	}


private:
	bool PostAccept()
	{
		if (m_SessionQueue.empty())
		{
			m_bIsAccepting = false;
			return false;
		}

		m_bIsAccepting = true;
		int nSessionID = m_SessionQueue.front();

		m_SessionQueue.pop_front();

		m_acceptor.async_accept(m_SessionList[nSessionID]->Socket(),
			boost::bind(&Server::handle_accept, this, m_SessionList[nSessionID],
				boost::asio::placeholders::error)
		);

		return true;
	}

	void handle_accept(Session* pSession, const boost::system::error_code& error)
	{
		if (!error)
		{
			cout << "Client connect success. SessionID: " << pSession->SessionID() << endl;

			pSession->Init();

			pSession->PostReceive();

			pSession->CompletedAccept();

			PostAccept();
		}
		else
		{
			cout << "error No: " << error.value() << " error Message: " << error.message() << endl;
		}
	}

	bool m_bIsAccepting;

	tcp::acceptor m_acceptor;

	vector<Session*> m_SessionList;

	deque<int> m_SessionQueue;

	char query[126];
};

#endif
