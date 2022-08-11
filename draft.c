#include "hiredis/hiredis.h"
#include <unistd.h> /* for execvp */
#include <stdlib.h>
#include <stdio.h>

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
    void* reply;
    reply = redisCommand(redisContext, "GET %s", key);
    if (reply==NULL) { /* an error has occurred */
        /* handle error. error type would be in context->err */
    }
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

int main(int argc, char** argv) {
    redisContext* context;
    char* appInput;
    int port; /* I guess it is given by arguments*/
    int isDone;
    int commandFailed; /* indicates if a command process by the server failed and a new connection set up is needed,initiated as 0*/
    /* We assume the server has already been initialized */
    /* now we wish to create a connection */
    /* need to decide port number */
    context = connectToServer("127.0.0.1",port); /* connect to right port */
    if (context) { /* context = NULL: exit the program */
        exit(1); /* exit with error */
    }
    /* here we're connected */
    /* my idea: initiate a while loop for any commands wanted from app */
    /* finish while loop when given input from user */
    while(true) {
        /* TODO: need to get commands and parse them so we can send it to the right subfunction */
        scanf("%s\n",appInput); /* scan possible command */ 
        if (commandFailed) {
            context = connectToServer("127.0.0.1",port); /* figure if should put inside a function or not */
            if (context) { /* context = NULL: exit the program */
            exit(1); /* exit with error */
            }
        }
        if(isDone) {
            redisFree(context);
            break; /*and thus end run of program, until next time */
            /* CHECK how we want to refer to the program - whether it's a program
            executed that keeps running or a program that stops and starts each time */
        }
    }
}