#include "GameCommand.h"

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

CMovePlayerCommand::CMovePlayerCommand()
{
	Type = PLAYER_MOVE_COMMAND;
}

void  CMovePlayerCommand::Serialize(char* ByteBuffer, int length)
{
	std::strstream bf(ByteBuffer, length);
	int left = length;
	bf.write(reinterpret_cast<char*>(&Type), sizeof(CommandType));
	bf.write(reinterpret_cast<char*>(&Target_x), sizeof(float));
	bf.write(reinterpret_cast<char*>(&Target_y), sizeof(float));
	int len = PlayerName.length();
	bf.write(reinterpret_cast<char*>(&len), sizeof(int));
	bf.write(PlayerName.c_str(), sizeof(char) * PlayerName.length());
	left -= bf.tellp();
	bf.flush();


}

bool CMovePlayerCommand::Deserialize(char* ByteBuffer, int length)
{
	std::strstream bf(ByteBuffer, length);
	int left = length;
	bf.read(reinterpret_cast<char*>(&Target_x), sizeof(float));
	bf.read(reinterpret_cast<char*>(&Target_y), sizeof(float));
	int len = 0;
	bf.read(reinterpret_cast<char*>(&len), sizeof(float));
	char* sPlayerName = 0;
	left -= bf.tellp();
	bf.read(sPlayerName, length);
	PlayerName = sPlayerName;

	return true;
}

bool CMovePlayerCommand::Act()
{
	return false;
}