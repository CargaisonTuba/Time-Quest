#pragma once
#include "../NPC.h"

class Ally : public NPC
{
public:
	Ally(std::string texturePath, float defaultLife, sf::Vector2f initPosition);
	~Ally();

	bool update(sf::Vector2f playerPos, std::vector<Tile> const& _tiles, std::vector<ThrowedObject>& throwableObjectsList, float const& dt);

};
