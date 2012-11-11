#pragma once

#include "IwArray.h"
#include "IwGameSprite.h"

class CControls
{
	CIwGameSpriteManager SpriteManager;
	CIwArray<CIw2DImage*> ImageCache;

	CControls(void);
public:
	~CControls(void);

	static CControls * CreateControls(float width, float height);

	void Draw();
};

