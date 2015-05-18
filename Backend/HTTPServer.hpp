#pragma once

#include <uv.h>
#include <http_parser.h>

#define DEFAULT_BACKLOG 128
#define MAX_HTTP_HEADERS 20
#define RESPONSE \
  "HTTP/1.1 200 OK\r\n" \
  "Content-Type: text/html; charset=utf-8\r\n" \
  "Content-Length: 21\r\n" \
  "\r\n" \
  "<h1>hello world</h1>\n"

class HTTPServer
{
public:
	HTTPServer();
	~HTTPServer();

	int run(const int port);

private:
	struct Client
	{
		typedef struct {
			const char* field;
			const char* value;
			size_t field_length;
			size_t value_length;
		} http_header_t;

		struct http_request_t {

			http_request_t(Client *pClient)
				: client(pClient)
				, body(nullptr)
			{}

			Client *client;
			uv_write_t req;
			http_parser parser;
			char* url;
			char* method;
			int header_lines;
			http_header_t headers[MAX_HTTP_HEADERS];
			const char* body;
		};


		uv_tcp_t handle;
		uv_write_t write_req;
		http_parser parser;
		HTTPServer* server;
		
		static void onRead(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);
		static void afterWrite(uv_write_t* req, int status);
		static void onClose(uv_handle_t* handle);

		static int http_message_begin_cb(http_parser* parser);
		static int http_url_cb(http_parser* parser, const char* chunk, size_t len);
		static int http_header_field_cb(http_parser* parser, const char* chunk, size_t len);
		static int http_header_value_cb(http_parser* parser, const char* chunk, size_t len);
		static int http_headers_complete_cb(http_parser* parser);
		static int http_body_cb(http_parser* parser, const char* chunk, size_t len);
		static int http_message_complete_cb(http_parser* parser);
	};

	static void onConnection(uv_stream_t *server, int status);
	static void allocBuffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);

	uv_loop_t *loop;
	uv_tcp_t server;
	sockaddr_in addr;
	http_parser_settings parser_settings;
};

