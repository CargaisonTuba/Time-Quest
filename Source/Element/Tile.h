#pragma once
#include "Element.h"

class Tile : public Element
{
public:
	Tile(sf::Vector2f coords, bool wall);
	~Tile();

	bool isWall() const;
	sf::FloatRect getHitbox() const;

private:
	sf::Vector2f _coords;
	bool _wall;
};

