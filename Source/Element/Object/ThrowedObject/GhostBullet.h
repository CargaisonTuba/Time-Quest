#pragma once

#include <ctime>
#include <math.h>
#include <stdlib.h>
#include <iostream>

#include "../ThrowedObject.h"


class GhostBullet
{
public:
	GhostBullet(float angle, sf::Vector2f throwerPosition, sf::Vector2f direction, sf::FloatRect cible, sf::Vector2f _iblePos);
	GhostBullet();
	~GhostBullet();
	bool travel(std::vector<std::vector<Tile>> _tiles);

private:
	std::time_t _creationDate;
	sf::Vector2f _direction;
	sf::Clock _clock;
	sf::Texture _ghostText;
	sf::Sprite _ghostSprite;
	sf::Vector2f _initPos;
	sf::FloatRect _cibleHitbox;
	sf::Vector2f _ciblePos;
};


