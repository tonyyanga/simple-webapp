#ifndef SERVER
#define SERVER

#include <sys/types.h>

struct arguments {
    char* db_username;
    char* db_password;
    char* db_name;
} env; // shared environmental variables (by CLI arguments)

#endif
