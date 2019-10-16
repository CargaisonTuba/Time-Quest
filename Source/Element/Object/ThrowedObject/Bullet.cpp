#include <ctime>
#include "Bullet.h"


Bullet::Bullet(sf::Vector2f throwerPosition, sf::Vector2f direction)
{
	this->_creationDate = std::time(0);
	this->_direction = direction;
	this->_body.setPosition(throwerPosition);
	this->_body.setFillColor(sf::Color::Black);
	this->_body.setOutlineColor(sf::Color::White);
	this->_body.setRadius(2);
}

Bullet::~Bullet()
{

}

bool Bullet::update()
{
	if (_clock.getElapsedTime() > sf::seconds(5.f))
	{
		return false;
	}
	this->_body.move(_direction);
	return true;
}

