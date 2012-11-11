#include "Level.h"
#include "gameobject.h"
#include "objectcreator.h"

CLevel::CLevel()
	:Running(false)
{
}

CLevel::~CLevel()
{
	for (Iterator it = Objects.begin(); it != Objects.end(); ++it)
		delete (*it);
}

void CLevel::Start()
{
	Running = true;
}

void CLevel::Stop()
{
	Running = false;
}

void CLevel::Update(float dt)
{
	if(Running)
	for (Iterator it = Objects.begin(); it != Objects.end(); ++it)
		(*it)->Update(dt);
}

CLevel* CLevel::CreateTestLevel(float width, float height, CObjectCreator* objectCreator)
{
	CLevel* level = new CLevel();
	int num = 22;
	double da = 0;
	double di = PI*2.0/(double)num;
	for(int i=0;i<=num;++i,da+=di)
	{	
		CGameObject* go = objectCreator->CreateObjectByName("test1");
		if(go == NULL) continue;
		
		double dx = cos(da);
		double dy = sin(da);
		float x = 0 + dx * 100;
		float y = 0 + dy * 100;
		go->setPos(x,y);
		go->setDir(cos(da+di),sin(da+di));
		go->setSpeed(-100+50*(i%2));
		go->setSize(0.5f);
		level->Objects.push_back(go);
	}
	/*
	CGameObject* go = objectCreator->CreateObjectByName("test1");
	go->setPos(100,0);
	go->setSize(0.5f);
	go->setDir(-1,-1);
	go->setSpeed(5);
	level->Objects.push_back(go);
	*/
	return level;
}
