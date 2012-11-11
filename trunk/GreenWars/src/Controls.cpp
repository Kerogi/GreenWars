#include "Controls.h"
#include "gameobject.h"
#include "objectcreator.h"

CControls::CControls(void)
{
}


CControls::~CControls(void)
{
	for (Iterator it = Objects.begin(); it != Objects.end(); ++it)
		delete (*it);
}


CControls * CControls::CreateControls(float width, float height, CObjectCreator * objectCreator)
{
	CControls* controls = new CControls();
	
	CGameObject* go = objectCreator->CreateObjectByName("touchscreenMoveDown");
	go->setPos(0,0);
	go->setSize(0.5f);
	controls->Objects.push_back(go);
	CGameObject* go = objectCreator->CreateObjectByName("touchscreenMoveUP");
	go->setPos(0,0);
	go->setSize(0.5f);
	controls->Objects.push_back(go);
	CGameObject* go = objectCreator->CreateObjectByName("touchscreenMoveL");
	go->setPos(0,0);
	go->setSize(0.5f);
	controls->Objects.push_back(go);
	CGameObject* go = objectCreator->CreateObjectByName("touchscreenMoveR");
	go->setPos(0,0);
	go->setSize(0.5f);
	controls->Objects.push_back(go);
}
