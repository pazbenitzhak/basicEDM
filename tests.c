#include "header.h"

int main(int argc, char** argv) {
    int port;
    redisContext* context;
    port = 6400;
    printf("In tests\n");
    context = connectToServer("127.0.0.1",port); /* connect to right port */
    printf("after connection\n");
    printf("context error str is: %s\n",context->errstr);
    printf("context err val is: %i\n",context->err);
    printf("context addrlen is: %li\n",context->addrlen);
    if (context==NULL) { /* context = NULL: exit the program */
        printf("if confirmed\n");
        exit(1); /* exit with error */
    }
    printf("after if condition\n");
    getValue("a",context);
}