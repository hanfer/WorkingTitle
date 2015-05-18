#include "Parser.hpp"
#include <jansson.h>


Parser::Parser()
{
}


Parser::~Parser()
{
}

void Parser::run()
{
	Parser *parser = new Parser();
	uv_queue_work(uv_default_loop(), &parser->req, onWork, onDone);
}

void Parser::onWork(uv_work_t* req)
{
	Parser *self = (Parser*)req->data;
	return self->work();
}

void Parser::onDone(uv_work_t* req, int status)
{
	Parser *self = (Parser*)req->data;

	delete self;
}

void Parser::work()
{
	json_error_t error;
	json_t *root = json_loads(json.c_str(), 0, &error);
}