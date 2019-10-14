#include "Tile.h"

Tile::Tile(sf::Vector2f coords, bool wall) {
	_coords = coords;
	_wall = wall;
}

Tile::~Tile() {

}
