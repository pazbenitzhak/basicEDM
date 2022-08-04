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
    char* value;
    value = redisCommand(context, "GET %s", key);
    /* an impoprtant discussion - where do we get the return value from the GET operation?
    Right now I think it's given only on std and therefore should be read from it (some kind of std).
    Therefore here value would stand only for the response reply value! - CHECK */
    /* if value is error - handle */
    /* if value is not error - return */
    return value;

}

int main(int argc, char** argv) {
    redisContext* context;
    int port; /* I guess it is given by arguments*/
    int isDone;
    /* We assume the server has already been initialized */
    /* now we wish to create a connection */
    /* need to decide port number */
    context = redisConnect("127.0.0.1",port); /* connect to right port */
    /* localhost is used since it's phase I */
    if (context == NULL || context->err) { /* handle unsuccessful connection, taken from github C client */
        if (context) {
            printf("Error: %s\n",context->errstr);
            /* TODO: handle error */
            /* options: run function again, abort and exit program */
        }
        else {
            printf("Can't allocate Redis context\n"); /* TODO: decide what should be written here*/
        }
    }
    /* here we're connected */
    /* my idea: initiate a while loop for any commands wanted from app */
    /* finish while loop when given input from user */
    while(true) {
        /* need to get commands and parse them so we can send it to the right subfunction */

        if(isDone) {
            redisFree(context);
            break; /*and thus end run of program, until next time */
            /* CHECK how we want to refer to the program - whether it's a program
            executed that keeps running or a program that stops and starts each time */
        }
    }
}