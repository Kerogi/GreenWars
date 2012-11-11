#if !defined(_CIWGAME_SPRITE_H_)
#define _CIWGAME_SPRITE_H_

#include "s3e.h"
#include "Iw2D.h"

class CIwGameSpriteManager;

//
//
// CIwGameSprite - A sprite is the visual representation of an on screen game object
//
// Can be thought of as an interface rather than a concrete class as other sprite types are created from this
//
//
class CIwGameSprite
{
	/// Properties
protected:
	CIwGameSpriteManager* Parent;		// Parent sprite manager
	CIwSVec2	Position;				// Position of the sprite
	iwangle		Angle;					// Rotation of sprite (IW_ANGLE_2PI = 360 degrees)
	iwfixed		Scale;					// Scale of sprite (IW_GEOM_ONE = 1.0)
	CIwColour	Colour;					// Colour of sprite
	bool		Visible;				// Sprites visible state
	bool		Pooled;					// Tells system if we belong to a sprite pool or not
	bool		InUse;					// Used in a memory pooling system to mark this sprite as in use
public:
	void		setParent(CIwGameSpriteManager* parent) { Parent = parent; }
	void		setPosAngScale(int x, int y, iwangle angle, iwfixed scale)
	{
		Position.x = x;
		Position.y = y;
		Angle = angle;
		Scale = scale;
		TransformDirty = true;
	}
	void		setPosition(int x, int y)
	{
		Position.x = x;
		Position.y = y;
		TransformDirty = true;
	}
	CIwSVec2	getPosition() const			{ return Position; }
	void		setAngle(iwangle angle)
	{
		Angle = angle;
		TransformDirty = true;
	}
	iwangle		getAngle() const			{ return Angle; }		
	void		setScale(iwfixed scale)
	{
		Scale = scale;
		TransformDirty = true;
	}
	iwfixed		getScale() const			{ return Scale; }
	void		setColour(CIwColour colour) { Colour = colour; }
	CIwColour	getColour() const			{ return Colour; }
	void		setVisible(bool show)		{ Visible = show; }
	bool		isVisible() const			{ return Visible; }
	void		forceTransformDirty()		{ TransformDirty = true; }
	void		setPooled(bool pooled)		{ Pooled = pooled; }
	bool		isPooled() const			{ return Pooled; }
	void		setInUse(bool in_use)		{ InUse = in_use; }
	bool		isInUse() const				{ return InUse; }
	/// Properties End
protected:
	CIwMat2D	Transform;				// Transform
	bool		TransformDirty;			// Dirty when transform changed

	void		RebuildTransform();		// Rebuilds the display transform

public:
	CIwGameSprite() : Pooled(false) { Init(); }
	virtual ~CIwGameSprite() {}

	virtual void	Init();				// Called to initialise the sprite, used after construction or to reset the sprite in a pooled sprite system
	virtual void	Draw() = 0;			// Pure virtual, need to implement in derived classes
};

//
//
// CIwGameBitmapSprite - A BitmapSprite is a bitmapped visual representation of an on screen game object
//
//
class CIwGameBitmapSprite : public CIwGameSprite
{
	// Properties
protected:
	CIw2DImage*	Image;					// Bitmapped image that represents this sprite
	int			Width, Height;			// Destination width and height
	int			SrcX, SrcY;				// Top left position in source texture
	int			SrcWidth, SrcHeight;	// Width and height of sprite in source texture
public:
	void		setImage(CIw2DImage* image)
	{
		Image = image;
	}
	void		setDestSize(int width, int height)
	{
		Width = width;
		Height = height;
	}
	void		setSrcRect(int x, int y, int width, int height)
	{
		SrcX = x;
		SrcY = y; 
		SrcWidth = width;
		SrcHeight = height;
	}
	// Properties End
public:

	CIwGameBitmapSprite() : CIwGameSprite(), Image(NULL)	{}
	virtual ~CIwGameBitmapSprite() {}
	
	void	Draw();
};

//
//
// CIwGameSpriteManager - A sprite manager 
//
// The sprite manager managers a collection of sprites, including drawing, tracking and clean up
// The sprite manager also carries its own visual transform that will be applied to all of its children, allowing the user to apply rotation, scaling ans translation to all child sprites
//
//
class CIwGameSpriteManager
{
public:
	// Provide public access to iteration of the sprite list
	typedef CIwList<CIwGameSprite*>::iterator	Iterator;
	Iterator		begin() { return Sprites.begin(); }
	Iterator		end()	{ return Sprites.end(); }

	// Properties
protected:
	CIwMat2D					Transform;			// Transform
	CIwList<CIwGameSprite*>		Sprites;			// Our list of sprites
public:
	void			addSprite(CIwGameSprite* sprite);
	void			removeSprite(CIwGameSprite* sprite, bool delete_sprites = true);
	void			setTransform(const CIwMat2D& transform)	{ Transform = transform; DirtyChildTransforms(); }
	const CIwMat2D&	getTransform() const					{ return Transform; }
	// Properties End

protected:
	void			DirtyChildTransforms();

public:
	CIwGameSpriteManager()
	{
		// Set up default rotation, scaling and translation
		Transform.SetIdentity();
		Transform.m[0][0] = IW_GEOM_ONE;
		Transform.m[1][1] = IW_GEOM_ONE;
	}
	~CIwGameSpriteManager() { Release(); }
	
	void			Draw();
	void			Release(bool delete_sprites = true);
};





#endif // _CIWGAME_SPRITE_H_
