#include "hiredis/hiredis.h"
#include <unistd.h> /* for execvp */
#include <stdlib.h>

#define true 1

redisReply* getValue(char* key, redisContext* redisContext);

void flipper() {
    printf("hello world\n");
}