#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

#include "HTTPServer.hpp"

int main() {
	HTTPServer* server = new HTTPServer(8000);
	server->run();
	return   uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}