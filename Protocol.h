
const unsigned short PORT_NUMBER = 9000;

const int MAX_RECEIVE_BUFFER_LEN = 4096;

const int MAX_NAME_LEN = 16;

const int MAX_MESSAGE_LEN = 2048;

const int MAX_ABM_RECODE = 80;

const int MAX_GNG_RECODE = 81;

const int MAX_AAT_RECODE = 50;


struct PACKET_HEADER
{
	short nID;
	short nSize;
};



//  PACKET
const short RES_CONNECT = 0;

const short REQ_IN = 1;

const short RES_IN = 2;

const short REQ_SCORE = 7;

const short RES_SCORE = 8;

const short REQ_ABM_RECODE = 9;

const short REQ_GNG_RECODE = 10;

const short REQ_AAT_RECODE = 11;

const short REQ_INFO = 12;


const short REQ_TEST = 99;


struct PKT_RES_CONNECT : public PACKET_HEADER
{
	void Init()
	{
		nID = RES_CONNECT;
		nSize = sizeof(PKT_RES_CONNECT);
		bIsConnect = false;
	}

	bool bIsConnect;
};


struct PKT_REQ_IN : public PACKET_HEADER
{
	void Init()
	{
		nID = REQ_IN;
		nSize = sizeof(PKT_REQ_IN);
		memset(gameCode, 0, MAX_NAME_LEN);
		memset(uniqueCode, 0, MAX_NAME_LEN);
	}

	char gameCode[MAX_NAME_LEN];	// 최초 게임 입장 시 제출하는 코드
	char uniqueCode[MAX_NAME_LEN];	// 유저의 유니크 코드
};

struct PKT_RES_IN : public PACKET_HEADER
{
	void Init()
	{
		nID = RES_IN;
		nSize = sizeof(PKT_RES_IN);
		nIsSuccess = 0;
		memset(uniqueCode, 0, MAX_NAME_LEN);
	}

	short nIsSuccess;
	char uniqueCode[MAX_NAME_LEN];
};

struct PKT_REQ_SCORE : public PACKET_HEADER
{
	void Init()
	{
		nID = REQ_SCORE;
		nSize = sizeof(PKT_REQ_SCORE);
		memset(nScore, 0, sizeof(nScore));
	}

	int nScore[9];
};

struct PKT_RES_SCORE : public PACKET_HEADER
{
	void Init()
	{
		nID = RES_SCORE;
		nSize = sizeof(PKT_RES_SCORE);
		memset(nScore, 0, sizeof(nScore));
	}

	int nScore[9];
};

struct PKT_REQ_ABM_RECODE : public PACKET_HEADER
{
	void Init()
	{
		nID = REQ_ABM_RECODE;
		nSize = sizeof(PKT_REQ_ABM_RECODE);
		arraySize = 0;
		memset(trials, 0, sizeof(trials));
		memset(cigaretteIsLeft, 0, sizeof(cigaretteIsLeft));
		memset(xTouchPos, 0, sizeof(xTouchPos));
		memset(yTouchPos, 0, sizeof(yTouchPos));
		memset(reactionTime, 0, sizeof(reactionTime));
	}

public:
	int arraySize;
	int trials[MAX_ABM_RECODE];
	int cigaretteIsLeft[MAX_ABM_RECODE];
	float xTouchPos[MAX_ABM_RECODE];
	float yTouchPos[MAX_ABM_RECODE];
	float reactionTime[MAX_ABM_RECODE * 3];
};

struct PKT_REQ_GNG_RECODE : public PACKET_HEADER
{
	void Init()
	{
		nID = REQ_ABM_RECODE;
		nSize = sizeof(PKT_REQ_GNG_RECODE);
		arraySize = 0;
		memset(trials, 0, sizeof(trials));
		memset(isCigarette, 0, sizeof(isCigarette));
		memset(isTouch, 0, sizeof(isTouch));
		memset(trapClear, 0, sizeof(trapClear));
		memset(reactionTime, 0, sizeof(reactionTime));
	}

public:
	int arraySize;
	int trials[MAX_GNG_RECODE];
	int isCigarette[MAX_GNG_RECODE];
	int isTouch[MAX_GNG_RECODE];
	int trapClear[MAX_GNG_RECODE];
	float reactionTime[MAX_GNG_RECODE];
};

struct PKT_REQ_AAT_RECODE : public PACKET_HEADER
{
	void Init()
	{
		nID = REQ_ABM_RECODE;
		nSize = sizeof(PKT_REQ_AAT_RECODE);
		arraySize = 0;
		memset(trials, 0, sizeof(trials));
		memset(isCigarette, 0, sizeof(isCigarette));
		memset(outlineType, 0, sizeof(outlineType));
		memset(userBehavior, 0, sizeof(userBehavior));
		memset(reactionTime, 0, sizeof(reactionTime));
	}

public:
	int arraySize;
	int trials[MAX_AAT_RECODE];
	int isCigarette[MAX_AAT_RECODE];
	int outlineType[MAX_AAT_RECODE];
	int userBehavior[MAX_AAT_RECODE];
	float reactionTime[MAX_AAT_RECODE];
};

struct PKT_REQ_INFO : public PACKET_HEADER
{
	void Init()
	{
		nID = REQ_INFO;
		nSize = sizeof(PKT_REQ_INFO);
		level = 0;
		exp = 0;
	}

public:
	int level;
	int exp;
};

struct MsgTest : public PACKET_HEADER
{
	void Init()
	{
		nID = REQ_TEST;
		nSize = sizeof(MsgTest);
		memset(f, 0, sizeof(f));
		memset(n, 0, sizeof(n));
	}

	void Print()
	{
		for(int i = 0; i < sizeof(f) / sizeof(float); ++i)
		{
			cout << f[i] << ", ";
		}

		for(int i = 0; i < sizeof(n) / sizeof(short); ++i)
		{
			cout << n[i] << ", ";
		}
		cout << endl;

		
		cout << endl;		
	}

public:
	float f[4];
	short n[4];
};