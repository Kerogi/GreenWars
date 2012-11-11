
#ifndef SERVERPEER_H
#define SERVERPEER_H

#include <vector>

using namespace std;

class sPeer
{
private:
	
public:
	bool IsAlive;

	sPeer();
	bool Connect(char* address, int port);
	void Dissconnect();

	bool Send(char* data);
	char* Recive();
	~sPeer();
};

#endif