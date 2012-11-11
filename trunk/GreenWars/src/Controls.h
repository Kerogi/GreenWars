#pragma once

#include "IwArray.h"

class CGameObject;
class CObjectCreator;

class CControls
{
	typedef CIwArray<CGameObject*> ObjectsList;
	typedef ObjectsList::iterator	Iterator;

	ObjectsList Objects;

	CControls(void);
public:
	~CControls(void);
	CControls * CreateControls(float width, float height, CObjectCreator * objectCreator);
};

