#pragma once

#include <ctime>
#include <math.h>
#include <stdlib.h>
#include <iostream>

#include "../ThrowedObject.h"
#include "../../../Entity/Entity.h"

class GhostBullet
{
public:
	GhostBullet(float angle, sf::Vector2f throwerPosition, sf::Vector2f direction, Entity cible);
	GhostBullet();
	~GhostBullet();
	bool travel(std::vector<std::vector<Tile>> _tiles);

private:
	std::time_t _creationDate;
	sf::Vector2f _direction;
	sf::Clock _clock;
	sf::Sprite _ghostSprite;
	sf::Vector2f _initPos;
	Entity _cible;
};


