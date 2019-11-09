#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(std::string texturePath, float defaultLife, sf::Vector2f initPosition);
	~Player();

	sf::Vector2f getPosition() const;

	void update(Cursor curseur, std::vector<Tile> _tiles, std::vector<ThrowedObject> &throwableObjectsList, float const& dt);
};
