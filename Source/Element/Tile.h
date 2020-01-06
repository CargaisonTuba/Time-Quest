#pragma once
#include "Element.h"

#define WALL 0
#define WATER 1
#define NORMAL 2

#define TSIZE 30.f

class Tile : public Element
{
public:
	Tile(sf::Vector2f coords, int status);
	Tile();
	~Tile();

	bool isWall() const;
	sf::FloatRect getHitbox() const;

private:
	sf::Vector2f _coords;
	int _status;
};

