#pragma once

#include <SFML/Graphics.hpp>

#include "Object.h"

class ThrowedObject : public Object
{
public:
	ThrowedObject(sf::Vector2f throwerPosition, sf::Vector2f direction, int range, float damages = 0);
	ThrowedObject();
	~ThrowedObject();

	float getDamages() const;
	bool update(float const& dt);

protected:
	sf::Clock _clock;
	float _damages;
	int _range;
};

