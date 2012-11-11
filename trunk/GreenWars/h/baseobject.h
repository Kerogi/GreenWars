#ifndef BASEOBJECT_H
#define BASEOBJECT_H

/// Base interface for all game objects
class CBaseObject
{
public:
	virtual ~CBaseObject() {};
	/// Update object state according to dt(time interval in sec)
	/// @param dt - time interval to evalute new object state
	virtual bool Update(float dt) = 0;
	/// Returns current object state
	/// @return Current state of object
	virtual int GetState() = 0;
	/// Draw object
	virtual void Draw() = 0;
};

#endif BASEOBJECT_H