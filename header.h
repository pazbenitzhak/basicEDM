#include "hiredis/hiredis.h"
#include <unistd.h> /* for execvp */
#include <stdlib.h>
#include <stdio.h>

char* getValue(char* key, redisContext* redisContext);
redisContext* connectToServer(char* IP, int port);
