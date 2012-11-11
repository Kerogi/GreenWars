#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H

#include "IwString.h"

enum CommandType
{
		HEARTBEAT=0,
		PLAYER_GOTO_COMMAND, 
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
	virtual const uint16* getMap();

	friend class CCommandFactory;
};

class CGotoPlayerCommand: public CGameCommand
{
public:
	float Target_x;
	float Target_y;
	CIwStringS PlayerName;
	CGotoPlayerCommand();
public:
	virtual bool Deserialize(char* ByteBuffer, int length);
	virtual void Serialize(char* ByteBuffer, int length);
	virtual const uint16* getMap();

	friend class CCommandFactory;
};

class CMovePlayerCommand: public CGameCommand
{
public:
	float Delta_x;
	float Delta_y;
	CIwStringS PlayerName;
	CMovePlayerCommand();
public:
	virtual bool Deserialize(char* ByteBuffer, int length);
	virtual void Serialize(char* ByteBuffer, int length);
	virtual const uint16* getMap();

	friend class CCommandFactory;
};

class CCommandFactory
{
public:
	static CGameCommand* CreateCommandFromBuffre(char* ByteBuffer, int length);
};

#endif