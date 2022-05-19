
#ifndef MAIN
#define MAIN

#include "Stdafx.h"

#include "Server.h"
#include "Database.h"
#include "FileIOSystem.h"

Database* Database::instance = nullptr;
IOSystem* IOSystem::instance = nullptr;

int main(int argc, char* argv[])
{
	boost::asio::io_context io_context;

	Server server(io_context);

	server.Init(MAX_SESSION_COUNT);

	server.Start();

	io_context.run();

	cout << "Netword is shutdown" << endl;

	getchar();

	return 0;
}

#endif