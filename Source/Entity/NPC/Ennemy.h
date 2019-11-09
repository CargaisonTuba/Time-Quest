#pragma once
#include "NPC.h"

class Ennemy : public NPC
{
public:
	Ennemy(std::string texturePath, float defaultLife, sf::Vector2f initPosition);
	~Ennemy();

	bool update(sf::Vector2f playerPos, std::vector<ThrowedObject>& throwableObjectsList, float const& dt);
};
