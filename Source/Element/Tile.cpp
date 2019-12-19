#include "Tile.h"
#include <iostream>

Tile::Tile(sf::Vector2f coords, int status) {
	_coords = coords;
	_status = status;
}

Tile::Tile()
{

}

Tile::~Tile() {

}

bool Tile::isWall() const {
	return _status == WALL;
}

sf::FloatRect Tile::getHitbox() const {
	sf::FloatRect hb(_coords, sf::Vector2f(TSIZE, TSIZE));
	return hb;
}