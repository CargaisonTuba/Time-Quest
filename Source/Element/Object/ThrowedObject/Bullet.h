#pragma once

#include <ctime>
#include "../ThrowedObject.h"


class Bullet : public ThrowedObject
{
public:
	Bullet(sf::Vector2f throwerPosition, sf::Vector2f direction);
	~Bullet();

	bool update();

	

private:
	std::time_t _creationDate;
	sf::Vector2f _direction;
	sf::Clock _clock;
	
};
