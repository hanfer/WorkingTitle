#pragma once

#include <uv.h>
#include <string>

class Parser
{
public:
	Parser();
	~Parser();

	static void run();

private:
	static void onWork(uv_work_t *req);
	static void onDone(uv_work_t *req, int status);

	void work();

	uv_work_t req;
	std::string json;
};

