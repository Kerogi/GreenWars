#include "s3e.h"
#include "s3eThread.h"
#include "ServerPeer.h"
#include <unistd.h>
#include <vector>
#include <game.h>
#include <stdio.h>

#define SOCKET_BUFFER_SIZE 64
#define GW_PORT 47927
#define SOCKET_TIMEOUT 5000

using namespace std;

//----------SERVER implementation-----------


sServer::sServer()
{
}

void sServer::Start()
{
	g_Sock = s3eSocketCreate(S3E_SOCKET_TCP, 0);
	if (g_Sock == NULL)
	{
		// ERROR!!
		return;
	}

	// look up address
	s3eInetAddress addr;
	memset(&addr, 0, sizeof(addr));
	addr.m_Port = s3eInetHtons(GW_PORT);
	addr.m_IPAddress = 0;

	if (s3eSocketBind(g_Sock, &addr, S3E_TRUE) != S3E_RESULT_SUCCESS)
	{
		// ERROR!!
		return;
	}

	if (s3eSocketListen(g_Sock, 10) != S3E_RESULT_SUCCESS)
	{
		// ERROR!!
		return;
	}

	s3eSocket* newSocket = s3eSocketAccept(g_Sock, &addr, AcceptCallback, this);
	if (newSocket)
		CreatePeer(newSocket, &addr);
}

int32 sServer::AcceptCallback(s3eSocket* sock, void* sysData, void* userData)
{
	sServer* serv = (sServer*)userData;

    s3eInetAddress addr;
    s3eSocket* newSocket = s3eSocketAccept(serv->g_Sock, &addr, AcceptCallback, serv);
    if (newSocket)
		serv->CreatePeer(newSocket, &addr);
    return 0;
}

void sServer::CreatePeer(s3eSocket* newSocket, s3eInetAddress* address)
{
	sPeer* peer = new sPeer(this);
	peer->Connect(newSocket, address);
	m_pears.push_back(peer);
	peer->loop_thread = s3eThreadCreate(sPeer::Loop,peer,NULL);
}

void sServer::Stop()
{
	for(int i=0; i<m_pears.size(); i++)
	{
		m_pears[i]->Dissconnect();
		s3eThreadJoin(m_pears[i]->loop_thread, NULL);
	}
}

sServer::~sServer()
{
	Stop();
	m_pears.clear();
}

//----------PEER implementation-----------

sPeer::sPeer()
{
	m_server = NULL;
	m_socket = NULL;
	m_address = NULL;
	m_clientSockConnected = false;
	m_lock = s3eThreadLockCreate();
	IsAlive = false;
}

sPeer::sPeer(sServer* pServer)
{
	m_server = pServer;
	m_socket = NULL;
	m_address = NULL;
	m_clientSockConnected = false;
	m_lock = s3eThreadLockCreate();
	IsAlive = false;
}

void* sPeer::Loop(void* arg)
{
	sPeer* peer = (sPeer*)arg;

	int rtn;
	char buf[SOCKET_BUFFER_SIZE];

	while (peer->IsAlive)
	{
		s3eThreadLockAcquire(peer->m_lock);
		rtn = s3eSocketRecv(peer->m_socket, buf, SOCKET_BUFFER_SIZE, 0);
		s3eThreadLockRelease(peer->m_lock);
		if (rtn>0)
		{

		}
		s3eDeviceYield();
	}

	return NULL;
}

bool sPeer::Connect(s3eSocket* newSocket, s3eInetAddress* address)
{
	m_socket = newSocket;
	m_address = address;
	IsAlive = true;
	return true;
}

bool sPeer::Connect(char* hostname)
{
	m_clientSockConnected = false;

    //Creating new socket
    m_socket = s3eSocketCreate(S3E_SOCKET_TCP, 0);
    if (m_socket == NULL)
        return false;

    // look up address
    s3eInetAddress addr;
    memset(&addr, 0, sizeof(addr));

    if (s3eInetLookup(hostname, &addr, NULL, NULL) == S3E_RESULT_ERROR)
        return false;

    addr.m_Port = s3eInetHtons(GW_PORT);

    int32 counter = 0;
    // Using the created socket, address structure and set callback function the Connect is called.
    // A wait is performed for a minute while the connect is attempted. When connection succeeds the
    // callback sets the g_SocketIsConnected bool to true causing the waiting to stop
    if (s3eSocketConnect(m_socket, &addr, &ConnectCB, this) != S3E_RESULT_SUCCESS)
    {
        switch (s3eSocketGetError())
        {
            // These errors are 'OK', because they mean,
            // that a connect is in progress
            case S3E_SOCKET_ERR_INPROGRESS:
            case S3E_SOCKET_ERR_ALREADY:
            case S3E_SOCKET_ERR_WOULDBLOCK:
                break;
            default:
                // A 'real' error happened
                return false;
        }

        // Try to connect, but wait a maximum time of SOCKET_TIMEOUT
        uint64 testStartTime = s3eTimerGetMs();
        while (s3eTimerGetMs() - testStartTime < SOCKET_TIMEOUT)
        {
            // Stop waiting since socket is now connected
            if (m_clientSockConnected)
                break;

            s3eDeviceYield(30);
        }
    }

    if (m_clientSockConnected == false)
		return false;

	IsAlive = true;
	return true;
}

int32 sPeer::ConnectCB(s3eSocket* g_Sock, void* sys, void* data)
{
    s3eResult res = *(s3eResult*)sys;
	sPeer* peer = (sPeer*)data;

    if (res == S3E_RESULT_SUCCESS)
        peer->m_clientSockConnected = true;
    else
        peer->m_clientSockConnected = false;

    return 0;
}

void sPeer::Dissconnect()
{
	IsAlive = false;
	s3eThreadLockRelease(m_lock);
}

void sPeer::Send(char* pData)
{
	char buf[SOCKET_BUFFER_SIZE];
	int32 retValue;
	strlcpy(buf,pData,SOCKET_BUFFER_SIZE);

	s3eThreadLockAcquire(m_lock);
	retValue = s3eSocketSend(m_socket, buf, SOCKET_BUFFER_SIZE, 0); 
	s3eThreadLockRelease(m_lock);
}