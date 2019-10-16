#include "Tile.h"
#include <iostream>

Tile::Tile(sf::Vector2f coords, bool wall) {
	_coords = coords;
	_wall = wall;
}

Tile::~Tile() {

}

bool Tile::isWall() const {
	return _wall;
}

sf::FloatRect Tile::getHitbox() const {
	//std::cout << "tile at " << _coords.x << ";" << _coords.y << "\n";
	sf::FloatRect hb(_coords, sf::Vector2f(30, 30));
	return hb;
}