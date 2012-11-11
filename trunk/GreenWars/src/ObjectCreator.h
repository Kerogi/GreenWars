#ifndef OBJECTCRETOR_H
#define OBJECTCRETOR_H
#include <IwArray.h>

class CIwGameSpriteManager;
class CGameObject;
class CIw2DImage;

class CObjectCreator
{
	CIwGameSpriteManager* SpriteManager;
	CIwArray<CIw2DImage*> ImageCache;
public: 
	CObjectCreator(CIwGameSpriteManager* manager);
	~CObjectCreator();

	CGameObject* CreateObjectByName(const char* objectName);
};

//extern CIwArray<CIw2DImage*> g_LoadedImages;
//CLevel* CreateTestLevel();
#endif OBJECTCRETOR_H