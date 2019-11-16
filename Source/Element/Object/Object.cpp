#include "Object.h"
#include "SFML/Graphics.hpp"
#include <iostream>

#ifndef NULL
#define NULL 0
#endif

Object::Object(std::string texturePath, sf::Vector2f throwerPosition, sf::Vector2f direction)
{
	_creationDate = (time_t)0;
	if (!_objectText.loadFromFile(texturePath))
	{
		std::cout << "Erreur texture balle \n";
	}
	_objectSprite.setTexture(_objectText);
	this->_direction = direction;
	this->_objectSprite.setPosition(throwerPosition);
	this->_posInit = throwerPosition;
}

Object::Object()
{
	_creationDate = (time_t)0;
}

Object::~Object()
{

}

bool Object::update()
{
	return true;
}

/*sf::CircleShape& Object::getBody()
{
	//std::cout << "body";
	return this->_body;
}*/

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite s = _objectSprite;
	s.setTexture(_objectText);
	target.draw(s);
}

sf::Vector2f Object::getDirection()
{
	//std::cout << "direction x: " << _direction.x << " y: " << _direction.y << "\n";
	return _direction;
}

sf::FloatRect Object::getHitbox() const {
	return _objectSprite.getGlobalBounds();
}