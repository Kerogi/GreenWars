#include "player.h"
#include "gameobject.h"

CPlayer::CPlayer(const char* name, CGameObject* controlled_object)
	:Name(name)
	,ControlledObject(controlled_object)
	,Health(100)
	,IsAlive(true)
{
}

void CPlayer::MoveTo(float x, float y)
{
	MovePos.x = x;
	MovePos.y = y;
}

void CPlayer::LookAt(float x, float y)
{
	TargetPos.x = x;
	TargetPos.y = y;
}

void CPlayer::Update(float dt)
{
	CIwFVec2 path = ControlledObject->getPos() - MovePos;
	if(path.GetLengthSquared() > (ControlledObject->getSize()*ControlledObject->getSize()) / 2)
	{
		ControlledObject->setDir(path);
		ControlledObject->setSpeed(-50);
	}
	else
	{
		ControlledObject->setSpeed(0);
	}
}
