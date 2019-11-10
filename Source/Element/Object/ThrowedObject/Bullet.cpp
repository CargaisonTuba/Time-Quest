#include <ctime>
#include "Bullet.h"
#include <iostream>

Bullet::Bullet(sf::Vector2f throwerPosition, sf::Vector2f direction, int range, float damages) :
	ThrowedObject (throwerPosition, direction, range, damages)
{
	_body.setFillColor(sf::Color::Black);
	_body.setOutlineThickness(0);
	_body.setRadius(2);
}

Bullet::~Bullet()
{

}

