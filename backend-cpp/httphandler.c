#include "httphandler.h"

#include <event.h>
#include <evhttp.h>


void generic_request_handler(struct evhttp_request *req, void *arg)
{
    struct evbuffer *returnbuffer = evbuffer_new();

    evbuffer_add_printf(returnbuffer, "Thanks for the request!");
    evhttp_send_reply(req, HTTP_OK, "Client", returnbuffer);
    evbuffer_free(returnbuffer);
    return;
}
