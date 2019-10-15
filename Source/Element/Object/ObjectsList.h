#pragma once

#include "Object.h"

class ObjectsList
{
public:
	ObjectsList();
	~ObjectsList();
	void addObject(Object &newObject);
	bool deleteCurrentObject();
	Object *getCurrentObject();
	bool setCurrentToNextOne();
	void resetCurrentObject();
	bool isEmpty();
private:
	Object *_firstObject;
	Object *_lastObject;
	Object *_currentObject;
	int _nbOfObjects;
};