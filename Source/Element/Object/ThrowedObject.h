#pragma once

#include <SFML/Graphics.hpp>

#include "Object.h"

class ThrowedObject : public Object
{
public:
	ThrowedObject(sf::Vector2f throwerPosition, sf::Vector2f direction);
	ThrowedObject();
	~ThrowedObject();

	bool update();
protected:
	sf::Clock _clock;
};

