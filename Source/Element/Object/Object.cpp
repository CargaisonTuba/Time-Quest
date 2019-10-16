#include "Object.h"
#include "SFML/Graphics.hpp"

#ifndef NULL
#define NULL 0
#endif

Object::Object()
{
	this->_body.setPosition(0, 0);
	this->_body.setFillColor(sf::Color::Black);
	this->_body.setRadius(3);
}

Object::~Object()
{

}

bool Object::update()
{
	return true;
}

sf::CircleShape* Object::getBody()
{
	return &this->_body;
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->_body);
}