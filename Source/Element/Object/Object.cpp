#include "Object.h"
#include "SFML/Graphics.hpp"
#include <iostream>

#ifndef NULL
#define NULL 0
#endif

Object::Object(std::string texturePath, sf::Vector2f initPosition)
{
	_creationDate = (time_t)0;
	if (!_objectText.loadFromFile(texturePath))
	{
		std::cout << "Erreur texture balle : " << texturePath << "\n";
	}
	_objectSprite.setTexture(_objectText);
	this->_objectSprite.setPosition(initPosition);
	this->_initPosition = initPosition;
	_isDropped = false;

	_type = 0;
}

Object::Object()
{
	_creationDate = (time_t)0;
	_isDropped = false;
}

Object::~Object()
{

}

bool Object::update()
{
	return true;
}

void Object::setDropped(bool dropped) {
	_isDropped = dropped;
	_objectSprite.setScale(sf::Vector2f(0.1, 0.1));
}

void Object::resetAngle() {
	_objectSprite.setRotation(3.1415f);
}

sf::Vector2f Object::getPosition() const {
	return _objectSprite.getPosition();
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite s = _objectSprite;
	s.setTexture(_objectText);
	target.draw(s);
}

sf::FloatRect Object::getHitbox() const 
{
	sf::Sprite s = _objectSprite;
	s.setTexture(_objectText);
	return s.getGlobalBounds();
}

int Object::getType() const {
	return _type;
}