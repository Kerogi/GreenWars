#include "GameCommand.h"
#include "IwGx.h"
#include "IwGxPrint.h"
#include "IwSerialise.h"

CGameCommand* CCommandFactory::CreateCommandFromBuffre(char* ByteBuffer, int length)
{
	CommandType type = static_cast<CommandType>(ByteBuffer[0]);
	CGameCommand* cmd = 0;
	switch(type)
	{
		case PLAYER_MOVE_COMMAND:
		{
			cmd = new CMovePlayerCommand();
			if(!cmd->Deserialize(ByteBuffer+sizeof(CommandType), length-1))
			{
				delete cmd;
				cmd = 0;
			}
		}
		break;
		//default:
			//return 0;
	}
	return cmd;
}
#include <strstream> 

CGameCommand::CGameCommand()
{

}

const uint16* CGameCommand::getMap()
{
	static uint16 mmap[] = { IW_TYPE_UINT16 };
	return mmap;
}

CMovePlayerCommand::CMovePlayerCommand()
{
	Type = PLAYER_MOVE_COMMAND;
}

void  CMovePlayerCommand::Serialize(char* ByteBuffer, int length)
{
	IwSerialiseOpenFromMemory (ByteBuffer, length, false);
	// serialise out using the above-defined structure
    IwSerialiseMappedData(getMap(), this, 1, sizeof(this));

	IwSerialiseClose();
}

bool CMovePlayerCommand::Deserialize(char* ByteBuffer, int length)
{
	IwSerialiseOpenFromMemory (ByteBuffer, length, true);
	// serialise out using the above-defined structure
    IwSerialiseMappedData(getMap(), this, 1, sizeof(this));
	
	IwSerialiseClose();
	return true;
}

const uint16* CMovePlayerCommand::getMap()
{
	static uint16 mmap[] = { IW_TYPE_UINT16 , IW_TYPE_FLOAT, IW_TYPE_FLOAT, IW_TYPE_ARRAY(IW_TYPE_CHAR, 16)};
	return mmap;
}
