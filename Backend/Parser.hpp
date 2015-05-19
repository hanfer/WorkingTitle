#pragma once

#include <uv.h>
#include <string>
#include <functional>

#include "Any.hpp"
#include "Global.hpp"

class Parser
{
public:
	struct Result
	{
		std::string jsonrpc;
		std::string method;
		AnyList params;
		u64 id;
	};

	typedef std::function<void(Parser*)> CallbackType;

	Parser();
	~Parser();

	static void run(std::string json, CallbackType pCb);

	CallbackType cb;
	Result result;

private:
	static void onWork(uv_work_t *req);
	static void onDone(uv_work_t *req, int status);

	void work();

	uv_work_t req;
	std::string json;
};

