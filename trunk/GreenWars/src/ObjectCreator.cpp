#include "objectcreator.h"
#include "gameobject.h"
#include "IwGameSprite.h"
#include "Iw2D.h"

CObjectCreator::CObjectCreator(CIwGameSpriteManager* manager)
	:SpriteManager(manager)
{

}

CObjectCreator::~CObjectCreator()
{
	for (CIwArray<CIw2DImage*>::iterator it = ImageCache.begin(); it != ImageCache.end(); ++it)
		delete (*it);
}

CGameObject* CObjectCreator::CreateObjectByName(const char* object_name)
{
	CIw2DImage* image = Iw2DCreateImageResource(object_name);
	if(image)
	{
		ImageCache.append(image);
		CIwGameBitmapSprite* sprite = new CIwGameBitmapSprite();
		sprite->setPosAngScale(0,0, 0, IW_GEOM_ONE);
		sprite->setImage(image);

		SpriteManager->addSprite(sprite);
		CGameObject* go = new CGameObject();
		go->setSprite(sprite);
		go->Update(0);

		return go;
	}
	return NULL;
}