#include "Backend.hpp"
#include "Parser.hpp"

Backend::Backend()
	: server(new HTTPServer())
{
}

Backend::~Backend()
{
}

int Backend::run()
{
	std::string json = "{ \"jsonrpc\": \"2.0\", \"method\" : \"CreateBuffer\", \"params\" : [\"test\"], \"id\" : 1 }";
	Parser::run (json, [this](Parser *parser) {
		Command *cmd = createCommand(parser->result.method);
		cmd->validate(parser->result.params);
		cmd->execute(this);
	});

	//server->run(8000);
	return uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}

Command* Backend::createCommand(const std::string &name)
{
	auto it = map.find(name);

	if (it == map.end())
		return nullptr;

	return it->second();
}

int main()
{
	Backend backend;
	
	return backend.run();
}