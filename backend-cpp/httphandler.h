#ifndef HTTP_HANDLER
#define HTTP_HANDLER

#include <event.h>
#include <evhttp.h>

void generic_request_handler(struct evhttp_request *req, void *arg);

#endif
