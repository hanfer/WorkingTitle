#pragma once

#include <functional>

#include "HTTPServer.hpp"
#include "Command.hpp"

class Backend
{
public:
	Backend();
	~Backend();

	int run();

private:
    HTTPServer* server;
};