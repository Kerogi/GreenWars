#include "s3e.h"
#include "s3eThread.h"
#include "ServerPeer.h"
#include <unistd.h>
#include <vector>
#include <game.h>
#include <stdio.h>

#define SOCKET_BUFFER_SIZE 512
#define GW_PORT 7777//47927

using namespace std;

//----------SERVER implementation-----------
