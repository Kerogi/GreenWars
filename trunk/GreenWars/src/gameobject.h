#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "baseobject.h"
#include "IwGeom.h"

class CIwGameSprite;

/// Base interface for all game objects
class CGameObject: public CBaseObject
{
	CIwGameSprite* Sprite;
	CIwFVec2	Position;				// Position of the sprite
	CIwFVec2	Dirrection;				// Position of the sprite
	float		Speed;
	float		Size;
	bool		AdvancedMovement;
	friend class CObjectCreator;
	CGameObject();
public:
	//CGameObject(const CGameObject&);
	void setAdvancedMovement(bool movement);

	const CIwFVec2& getPos() const		{ return Position;  }
	void setPos(const CIwFVec2& pos)	{ Position = pos;   }
	void setPos(const float x, const float y)	{ Position.x = x; Position.y = y;}

	const CIwFVec2& getDir() const 		{ return Dirrection;}
	void setDir(const CIwFVec2& dir)	{ Dirrection = dir; Dirrection.Normalise();}
	void setDir(const float dx, const float dy)	{ Dirrection.x = dx; Dirrection.y = dy; Dirrection.Normalise();}
	
	float getSpeed() const		{ return Speed;     }
	void setSpeed(const float speed)	{ Speed = speed;    }

	float getSize() const			{ return Size;      }
	void setSize(const float size)		{ Size = size;      }

	CIwGameSprite* getSprite() const			{ return Sprite;      }
	void setSprite(CIwGameSprite* sprite)		{ Sprite = sprite;    }


	bool Update(float dt);
	int  GetState() {return 0;};
	bool Collision(const CGameObject & obj);
	void Draw() {};
};


#endif GAMEOBJECT_H