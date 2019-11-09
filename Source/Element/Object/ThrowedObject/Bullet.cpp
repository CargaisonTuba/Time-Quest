#include <ctime>
#include "Bullet.h"
#include <iostream>

Bullet::Bullet(sf::Vector2f throwerPosition, sf::Vector2f direction, float damages) :
	ThrowedObject (throwerPosition, direction, damages)
{
	_body.setFillColor(sf::Color::Black);
	_body.setOutlineThickness(0);
	_body.setRadius(1);
}

Bullet::~Bullet()
{

}

