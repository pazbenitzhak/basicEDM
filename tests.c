#include "draft.c"
#include "hiredis.h"

int main(int argc, char** argv) {
    int port;
    redisContext* context;
    port = 600;
    context = connectToServer("127.0.0.1",port); /* connect to right port */
    if (context) { /* context = NULL: exit the program */
        exit(1); /* exit with error */
    }
    getValue("a",context);
}