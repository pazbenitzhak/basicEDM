#include "hiredis/hiredis.h"
#include <unistd.h> /* for execvp */
#include <stdlib.h>
#include <stdio.h>
#include "header.h"

#define true 1

static int isInitialized; /* 1 iff a server has already been initialized for this app */


/* General note: for now all exit funcs are temporary. The true handling there
would be distinguished later */

/* No need to set up a server, as this task would be performed by SpotOS*/
/* Therefore, we assume a server was initiated by SpotOs and its details given to us */




/* connect to the server with built-in functions */


/* set, get etc... with built-in functions */

/* get function */

char* getValue(char* key, redisContext* redisContext) {
    redisReply reply;
    reply = redisCommand(redisContext, "GET %s", key);
    if (reply==NULL) { /* an error has occurred */
        /* handle error. error type would be in context->err */
        printf("Error!\n");
    }
    if (reply==REDIS_REPLY_STATUS) {
        printf("status string: %s\n", reply->str);
        printf("status len: %i\n", reply->len);
    }
    printf("status string: %s\n", reply->str);
    printf("status len: %i\n",reply->len);
    /* an important discussion - where do we get the return value from the GET operation?
    Right now I think it's given only on std and therefore should be read from it (some kind of std).
    Therefore here value would stand only for the response reply value! - CHECK */
    /* if value is error - handle 
    from Redis documentation: "A client implementation may return different types of exceptions for different errors or provide a generic way to trap errors by directly providing the error name to the caller as a string."
    */
    /* if value is not error - return */
    REDIS_REPLY_NIL;
    return reply;

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