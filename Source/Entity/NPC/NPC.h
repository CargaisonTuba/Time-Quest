#pragma once
#include "../Entity.h"

class NPC : public Entity
{
public:
	NPC(std::string texturePath, float defaultLife, sf::Vector2f initPosition);
	~NPC();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update();
};
