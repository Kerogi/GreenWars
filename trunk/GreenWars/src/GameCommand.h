#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H

#include "IwString.h"

enum CommandType
{
		HEARTBEAT=0,
		PLAYER_MOVE_COMMAND 
} ;

class CommandFactory;

class CGameCommand
{
public:
	CGameCommand();
	CommandType Type;
public:
	CommandType getType() const { return Type; }

	virtual bool Deserialize(char* ByteBuffer, int length) = 0;
	virtual void Serialize(char* ByteBuffer, int length) = 0;
	virtual bool Act() = 0;

	friend class CCommandFactory;
};

class CMovePlayerCommand: public CGameCommand
{
public:
	float Target_x;
	float Target_y;
	CIwStringS PlayerName;
	CMovePlayerCommand();
public:
	virtual bool Deserialize(char* ByteBuffer, int length);
	virtual void Serialize(char* ByteBuffer, int length);
	virtual bool Act();

	friend class CCommandFactory;
};


class CCommandFactory
{
public:
	static CGameCommand* CreateCommandFromBuffre(char* ByteBuffer, int length);
};

#endif