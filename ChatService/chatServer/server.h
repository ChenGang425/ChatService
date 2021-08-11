#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")
#include <windows.h>
#include <list>

#include "Comment.h"
#include "DataBase.h"
using namespace std;


void communicat(int idx);



SOCKET cSocket[1024];

list<SOCKET> clientCount;
list<SOCKET> oneZoneClient;
list<SOCKET> twoZoneClient;
