#include "player.h"
#include "gameobject.h"

CPlayer::CPlayer(const char* name, CGameObject* controlled_object)
	:Name(name)
	,ControlledObject(controlled_object)
	,cachesSquaredSize(0)
{
	MovePos = ControlledObject->getPos();
	TargetPos = ControlledObject->getPos();
	cachesSquaredSize = ControlledObject->getSize();
	cachesSquaredSize *= cachesSquaredSize;
}

void CPlayer::setPos(float x, float y)
{
	ControlledObject->setPos(x,y);
}

void CPlayer::setSize(float size)
{
	ControlledObject->setSize(size);
	cachesSquaredSize = size*size;
}

void CPlayer::moveTo(float x, float y)
{
	MovePos.x = x;
	MovePos.y = y;
}

void CPlayer::lookAt(float x, float y)
{
	TargetPos.x = x;
	TargetPos.y = y;
}

void CPlayer::Update(float dt)
{
	CIwFVec2 path = MovePos - ControlledObject->getPos();
	if(path.GetLengthSquared() > (cachesSquaredSize / 2) )
	{
		ControlledObject->setDir(path);
		ControlledObject->setSpeed(50);
	}
	else
	{
		ControlledObject->setSpeed(0);
	}
}
