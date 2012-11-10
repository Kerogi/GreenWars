#ifndef BASEOBJECT_H
#define BASEOBJECT_H

/// Base interface for all game objects
class CBaseObject
{
public:
	/// Update object state according to dt(time interval)
	/// @param dt - time interval to evalute new object state
	void Update(int dt) = 0;
	/// Returns current object state
	/// @return Current state of object
	int GetState() = 0;
	/// Checks collision with other object
	/// @param obj - object for collision checking
	void Collision(const CBaseObject & obj) = 0;
	/// Draw object
	void Draw() = 0;
};

#endif BASEOBJECT_H