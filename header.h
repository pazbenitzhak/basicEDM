#include "hiredis/hiredis.h"
#include <unistd.h> /* for execvp */
#include <stdlib.h>
#include <stdio.h>

redisReply* getValue(char* key, redisContext* redisContext);
redisContext* abcd(char* IP, int port);

void flipper() {
    printf("hello world\n");
}
