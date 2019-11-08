#include <ctime>
#include "Bullet.h"
#include <iostream>


Bullet::Bullet(sf::Vector2f throwerPosition, sf::Vector2f direction, float damages) :
	ThrowedObject (throwerPosition, direction)
{
	std::cout << "new bullet\n";
	_damages = damages;
}

Bullet::~Bullet()
{

}
