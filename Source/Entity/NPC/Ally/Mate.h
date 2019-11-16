#pragma once
#include "Ally.h"
#include "../Ennemy.h"
class Mate : public Ally
{
public:
	Mate(std::string texturePath, float defaultLife, sf::Vector2f initPosition);
	~Mate();

	bool update(std::vector<Ennemy> _ennemies, sf::Vector2f playerPos, std::vector<Tile> const& _tiles, std::vector<ThrowedObject>& throwableObjectsList, float const& dt);

private:
	//static int compteur;
	//int _ID;
	int _detectRange;
};

