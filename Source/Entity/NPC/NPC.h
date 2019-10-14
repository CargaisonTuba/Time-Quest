#pragma once
#include "../Entity.h"

class NPC : public Entity
{
public:
	NPC(std::string texturePath, int defaultLife, sf::Vector2f initPosition);
	~NPC();
};
