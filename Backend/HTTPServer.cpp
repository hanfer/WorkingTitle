#include "HTTPServer.hpp"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string>


HTTPServer::HTTPServer()
	: loop(uv_default_loop())
{
	
}

HTTPServer::~HTTPServer()
{
}

int HTTPServer::run(const int port)
{
	parser_settings.on_url = Client::http_url_cb;
	parser_settings.on_body = Client::http_body_cb;
	parser_settings.on_header_field = Client::http_header_field_cb;
	parser_settings.on_header_value = Client::http_header_value_cb;
	parser_settings.on_headers_complete = Client::http_headers_complete_cb;
	parser_settings.on_message_begin = Client::http_message_begin_cb;
	parser_settings.on_message_complete = Client::http_message_complete_cb;

	uv_tcp_init(loop, &server);

	server.data = this;

	
	uv_ip4_addr("0.0.0.0", port, &addr);

	uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);

	int r = uv_listen((uv_stream_t*)&server, DEFAULT_BACKLOG, onConnection);
	if (r) {
		fprintf(stderr, "Listen error %s\n", uv_strerror(r));
	}

	return 1;
}

void HTTPServer::onConnection(uv_stream_t* server, int status)
{
	if (status < 0) {
		fprintf(stderr, "New connection error %s\n", uv_strerror(status));
		// error!
		return;
	}
	
	Client *client = new Client();
	HTTPServer *self = (HTTPServer*)server->data;

	uv_tcp_init(self->loop, &client->handle);
	http_parser_init(&client->parser, HTTP_REQUEST);

	client->server = self;
	client->parser.data = new Client::http_request_t(client);
	client->handle.data = client;

	if (uv_accept(server, (uv_stream_t*)&client->handle) == 0) {
		uv_read_start((uv_stream_t*)&client->handle, allocBuffer, Client::onRead);
	}
	else {
		uv_close((uv_handle_t*)&client->handle, NULL);
	}
}

void HTTPServer::allocBuffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf)
{
	buf->base = new char[suggested_size];
	buf->len = suggested_size;
}

void HTTPServer::Client::onRead(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf)
{
	Client* client = (Client*)tcp->data;

	if (nread < 0) {
		if (nread != UV_EOF)
			fprintf(stderr, "Read error %s\n", uv_err_name(nread));
		uv_close((uv_handle_t*)client, NULL);
	}
	else if (nread > 0) {
		size_t parsed = parsed = http_parser_execute(&client->parser, &client->server->parser_settings, buf->base, nread);
	}

	if (buf->base)
		free(buf->base);
}



/**
* Initializes default values, counters.
*/
int HTTPServer::Client::http_message_begin_cb(http_parser* parser) {
	http_request_t* http_request = (http_request_t*)parser->data;

	http_request->header_lines = 0;

	return 0;
}

/**
* Copies url string to http_request->url.
*/
int HTTPServer::Client::http_url_cb(http_parser* parser, const char* chunk, size_t len) {
	http_request_t* http_request = (http_request_t*)parser->data;

	http_request->url = (char *)malloc(len + 1);

	strncpy_s((char*)http_request->url, len + 1, chunk, len);

	return 0;
}

/**
* Copy the header field name to the current header item.
*/
int HTTPServer::Client::http_header_field_cb(http_parser* parser, const char* chunk, size_t len) {
	http_request_t* http_request = (http_request_t*)parser->data;

	http_header_t* header = &http_request->headers[http_request->header_lines];

	header->field = (char *)malloc(len + 1);
	header->field_length = len;

	strncpy_s((char*)header->field, len + 1, chunk, len);

	return 0;
}

/**
* Now copy its assigned value.
*/
int HTTPServer::Client::http_header_value_cb(http_parser* parser, const char* chunk, size_t len) {
	http_request_t* http_request = (http_request_t*)parser->data;

	http_header_t* header = &http_request->headers[http_request->header_lines];

	header->value_length = len;
	header->value = (char *)malloc(len + 1);

	strncpy_s((char*)header->value, len + 1, chunk, len);

	++http_request->header_lines;

	return 0;
}

/**
* Extract the method name.
*/
int HTTPServer::Client::http_headers_complete_cb(http_parser* parser) {
	http_request_t* http_request = (http_request_t*)parser->data;

	const char* method = http_method_str((http_method)parser->method);

	http_request->method = (char *)malloc(sizeof(method));
	strncpy_s(http_request->method, sizeof(method), method, strlen(method));

	return 0;
}

/**
* And copy the body content.
*/
int HTTPServer::Client::http_body_cb(http_parser* parser, const char* chunk, size_t len) {
	http_request_t* http_request = (http_request_t*)parser->data;

	http_request->body = (char*)malloc(len + 1);
	http_request->body = chunk;

	return 0;
}

/**
* Last cb executed by http_parser.
*
* In our case just logs the whole request to stdou.
*/
int HTTPServer::Client::http_message_complete_cb(http_parser* parser) {
	static uv_buf_t resp_buf = {sizeof(RESPONSE), RESPONSE};
	http_request_t* http_request = (http_request_t*)parser->data;

	/* now print the ordered http http_request to console */
	printf("url: %s\n", http_request->url);
	printf("method: %s\n", http_request->method);
	for (int i = 0; i < 5; i++) {
		http_header_t* header = &http_request->headers[i];
		if (header->field)
			printf("Header: %s: %s\n", header->field, header->value);
	}
	if (http_request->body)
		printf("body: %s\n", http_request->body);
	printf("\r\n");

	/* lets send our short http hello world response and close the socket */
	uv_write(&http_request->req, (uv_stream_t *)(&http_request->client->handle), &resp_buf, 1, afterWrite);

	return 0;
}

void HTTPServer::Client::afterWrite(uv_write_t* req, int status)
{
	uv_close((uv_handle_t*)req->handle, onClose);
}

void HTTPServer::Client::onClose(uv_handle_t* handle)
{
	Client* client = (Client*)handle->data;
	free(client);
}