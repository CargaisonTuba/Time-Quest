#include <ctime>
#include "Bullet.h"
#include <iostream>


Bullet::Bullet(sf::Vector2f throwerPosition, sf::Vector2f direction)
{
	this->_creationDate = std::time(0);
	this->_direction = direction;
	this->_body.setPosition(throwerPosition);
	this->_body.setFillColor(sf::Color::Black);
	this->_body.setOutlineColor(sf::Color::White);
	this->_body.setOutlineThickness(1);
	this->_body.setRadius(5);
}

Bullet::~Bullet()
{

}

bool Bullet::update()
{
	if (_clock.getElapsedTime() > sf::seconds(5.f))
	{
		std::cout << "hey";
		return false;
	}
	//std::cout << _direction.x << " et " << _direction.y << "\n";
	//sf::Vector2f newPosition(_direction.x + _body.getPosition().x, _direction.y + _body.getPosition().y);
	std::cout << "prout";
	_body.move(sf::Vector2f(_direction.x*100,_direction.y*100));
	//_body.setPosition(newPosition);
	return true;
}



