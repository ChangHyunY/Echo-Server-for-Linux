
#ifndef IOSYSTEM
#define IOSYSTEM

#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include <unistd.h>		// use access() function

//#include "Protocol.h"
#include "Stdafx.h"


using namespace std;

class IOSystem
{
private:
	IOSystem();

	static IOSystem *instance;

public:
	~IOSystem();

	static IOSystem* GetInstance();

	void Output_File(string folder_name, string fileDesc);

	void StructToString(PKT_REQ_ABM_RECODE datas, string name);

	void StructToString(PKT_REQ_GNG_RECODE datas, string name);

	void StructToString(PKT_REQ_AAT_RECODE datas, string name);

private:
	bool Make_Directory(string folder_name);

	string access_file(string folder_name, int index);

	const string fixed_path = "/home/ubuntu/projects/EchoServer/UserDataSet/";

	string all_path;
};

#endif