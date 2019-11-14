#include "Tile.h"
#include <iostream>

Tile::Tile(sf::Vector2f coords, int status) {
	_coords = coords;
	_status = status;
}

Tile::~Tile() {

}

bool Tile::isWall() const {
	return _status == WALL;
}

sf::FloatRect Tile::getHitbox() const {
	//std::cout << "tile at " << _coords.x << ";" << _coords.y << "\n";
	sf::FloatRect hb(_coords, sf::Vector2f(30, 30));
	return hb;
}