#include <ctime>
#include "Bullet.h"


Bullet::Bullet(sf::Vector2f playerPosition, sf::Vector2f direction)
{
	this->_creationDate = std::time(0);
	this->_direction = direction;
	this->body.setPosition(playerPosition);
}

Bullet::~Bullet()
{

}

bool Bullet::update()
{
	if (std::time(0) - this->_creationDate > 5)
	{
		return false;
	}
	this->body.move(_direction);
	return true;
}
