#pragma once

#include "HTTPServer.hpp"
#include "Command.hpp"
#include <unordered_map>

class Backend
{
public:
	typedef Command*(*CommandFunc)();
	typedef std::unordered_map<std::string, CommandFunc> CommandMap;

	Backend();
	~Backend();

	int run();

private:
	Command *createCommand(const std::string &name);

    HTTPServer* server;

	const CommandMap map = CommandMap{
		{ "CreateBuffer", &Command::create<CreateBuffer> }
	};
};