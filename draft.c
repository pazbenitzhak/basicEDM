#include "hiredis.h" /* TODO: put all files in the same folders, fork? */
#include <unistd.h> /* for execvp */
#include <stdlib.h>
#include <stdio.h>

#define true 1

static int isInitialized; /* 1 iff a server has already been initialized for this app */


/* General note: for now all exit funcs are temporary. The true handling there
would be distinguished later */


/* init function - for setting up a server */
/* need to set up a server at initialization 
define the server's size, if we want replicas etc
need to choose port and use localhost address 127.0.0.1*/
void init() { /* for now it's without args and a void return value */
    FILE* configFile;
    char* filepath;
    int isExecErr;
    /* open a config file, inside it write all wanted lines. file needs to end with .conf */
    configFile = fopen("serverCon.config","w"); /* open file to write all configurations */
    /* TODO: is opening a file like this OK? YES! I've checked */
    if (configFile==NULL) { /* that's how I chose to handle errors in fopen */
        printf("Error in opening new file\n");
        exit(1);
    }
    /* TODO; decide what the right filepath for the config file is */
    /*#from config file: Note that in order to read the configuration file, Redis must be
# started with the file path as first argument:
#
# ./redis-server /path/to/redis.conf*/
    if ((isExecErr=execvp("redis-server",))==-1) {/* an error has occured with execvp */
        printf("Error in initiating Redis server\n");
        exit(1);
    }
    /* TODO: handle execvp errors */
}

/* connect to the server with built-in functions */


/* set, get etc... with built-in functions */

/* get function */

char* getValue(char* key, redisContext* redisContext) {
    char* value;
    value = redisCommand(context, "GET %s", key);
    /* if value is error - handle */
    /* if value is not error - return */
    return value;

}

int main(int argc, char** argv) {
    redisContext* context;
    int port;
    int isDone;
    /* initiate server  - if needed. maybe distinguish if needed from user's input?*/
    if (!isInitialized) { /* need to initialize a new server */
        init();
        isInitialized = 1; /* as we've just initialized the new server */    
    }
    /* TODO: from what I understand, once initialized it might still need to be called again
    thus we should execute the command again here without config and with port number only */
    /* end of initiating server */
    /* anyway, now we've got our server initialized and are ready to move forward */
    /* now we wish to create a connection */
    /* need to decide port number */
    context = redisConnect("127.0.0.1",port);
    /* localhost is used since it's phase I */
    if (context == NULL || context->err) { /* handle unsuccessful connection, taken from github C client */
        if (context) {
            printf("Error: %s\n",context->errstr);
            /* handle error */
            /* options: run function again, abort and exit program */
        }
        else {
            printf("Can't allocate Redis context\n"); /* TODO: decide what should be written here*/
        }
    }
    /* my idea: initiate a while loop for any commands wanted from app */
    /* finish while loop when given input from user */
    while(true) {
        

        if(isDone) {
            redisFree(context);
            break; /*and thus end run of program, until next time */
            /* CHECK how we want to refer to the program - whether it's a program
            executed that keeps running or a program that stops and starts each time */
        }
    }
}