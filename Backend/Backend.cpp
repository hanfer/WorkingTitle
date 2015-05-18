#include "Backend.hpp"

Backend::Backend()
	: server(new HTTPServer())
{
}

Backend::~Backend()
{
}

int Backend::run()
{
	server->run(8000);
	return uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}

int main()
{
	Backend backend;
	
	return backend.run();
}