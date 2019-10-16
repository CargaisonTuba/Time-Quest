#include "ThrowedObject.h"

ThrowedObject::ThrowedObject(sf::Vector2f throwerPosition, sf::Vector2f direction)
{
	this->_body.setPosition(0, 0);
	this->_body.setFillColor(sf::Color::Red);
	this->_body.setRadius(3);
	this->_creationDate = std::time(0);
	this->_direction = direction;
	this->_body.setPosition(throwerPosition);
}

ThrowedObject::ThrowedObject()
{

}

ThrowedObject::~ThrowedObject()
{

}

bool ThrowedObject::update()
{
	if (_clock.getElapsedTime() > sf::seconds(5.f))
	{
		return false;
	}
	this->_body.move(_direction);
	return true;
}