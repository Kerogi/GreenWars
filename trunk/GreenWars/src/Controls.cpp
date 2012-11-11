#include "Controls.h"
#include "gameobject.h"
#include "objectcreator.h"
#include "IwGameSprite.h"
#include "Iw2D.h"

CControls::CControls(void)
{
}

CControls::~CControls(void)
{
	for (CIwArray<CIw2DImage*>::iterator it = ImageCache.begin(); it != ImageCache.end(); ++it)
		delete (*it);
}


CControls * CControls::CreateControls(float width, float height)
{
	int crosX = 50;
	int crosY = height - 50;

	CControls* controls = new CControls();
		
	controls->ScreenWidth = width;
	controls->ScreenHeight = height;


	CIw2DImage* image;
	
	image = Iw2DCreateImageResource("touchscreenMoveDown");
	if(image)
	{
		controls->ImageCache.append(image);
		CIwGameBitmapSprite* sprite = new CIwGameBitmapSprite();
		sprite->setPosAngScale(crosX, crosY + 20, 0, IW_GEOM_ONE/2);
		sprite->setImage(image);
		controls->SpriteManager.addSprite(sprite);
	}

	image = Iw2DCreateImageResource("touchscreenMoveUp");
	if(image)
	{
		controls->ImageCache.append(image);
		CIwGameBitmapSprite* sprite = new CIwGameBitmapSprite();
		sprite->setPosAngScale(crosX, crosY - 20, 0, IW_GEOM_ONE/2);
		sprite->setImage(image);
		controls->SpriteManager.addSprite(sprite);
	}

	image = Iw2DCreateImageResource("touchscreenMoveL");
	if(image)
	{
		controls->ImageCache.append(image);
		CIwGameBitmapSprite* sprite = new CIwGameBitmapSprite();
		sprite->setPosAngScale(crosX - 20, crosY, 0, IW_GEOM_ONE/2);
		sprite->setImage(image);
		controls->SpriteManager.addSprite(sprite);
	}

	image = Iw2DCreateImageResource("touchscreenMoveR");
	if(image)
	{
		controls->ImageCache.append(image);
		CIwGameBitmapSprite* sprite = new CIwGameBitmapSprite();
		sprite->setPosAngScale(crosX + 20, crosY, 0, IW_GEOM_ONE/2);
		sprite->setImage(image);
		controls->SpriteManager.addSprite(sprite);
	}

	return controls;
}

void CControls::Draw()
{
	CIwMat2D WorldTransform;
	WorldTransform.SetIdentity();
	SpriteManager.setTransform(WorldTransform);
	SpriteManager.Draw();
}

void CControls::UpdateControls()
{
    s3ePointerUpdate();
    s3eKeyboardUpdate();


}