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

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite s = _objectSprite;
	s.setTexture(_objectText);
	target.draw(s);
}

sf::FloatRect Object::getHitbox() const 
{
	return _objectSprite.getGlobalBounds();
}