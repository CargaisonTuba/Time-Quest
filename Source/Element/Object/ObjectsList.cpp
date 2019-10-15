#include "ObjectsList.h"

#ifndef NULL
#define NULL 0
#endif


ObjectsList::ObjectsList()
{	
	this->_firstObject = NULL;
	this->_lastObject = NULL;
	this->_nbOfObjects = 0;
	this->_currentObject = this->_firstObject;
}

ObjectsList::~ObjectsList()
{

}

void ObjectsList::addObject(Object &newObject)
{
	if (this->_nbOfObjects == 0)
	{
		this->_firstObject = &newObject;
		this->_lastObject = &newObject;
	}
	else
	{
		newObject.setNextOne(*this->_lastObject);
		this->_lastObject = &newObject;
	}
	this->_nbOfObjects++;
}

bool ObjectsList::deleteCurrentObject()
{
	if (this->_nbOfObjects != 0)
	{
		if (this->_nbOfObjects == 1)
		{
			this->_firstObject = NULL;
			this->_lastObject = NULL;
			this->_nbOfObjects = 0;
			this->_currentObject = this->_firstObject;
			return true;
		}
		Object* subCurrObject = this->_firstObject;
		for(int i = 1; i < this->_nbOfObjects; i++)
		{
			if (subCurrObject->isNextOneEqualTo(this->_currentObject))
			{
				subCurrObject->setNextOne(*this->_currentObject);
				this->_currentObject = this->_currentObject;
				this->_nbOfObjects--;
				return true;
			}
		}
		return false;
		

	}
	return false;
	
}

Object* ObjectsList::getCurrentObject()
{
	return this->_currentObject;
}

bool ObjectsList::setCurrentToNextOne()
{
	if (this->_currentObject == this->_lastObject)
	{
		return false;
	}
	this->_currentObject = this->_currentObject;
	return true;
}

void ObjectsList::resetCurrentObject()
{
	this->_currentObject = this->_firstObject;
}

bool ObjectsList::isEmpty()
{
	return (this->_nbOfObjects == 0);
}