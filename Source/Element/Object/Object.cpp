#include "Object.h"

#ifndef NULL
#define NULL 0
#endif

Object::Object()
{
	this->_nextOne = NULL;
}

Object::~Object()
{

}

void Object::setNextOne(Object &newObject)
{
	this->_nextOne = &newObject;
}


bool Object::isNextOneEqualTo(Object *comparedObject)
{
	if (this->_nextOne == NULL)
	{
		return false;
	}
	else
	{
		return this->_nextOne == comparedObject;
	}
}

bool Object::update()
{
	return true;
}