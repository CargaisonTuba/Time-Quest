#pragma once
#include "Entity.h"
#include "../Scene/Map.h"

class Player : public Entity
{
public:
	Player(std::string texturePath, int defaultLife, sf::Vector2f initPosition);
	~Player();

	sf::Vector2f getPosition() const;
	void update();
	bool fire(Map &map);
};
