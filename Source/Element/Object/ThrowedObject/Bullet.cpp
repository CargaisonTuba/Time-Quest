#include <ctime>
#include "Bullet.h"
#include <iostream>


Bullet::Bullet(sf::Vector2f throwerPosition, sf::Vector2f direction) :
	ThrowedObject (throwerPosition, direction)
{
	
}

Bullet::~Bullet()
{

}
