#pragma once

#include "IwArray.h"
#include "IwGameSprite.h"

class CGame;

class CControls
{
	CGame & Game;

	int ScreenWidth;
	int ScreenHeight;

	CIwGameSpriteManager SpriteManager;
	CIwArray<CIw2DImage*> ImageCache;

	struct HitZone
	{
		int x,y,w,h;
	};

	CIwArray<HitZone> hitZones;


	CControls(CGame & game);
public:
	~CControls(void);

	static CControls * CreateControls(float width, float height, CGame & game);

	void Draw();

	void UpdateControls();

	bool CheckHit(HitZone * hzone);
};

