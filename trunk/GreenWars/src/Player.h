#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "IwGeom.h"
#include "IwString.h"

class CGameObject;

class CPlayer
{
private:
	CGameObject* ControlledObject;
	float cachesSquaredSize;
	CIwFVec2 TargetPos;
	CIwFVec2 MovePos;
	CIwStringS Name;
	CPlayer(const char* Name, CGameObject* controlled_object);
public:
	friend class CGame;
	void setSize(float size);
	void setPos(float x, float y);
	void moveTo(float x, float y);
	void lookAt(float x, float y);
	void Update(float dt);
};

#endif