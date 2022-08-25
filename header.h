#include "hiredis/hiredis.h"
#include <unistd.h> /* for execvp */
#include <stdlib.h>

#define true 1

redisReply* getValue(char* key, redisContext* redisContext);
redisContext* connectToServer(char* IP, int port);

void flipper() {
    printf("hello world\n");
}

redisContext* connectToServer(char* IP, int port) {
    redisContext* context;
    context = redisConnect(IP, port);
    /* localhost is used since it's phase I */
    if (context ==  NULL || context->err) { /* handle unsuccessful connection, taken from github C client */
        if (context) {
            printf("Error: %s\n",context->errstr);
            /* TODO: handle error */
            /* options: run function again, abort and exit program */
            return NULL;
        }
        else {
            printf("Can't allocate Redis context\n"); /* TODO: decide what should be written here*/
            return NULL;
        }
    }
    return context;
}