#include "hiredis/hiredis.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define true 1

char* getValue(char* key, redisContext* redisContext);
redisContext* connectToServer(char* IP, int port);
