#pragma once
#include <time.h>
#include "../ThrowedObject.h"

class Grenade : public ThrowedObject
{
public:
	Grenade(float angle, std::string texturePath, sf::Vector2f throwerPosition, sf::Vector2f direction, int range, float damages);
	~Grenade();

private:
	std::time_t _creationDate;
	sf::Vector2f _direction;
	sf::Clock _clock;
	float _damages;
};

