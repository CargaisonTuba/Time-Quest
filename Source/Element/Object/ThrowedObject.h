#pragma once

#include <SFML/Graphics.hpp>
#include "../Tile.h"
#include "Object.h"
#include <SFML/Audio.hpp>

class ThrowedObject : public Object
{
public:
	ThrowedObject(std::string texturePath, sf::Vector2f throwerPosition, sf::Vector2f direction, int range, float damages = 0);
	ThrowedObject();
	~ThrowedObject();

	sf::Vector2f getDirection() const;
	float getDamages() const;
	bool update(float const& dt, std::vector<Tile> const& _tiles);

protected:
	sf::SoundBuffer _impactBuffer;
	sf::Sound _impactSound;
	sf::Clock _clock;
	float _damages;
	int _range;
	sf::Vector2f _position, _direction;
};

