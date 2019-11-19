#pragma once
#include "../Entity.h"

class NPC : public Entity
{
public:
	NPC(std::string texturePath, float defaultLife, sf::Vector2f initPosition);
	~NPC();

	void killNPC(std::vector<Object*>& droppedObjects);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::Vector2f playerPos);
};
