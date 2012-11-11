#include "IwGameSprite.h"

//
//
// CIwGameSprite implementation
//
//
void CIwGameSprite::RebuildTransform()
{
	// Build the transform
	// Set the rotation transform
	Transform.SetRot(Angle);
	// Scale the transform
	Transform.ScaleRot(Scale);
	// Translate the transform
	Transform.SetTrans(Position);
	Transform.PostMult(Parent->getTransform());

	TransformDirty = false;
}

void CIwGameSprite::Init()
{
	TransformDirty = true;
	Position.x = 0;
	Position.y = 0;
	Angle = 0;
	Scale = IW_GEOM_ONE;
	Colour.r = 0xff;
	Colour.g = 0xff;
	Colour.b = 0xff;
	Colour.a = 0xff;
}

//
//
// CIwGameBitmapSprite implementation
//
//
void CIwGameBitmapSprite::Draw()
{
	// Do not render if not visible
	if (Image == NULL || !Visible || Colour.a == 0)
		return;

	if (TransformDirty)
		RebuildTransform();

	// Set this transform as the active transform for Iw2D
	Iw2DSetTransformMatrix(Transform);

	// Set colour of sprite
	Iw2DSetColour(Colour);

	// Render the sprite (centered)
	int x = -(Image->GetWidth() / 2);
	int y = -(Image->GetHeight() / 2);
	Iw2DDrawImage(Image, CIwSVec2(x, y));
}

//
//
// CIwGameSpriteManager implementation
//
//
void CIwGameSpriteManager::addSprite(CIwGameSprite* sprite)
{
	Sprites.push_back(sprite);
	sprite->setParent(this);
}

void CIwGameSpriteManager::removeSprite(CIwGameSprite* sprite, bool delete_sprites)
{
	for (Iterator it = Sprites.begin(); it != Sprites.end(); ++it)
	{
		if (*it == sprite)
		{
			if (delete_sprites && !(*it)->isPooled())
				delete *it;
			Sprites.erase(it);
			break;
		}
	}
}

void CIwGameSpriteManager::Draw()
{
	// Draw all sprites in the sprite manager
	for (Iterator it = Sprites.begin(); it != Sprites.end(); ++it)
		(*it)->Draw();
}

void CIwGameSpriteManager::Release(bool delete_sprites)
{
	if (delete_sprites)
	{
		// Delete all sprites in the sprite manager
		for (Iterator it = Sprites.begin(); it != Sprites.end(); ++it)
		{
			if (!(*it)->isPooled())
				delete *it;
		}
	}
	Sprites.clear();
}

void CIwGameSpriteManager::DirtyChildTransforms()
{
	// Force all childreen to rebuild their transforms
	for (Iterator it = Sprites.begin(); it != Sprites.end(); ++it)
	{
		(*it)->forceTransformDirty();
	}
}

