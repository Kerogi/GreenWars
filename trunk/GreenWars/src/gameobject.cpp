#include "gameobject.h"
#include "IwGameSprite.h"


CGameObject::CGameObject()
	:Position(0,0)
	,Dirrection(0,0)
	,Speed(0)
	,Size(1)
	,Sprite(NULL)
	,AdvancedMovement(false)
{
}
/*
CGameObject::CGameObject(const CGameObject& copyMe)
	:Position(copyMe.Position)
	,Dirrection(copyMe.Dirrection)
	,Speed(copyMe.Speed)
	,Size(copyMe.Size)
	,Sprite(copyMe.Sprite)
{
	
}
**/
void CGameObject::setAdvancedMovement(bool movement)
{
	AdvancedMovement = movement;
}

bool CGameObject::Update(float dt)
{
	Position += Dirrection * Speed * dt;
	if(AdvancedMovement)
	{
		CIwFVec2 AttractorPoint(0,0);
		AttractorPoint -= Position;
		AttractorPoint.Normalise();
		Dirrection -= AttractorPoint *0.02f;
		Dirrection.Normalise();
	}

	if(Sprite)
	{
		Sprite->setAngle(IwGeomAtan2(IW_FIXED(-Dirrection.x),IW_FIXED(Dirrection.y)));
		Sprite->setPosition(Position.x, Position.y);
		Sprite->setScale(IW_FIXED(Size));
	}
	return true;
}

bool CGameObject::Collision(const CGameObject & obj)
{
	float distanceSquared = (obj.getPos() - Position).GetLengthSquared();
	float minDistanceSquared = (Size*Size + obj.getSize()*obj.getSize());
	return (distanceSquared < minDistanceSquared);
}
