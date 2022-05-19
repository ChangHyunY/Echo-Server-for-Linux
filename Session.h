#ifndef SESSION_H
#define SESSION_H

#include "Stdafx.h"

class Server;

class Session
{
public:
	Session(int nSessionID, boost::asio::io_context& io_context, Server* pServer);

	~Session();

	int SessionID() { return m_nSessionID; }

	tcp::socket& Socket() { return m_Socket; }

	void Init();

	void PostReceive();

	void PostSend(const bool bImmediately, const int nSize, char* pData);

	void SetSEQ(int seqID) { m_nSeqID = seqID; }

	int GetSEQ() { return m_nSeqID; }

	void SetName(const char* pszName) { m_Name = pszName; }

	const char* GetName() { return m_Name.c_str(); }

	void CompletedAccept();

private:
	void handle_write(const boost::system::error_code& error, size_t bytes_transferred);

	void handle_receive(const boost::system::error_code& error, size_t bytes_transferred);


	int m_nSessionID;

	int m_nSeqID;

	tcp::socket m_Socket;

	array<char, MAX_RECEIVE_BUFFER_LEN> m_ReceiveBuffer;

	int m_nPacketBufferMark;

	char m_PacketBuffer[MAX_RECEIVE_BUFFER_LEN * 2];

	deque<char*> m_SendDataQueue;

	string m_Name;

	Server* m_pServer;
};

#endif
