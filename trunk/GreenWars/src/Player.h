#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "IwGeom.h"
#include "IwString.h"

class CGameObject;

class CPlayer
{
private:
	CGameObject* ControlledObject;
	int Health;
	bool IsAlive;
	CIwFVec2 TargetPos;
	CIwFVec2 MovePos;
	CIwStringS Name;
	CPlayer(const char* Name, CGameObject* controlled_object);
public:
	friend class CGame;

	void MoveTo(float x, float y);
	void LookAt(float x, float y);
	void Update(float dt);
};

#endif