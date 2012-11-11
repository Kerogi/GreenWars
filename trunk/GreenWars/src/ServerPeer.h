
#ifndef SERVERPEER_H
#define SERVERPEER_H

#include <vector>


class sServer;

class sPeer
{
private:
	sServer* m_server;
	s3eSocket* m_socket;
	s3eInetAddress* m_address;

	bool m_clientSockConnected;

	s3eThreadLock* m_lock;
	
	static int32 ConnectCB(s3eSocket* g_Sock, void* sys, void* data);

public:
	bool IsAlive;
	s3eThread* loop_thread;

	sPeer();
	sPeer(sServer* pServer);

	static void* Loop(void* arg);

	bool Connect(s3eSocket* newSocket, s3eInetAddress* address);
	bool Connect(char* hostname);
	void Dissconnect();

	void Send(char* pData);

	/*bool Send(char* data);
	char* Recive();*/
	//~sPeer();
};

class sServer
{
private:
	s3eSocket* g_Sock;

	std::vector<sPeer*> m_pears;

	static int32 AcceptCallback(s3eSocket* sock, void* sysData, void* userData);
	
public:

	sServer();
	void Start();
	void Stop();

	void CreatePeer(s3eSocket* newSocket, s3eInetAddress* address);

	~sServer();
};

#endif