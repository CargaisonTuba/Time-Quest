#pragma once
#include "NPC.h"

class Ennemy : public NPC
{
public:
	Ennemy(std::string texturePath, int defaultLife, sf::Vector2f initPosition);
	~Ennemy();

	void update();
};
