#include <stdio.h>

#include <event.h>
#include <evhttp.h>

#include <mysql.h>

#include "httphandler.h"
#include "server.h"

void db_query(MYSQL* conn, struct evbuffer* buffer) {
    if (mysql_query(conn, "SELECT id, value FROM simple WHERE 1")) {
        evbuffer_add_printf(buffer, "%s\n", mysql_error(conn));
        return;
    } else {
        MYSQL_RES* res;
        MYSQL_ROW row;
        
        res = mysql_use_result(conn);
        while ((row = mysql_fetch_row(res)) != NULL) {
            evbuffer_add_printf(buffer, "%s\n", row[0]);
        }
        fprintf(stdout, "Successfully handle request!\n");
        return;
    }
}

MYSQL* db_connect(char* username, char* password, char* db_name) { 
    // Connect to default localhost mysql-server, on error return NULL

    const char* server = "localhost";
    MYSQL* conn;

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, server, username, password, db_name, 0, NULL, 0))
        return conn;
    else
        return NULL;
}

void generic_request_handler(struct evhttp_request *req, void *arg)
{
    struct evbuffer *returnbuffer = evbuffer_new();
    MYSQL* conn;

    conn = db_connect(env.db_username, env.db_password, env.db_name);
    if (conn) {
        db_query(conn, returnbuffer);
        mysql_close(conn);
    } else {
        // DB connection failed
        evbuffer_add_printf(returnbuffer, "Mysql DB connection error!");
    }
    evhttp_send_reply(req, HTTP_OK, "Client", returnbuffer);
    evbuffer_free(returnbuffer);
    return;
}
