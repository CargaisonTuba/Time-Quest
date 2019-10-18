#include "Object.h"
#include "SFML/Graphics.hpp"
#include <iostream>

#ifndef NULL
#define NULL 0
#endif

Object::Object(sf::Vector2f throwerPosition, sf::Vector2f direction)
{

	this->_body.setFillColor(sf::Color::Red);
	this->_body.setRadius(3);
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

sf::CircleShape& Object::getBody()
{
	//std::cout << "body";
	return this->_body;
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	target.draw(_body);
}

sf::Vector2f Object::getDirection()
{
	//std::cout << "direction x: " << _direction.x << " y: " << _direction.y << "\n";
	return _direction;
}