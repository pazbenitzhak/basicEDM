#include "header.h"

int main(int argc, char** argv) {
    int port;
    redisContext* context;
    port = 6400;
    context = abcd("127.0.0.1",port); /* connect to right port */
    if (context) { /* context = NULL: exit the program */
        exit(1); /* exit with error */
    }
    getValue("a",context);
}