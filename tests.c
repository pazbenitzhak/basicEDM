#include "header.h"

int main(int argc, char** argv) {
    int port;
    redisContext* context;
    port = 6400;
    printf("In tests\n");
    context = connectToServer("127.0.0.1",port); /* connect to right port */
    printf("after connection\n");
    if (context) { /* context = NULL: exit the program */
        printf("if confirmed\n");
        exit(1); /* exit with error */
    }
    printf("after if condition\n");
    getValue("a",context);
}