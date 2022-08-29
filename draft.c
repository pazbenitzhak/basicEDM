#include "header.h"
#include <string.h>

static int isInitialized; /* 1 iff a server has already been initialized for this app */


/* General note: for now all exit funcs are temporary. The true handling there
would be distinguished later */

/* No need to set up a server, as this task would be performed by SpotOS*/
/* Therefore, we assume a server was initiated by SpotOs and its details given to us */

/* functions */
char* getValue(char* key, redisContext* redisContext);
redisContext* connectToServer(char* IP, int port);


/* connect to the server with built-in functions */


/* set, get etc... with built-in functions */

/* get function */

/* here's the description*/
/* we'd probably decide that the key would be the virtual number */ 
char* getValue(char* key, redisContext* redisContext) {
    redisReply* reply;
    size_t len; /* represents reply length */
    int replyType;
    char* value;
    reply = redisCommand(redisContext, "GET %s", key);
    if (reply==NULL) { /* an error has occurred */
        /* handle error. error type would be in context->err */
        printf("Error in getting value: reply is NULL\n");
        exit(1); /* unsuccessful reply */
    }
    /* if we got here than we have a reply->type field */
    replyType = reply->type;
    switch (replyType)
    {
        case REDIS_REPLY_STATUS:
            /* a lot of times seems the same as reply string, so i'll leave it
            to handle over there */
            break;

        case REDIS_REPLY_ERROR:
            printf("error status string: %s\n", reply->str);
            exit(1); /* due to error occurring */
            break;

        case REDIS_REPLY_INTEGER:
            /* don't think it's supposed to happpen, therefore don't handle */
            break;

        case REDIS_REPLY_NIL:
            /* do not change data object, since it's initiated as NULL */
            printf("no data to access \n");
            break;

        case REDIS_REPLY_STRING:
            /* most important case and most useful*/
            len = reply->len;
            value = (char*) malloc(len*sizeof(char)); /* allocate memory for data */
            strcpy(value, reply->str); /* copy val to data, as reply is about to be freed */
            break;

        case REDIS_REPLY_ARRAY:
            /* not supposed to happen and thus won't be handled */
            break;

        case REDIS_REPLY_DOUBLE:
            /* not supposed to happen and thus won't be handled */
            break;

        case REDIS_REPLY_BOOL:
            /* not supposed to happen and thus won't be handled */
            break;

        case REDIS_REPLY_MAP: /* almost the same as array */
            /* not supposed to happen and thus won't be handled */
            break;

        case REDIS_REPLY_SET: /* almost the same as array */
            /* not supposed to happen and thus won't be handled */
            break;

        case REDIS_REPLY_PUSH:
            break; /* for now do nothing */

        /* I left out REDIS_REPLY_ATTR as I think it's irrelevant */

        case REDIS_REPLY_BIGNUM:
            /* not supposed to happen and thus won't be handled */
            break;

        case REDIS_REPLY_VERB:
            /* not supposed to happen and thus won't be handled */
            break;

    }

    /* need to free reply object */
    freeReplyObject(reply);
    /* if value is error - handle 
    from Redis documentation: "A client implementation may return different types of exceptions for different errors or provide a generic way to trap errors by directly providing the error name to the caller as a string."
    */
    /* if value is not error - return */
    return value;

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
    printf("connection successful\n");
    return context;
}