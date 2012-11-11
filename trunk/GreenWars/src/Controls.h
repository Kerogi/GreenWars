#pragma once

#include "IwArray.h"
#include "IwGameSprite.h"

class CControls
{
	int ScreenWidth;
	int ScreenHeight;

	CIwGameSpriteManager SpriteManager;
	CIwArray<CIw2DImage*> ImageCache;

	struct HitZone
	{
		int x,y,w,h;
	};

	CIwArray<HitZone> hitZones;


	CControls(void);
public:
	~CControls(void);

	static CControls * CreateControls(float width, float height);

	void Draw();

	void UpdateControls();

	bool CheckHit(HitZone * hzone);
};

