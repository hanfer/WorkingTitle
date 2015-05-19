#include "Parser.hpp"
#include <jansson.h>


Parser::Parser()
{
}


Parser::~Parser()
{
}

void Parser::run(std::string json, CallbackType pCb)
{
	Parser *parser = new Parser();

	parser->json = json;
	parser->cb = pCb;

	parser->req.data = parser;

	uv_queue_work(uv_default_loop(), &parser->req, onWork, onDone);
}

void Parser::onWork(uv_work_t* req)
{
	Parser *self = static_cast<Parser*>(req->data);
	return self->work();
}

void Parser::onDone(uv_work_t* req, int status)
{
	Parser *self = static_cast<Parser*>(req->data);
	return self->cb(self);
}

void Parser::work()
{
	json_error_t error;
	json_t *root = json_loads(json.c_str(), 0, &error);

	//TODO: error checking everywhere ;D

	auto getParam = [](json_t *param) -> Any
	{
		switch (static_cast<json_type>(json_typeof(param)))
		{
		case JSON_STRING: 
			return Any(std::string(json_string_value(param)));
		case JSON_INTEGER: 
			return Any(int(json_integer_value(param)));
		default: 
			return Any();
		}
	};

	json_t *jsonrpc = json_object_get(root, "jsonrpc");
	json_t *method = json_object_get(root, "method");
	json_t *params = json_object_get(root, "params");
	json_t *id = json_object_get(root, "id");

	result.jsonrpc = json_string_value(jsonrpc);
	result.method = json_string_value(method);

	for (u32 i = 0; i < json_array_size(params); i++)
		result.params.add(getParam(json_array_get(params, i)));

	result.id = json_integer_value(id);
}