#include "Outfit.h"

Outfit::Outfit(sf::Vector2f pos, std::string path) : Object("Time-Quest/Source/assets/" + path, pos)
{
	_type = OUTFIT;
}

Outfit::~Outfit() {

}