
#include "FileIOSystem.h"

IOSystem::IOSystem()
{
	instance = this;
}

IOSystem::~IOSystem()
{

}

IOSystem* IOSystem::GetInstance()
{
	if(IOSystem::instance == nullptr)
	{
		IOSystem::instance = new IOSystem();
	}

	return IOSystem::instance;
}

void IOSystem::Output_File(string folder_name, string fileDesc)
{
	cout << "Output file function" << endl;

	if(Make_Directory(folder_name))
	{
		ofstream fout(access_file(folder_name, 0));

		fout << fileDesc;

		fout.close();
	}
	else
	{
		cout << "Failed output file" << endl;
	}
}

bool IOSystem::Make_Directory(string folder_name)
{
	if(!(mkdir((new string(fixed_path + folder_name))->c_str(), 0766)))
	{
		cout << "create directory successed" << endl;

		return true;
	}
	else
	{
		cout << "create error. error : " << strerror(errno) << endl;

		if(errno == EEXIST) return true;
		else return false;
	}
}

// return num of max file count
// folder_name is Del-N
// index is (data)N
string IOSystem::access_file(string folder_name, int index = 0)
{
	// /home/ubuntu/projects/EchoServer/UserDataSet/Del-N/dataN.json
	all_path = fixed_path + folder_name + "/Data-" + to_string(index) + ".json";

    if(access(all_path.c_str(), F_OK) != -1)
    {
        return access_file(folder_name, ++index);
    }
    else
    {
        cout << all_path << ", " << index << endl;
        return all_path;
    }
}

void IOSystem::StructToString(PKT_REQ_ABM_RECODE datas, string name)
{
	cout << "In Struct To String" << endl;

	stringstream sstream;

	sstream << "{\"Type\":\"ABM\",";
	sstream << "\"Trials\":[";
	for(int i = 0, loop = datas.arraySize; i < loop; ++i)
	{
		sstream << "\"" << datas.trials[i] << "\"";
		if(i != loop - 1) sstream << ",";
	}

	sstream << "],\"Cigarette Is Left\":[";
	for (int i = 0, loop = datas.arraySize; i < loop; ++i)
	{
		sstream << "\"" << datas.cigaretteIsLeft[i] << "\"";
		if (i != loop - 1) sstream << ",";
	}

	sstream << "],\"First Touch\":[";
	for (int i = 0, loop = datas.arraySize; i < loop; ++i)
	{
		sstream << "{\"x\":" << datas.xTouchPos[i]
				<< ",\"y\":" << datas.yTouchPos[i]
				<< "}";
		if (i != loop - 1) sstream << ",";
	}

	sstream << "],\"Reaction Times\":[";
	for (int i = 0, loop = datas.arraySize * 3; i < loop; i += 3)
	{
		sstream << "{\"f\":" << datas.reactionTime[i]
				<< ",\"s\":" << datas.reactionTime[i + 1]
				<< ",\"t\":" << datas.reactionTime[i + 2]
				<< "}";
		if (i != loop - 3) sstream << ",";
	}

	sstream << "]}\0";
	cout << sstream.str() << endl;
	Output_File(name, sstream.str());
}

void IOSystem::StructToString(PKT_REQ_GNG_RECODE datas, string name)
{
	stringstream sstream;

	sstream << "{\"Type\":\"GNG\",";
	sstream << "\"Trials\":[";
	for(int i = 0, loop = datas.arraySize; i < loop; ++i)
	{
		sstream << "\"" << datas.trials[i] << "\"";
		if(i != loop - 1) sstream << ",";
	}

	sstream << "],\"Is Cigarette\":[";
	for (int i = 0, loop = datas.arraySize; i < loop; ++i)
	{
		sstream << "\"" << datas.isCigarette[i] << "\"";
		if (i != loop - 1) sstream << ",";
	}

	sstream << "],\"Is Touch\":[";
	for (int i = 0, loop = datas.arraySize; i < loop; ++i)
	{
		sstream << "\"" << datas.isTouch[i] << "\"";
		if (i != loop - 1) sstream << ",";
	}
	
	sstream << "],\"Trap Clear\":[";
	for (int i = 0, loop = datas.arraySize; i < loop; ++i)
	{
		sstream << "\"" << datas.trapClear[i] << "\"";
		if (i != loop - 1) sstream << ",";
	}
	
	sstream << "],\"Reaction Time\":[";
	for (int i = 0, loop = datas.arraySize; i < loop; ++i)
	{
		sstream << "\"" << datas.reactionTime[i] << "\"";
		if (i != loop - 1) sstream << ",";
	}

	sstream << "]}\0";
	cout << sstream.str() << endl;
	Output_File(name, sstream.str());
}

void IOSystem::StructToString(PKT_REQ_AAT_RECODE datas, string name)
{
	stringstream sstream;

	sstream << "{\"Type\":\"AAT\",";
	sstream << "\"Trials\":[";
	for(int i = 0, loop = datas.arraySize; i < loop; ++i)
	{
		sstream << "\"" << datas.trials[i] << "\"";
		if(i != loop - 1) sstream << ",";
	}

	sstream << "],\"Is Cigarette\":[";
	for (int i = 0, loop = datas.arraySize; i < loop; ++i)
	{
		sstream << "\"" << datas.isCigarette[i] << "\"";
		if (i != loop - 1) sstream << ",";
	}

	sstream << "],\"Outline Type\":[";
	for (int i = 0, loop = datas.arraySize; i < loop; ++i)
	{
		sstream << "\"" << datas.outlineType[i] << "\"";
		if (i != loop - 1) sstream << ",";
	}

	sstream << "],\"UserBehavior\":[";
	for (int i = 0, loop = datas.arraySize; i < loop; ++i)
	{
		sstream << "\"" << datas.userBehavior[i] << "\"";
		if (i != loop - 1) sstream << ",";
	}

	sstream << "],\"ReactionTime\":[";
	for (int i = 0, loop = datas.arraySize; i < loop; ++i)
	{
		sstream << "\"" << datas.reactionTime[i] << "\"";
		if (i != loop - 1) sstream << ",";
	}

	sstream << "]}\0";
	cout << sstream.str() << endl;
	Output_File(name, sstream.str());
}