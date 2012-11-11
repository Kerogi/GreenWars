#include "Controls.h"
#include "gameobject.h"
#include "objectcreator.h"
#include "IwGameSprite.h"
#include "Iw2D.h"
#include "game.h"

CControls::CControls(CGame & game)
	: Game(game)
{
	
}

CControls::~CControls(void)
{
	for (CIwArray<CIw2DImage*>::iterator it = ImageCache.begin(); it != ImageCache.end(); ++it)
		delete (*it);
}


CControls * CControls::CreateControls(float width, float height, CGame & game)
{
	int crosX = 50;
	int crosY = height - 50;

	CControls* controls = new CControls(game);

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
		HitZone hz = {sprite->getPosition().x, sprite->getPosition().y, image->GetWidth(), image->GetHeight()};
		hz.cmd.Delta_x = 0;
		hz.cmd.Delta_y = 10;
		hz.cmd.PlayerName = "player1";
		controls->hitZones.append(hz);
	}

	image = Iw2DCreateImageResource("touchscreenMoveUp");
	if(image)
	{
		controls->ImageCache.append(image);
		CIwGameBitmapSprite* sprite = new CIwGameBitmapSprite();
		sprite->setPosAngScale(crosX, crosY - 20, 0, IW_GEOM_ONE/2);
		sprite->setImage(image);
		controls->SpriteManager.addSprite(sprite);
		HitZone hz = {sprite->getPosition().x, sprite->getPosition().y, image->GetWidth(), image->GetHeight()};
		hz.cmd.Delta_x = 0;
		hz.cmd.Delta_y = -10;
		hz.cmd.PlayerName = "player1";
		controls->hitZones.append(hz);
	}

	image = Iw2DCreateImageResource("touchscreenMoveL");
	if(image)
	{
		controls->ImageCache.append(image);
		CIwGameBitmapSprite* sprite = new CIwGameBitmapSprite();
		sprite->setPosAngScale(crosX - 20, crosY, 0, IW_GEOM_ONE/2);
		sprite->setImage(image);
		controls->SpriteManager.addSprite(sprite);
		HitZone hz = {sprite->getPosition().x, sprite->getPosition().y, image->GetWidth(), image->GetHeight()};
		hz.cmd.Delta_x = -10;
		hz.cmd.Delta_y = 0;
		hz.cmd.PlayerName = "player1";
		controls->hitZones.append(hz);
	}

	image = Iw2DCreateImageResource("touchscreenMoveR");
	if(image)
	{
		controls->ImageCache.append(image);
		CIwGameBitmapSprite* sprite = new CIwGameBitmapSprite();
		sprite->setPosAngScale(crosX + 20, crosY, 0, IW_GEOM_ONE/2);
		sprite->setImage(image);
		controls->SpriteManager.addSprite(sprite);
		HitZone hz = {sprite->getPosition().x, sprite->getPosition().y, image->GetWidth(), image->GetHeight()};
		hz.cmd.Delta_x = 10;
		hz.cmd.Delta_y = 0;
		hz.cmd.PlayerName = "player1";
		controls->hitZones.append(hz);
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

bool CControls::CheckHit(HitZone * hzone)
{
	int x = s3ePointerGetX();
	int y = s3ePointerGetY();

	return((hzone->x<x)&&((hzone->x + hzone->w)>x)&&(hzone->y<y)&&((hzone->y + hzone->h)>y));
}

void CControls::UpdateControls()
{
	s3ePointerUpdate();
	s3eKeyboardUpdate();

	if (s3ePointerGetState(S3E_POINTER_BUTTON_SELECT) & S3E_POINTER_STATE_DOWN)
	{
		for(CIwArray<HitZone>::iterator it = hitZones.begin(); it != hitZones.end(); ++it)
		{
			if(CheckHit(it))
			{
				Game.ProcessCommand(&it->cmd);
				return;
			}
		}
	}
}