#pragma once
#include "Entity.h"
#include "../Element/Object/ThrowedObject.h"
#include "../Element/Object/ThrowedObject/Bullet.h"


class Player : public Entity
{
public:
	Player(std::string texturePath, int defaultLife, sf::Vector2f initPosition);
	~Player();

	sf::Vector2f getPosition() const;
	void update(std::vector<ThrowedObject> &throwableObjectsList, sf::RenderWindow& window);
	bool fire(std::vector<ThrowedObject> &throwableObjectsList, sf::RenderWindow& window);
	
};
