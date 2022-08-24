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

/* functions */

redisContext* connectToServer(char* IP, int port);


/* connect to the server with built-in functions */


/* set, get etc... with built-in functions */

/* get function */

/* here's the description*/
redisReply* getValue(char* key, redisContext* redisContext) {
    redisReply* reply;
    int replyType;
    reply = redisCommand(redisContext, "GET %s", key);
    flipper();
    if (reply==NULL) { /* an error has occurred */
        /* handle error. error type would be in context->err */
        printf("Error!\n");
    }
    /* if we got here than we have a reply->type field */
    replyType = reply->type;
    switch (replyType)
    {
        case REDIS_REPLY_STATUS:
            printf("status string: %s\n", reply->str);
            printf("status len: %li\n", reply->len);
            break;

        case REDIS_REPLY_ERROR:
            printf("error status string: %s\n", reply->str);
            break;

        case REDIS_REPLY_INTEGER:
            printf("the returned integer is: %lld\n",reply->integer);
            break;

        case REDIS_REPLY_NIL:
            printf("no data to access \n");
            break;

        case REDIS_REPLY_STRING:
            printf("reply string: %s\n", reply->str);
            printf("reply string len: %li\n", reply->len);
            break;

        case REDIS_REPLY_ARRAY:
            printf("number of elements in array is %li\n",reply->elements);
            break;

        case REDIS_REPLY_DOUBLE:
            printf("double value (as string) is %s\n",reply->str);
            break;

        case REDIS_REPLY_BOOL:
            printf("boolean value is: %lld",reply->integer);
            break;

        case REDIS_REPLY_MAP: /* almost the same as array */
            printf("number of elements in map is %li\n",reply->elements);
            break;

        case REDIS_REPLY_SET: /* almost the same as array */
            printf("number of elements in set is %li\n",reply->elements);
            break;

        case REDIS_REPLY_PUSH:
            break; /* for now do nothing */

        /* I left out REDIS_REPLY_ATTR as I think it's irrelevant */

        case REDIS_REPLY_BIGNUM:
            printf("big num as string is %s\n",reply->str);
            break;

        case REDIS_REPLY_VERB:
            printf("verbatim string payload is %s\n",reply->str);
            printf("type data is %s\n",reply->vtype);
            break;

    }

    printf("status string: %s\n", reply->str);
    printf("status len: %li\n",reply->len);
    
    /* an important discussion - where do we get the return value from the GET operation?
    Right now I think it's given only on std and therefore should be read from it (some kind of std).
    Therefore here value would stand only for the response reply value! - CHECK */
    /* if value is error - handle 
    from Redis documentation: "A client implementation may return different types of exceptions for different errors or provide a generic way to trap errors by directly providing the error name to the caller as a string."
    */
    /* if value is not error - return */
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