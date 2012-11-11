#ifndef LEVEL_H
#define LEVEL_H

//#include "gameobject.h"
#include "IwArray.h"

class CGameObject;
class CObjectCreator;

class CLevel
{
	typedef CIwArray<CGameObject*> ObjectsList;
	typedef ObjectsList::iterator	Iterator;

	ObjectsList Objects;
	bool Running;
	CLevel();
public:
	~CLevel();

	void Start();
	void Stop();
	void Update(float dt);
	void AddObject(CGameObject* obj);

	static CLevel* CreateTestLevel(float width, float height, CObjectCreator* objectCreator);
};

//CLevel* CreateTestLevel();
#endif LEVEL_H