#include "Object.h"
#include "SFML/Graphics.hpp"

#ifndef NULL
#define NULL 0
#endif

Object::Object(sf::Vector2f throwerPosition, sf::Vector2f direction)
{
	this->_body.setPosition(0, 0);
	this->_body.setFillColor(sf::Color::Red);
	this->_body.setRadius(3);
	this->_creationDate = std::time(0);
	this->_direction = direction;
	this->_body.setPosition(throwerPosition);
}

Object::Object()
{

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