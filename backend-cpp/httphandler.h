#ifndef HTTP_HANDLER
#define HTTP_HANDLER

#include <event.h>
#include <evhttp.h>

#include <mysql.h>

void generic_request_handler(struct evhttp_request *req, void *arg);

void db_query(MYSQL* conn, struct evbuffer* buffer);

// Connect to default localhost mysql-server, on error return NULL
MYSQL* db_connect(char* username, char* password, char* db_name);

#endif
