#include <ctime>
#include "Bullet.h"
#include <iostream>

Bullet::Bullet(float angle, std::string texturePath, sf::Vector2f throwerPosition, sf::Vector2f direction, int range, float damages) :
	ThrowedObject (texturePath, throwerPosition, direction, range, damages)
{
	_objectSprite.setRotation(angle);
	_objectSprite.setScale(0.5, 0.5);
}

Bullet::~Bullet()
{

}

