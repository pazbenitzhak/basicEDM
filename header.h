#include "hiredis/hiredis.h"
#include <unistd.h>
#include <stdlib.h>

#define true 1

redisReply* getValue(char* key, redisContext* redisContext);
redisContext* connectToServer(char* IP, int port);