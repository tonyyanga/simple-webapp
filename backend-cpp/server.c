#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <argp.h>

#include <event.h>
#include <evhttp.h>

#include "server.h"
#include "httphandler.h"

const char* args_doc = "A simple web application backend implemented by C";

const struct argp_option options[] = {
    //{"port", 'p', 0, 0, "Port that the server should listen at"},
    //{"addr", 'a', 0, 0, "Address that the server should listen at"},
    {"user", 'u', "USERNAME", 0, "Username of the mysql server"},
    {"pass", 'p', "PASSWORD", 0, "Password of the mysql server account"},
    {"db", 'd', "DB_NAME", 0, "Name of the mysql database to use"},
    {0} // required to end the options array
};


static error_t argp_parser(int key, char *arg, struct argp_state *state);

static error_t argp_parser(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state -> input;
    
    // Need error-handling
    switch (key) {
        case 'u':
            arguments -> db_username = arg;
            break;
        case 'p':
            arguments -> db_password = arg;
            break;
        case 'd':
            arguments -> db_name = arg;
            break;
        
        case ARGP_KEY_ARG: // when receiving non-option arguments
            break;

        case ARGP_KEY_END:
            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    // using static connection information for now
    int http_port = 8000;
    char* http_addr = "127.0.0.1";
    struct evhttp* http_server = NULL; 
    struct argp argp = {options, argp_parser, "", args_doc};

    argp_parse(&argp, argc, argv, 0, 0, &env);
    
    // For debugging only
    //fprintf(stdout, "Input arguments are %s, %s, %s\n", env.db_username, env.db_password, env.db_name);
    //fflush(stdout);

    //libevent for eventloop
    event_init();
    http_server = evhttp_start(http_addr, http_port);
    evhttp_set_gencb(http_server, generic_request_handler, NULL);

    fprintf(stdout, "Server started on port %d\n", http_port);

    //eventloop starts
    event_dispatch();

    return(0);
}
