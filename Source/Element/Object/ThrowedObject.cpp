#include "ThrowedObject.h"
#include "iostream"

ThrowedObject::ThrowedObject(sf::Vector2f throwerPosition, sf::Vector2f direction, float damages) :
	Object(throwerPosition, direction)
{
	this->_body.setFillColor(sf::Color::Black);
	this->_body.setOutlineColor(sf::Color::White);
	this->_body.setOutlineThickness(1);
	this->_body.setRadius(5);
	_clock = sf::Clock();
	this->_clock.restart();

	_damages = damages;
}

ThrowedObject::ThrowedObject()
{

}

ThrowedObject::~ThrowedObject()
{

}


float ThrowedObject::getDamages() const {
	return _damages;
}

bool ThrowedObject::update(float const& dt)
{
	if (_clock.getElapsedTime() > sf::seconds(5.f))
	{
		return false;
	}

	this->_body.move(_direction * dt);
	return true;
}