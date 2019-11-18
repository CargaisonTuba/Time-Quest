#pragma once
#include "Ally.h"
#include <vector>
#include "../Ennemy.h"

class Ennemy;
class Mate : public Ally
{
public:
	Mate(std::string texturePath, float defaultLife, sf::Vector2f initPosition);
	~Mate();

	bool update(std::vector<Ennemy>& _ennemies, sf::Vector2f playerPos, std::vector<Tile> const& _tiles, std::vector<ThrowedObject>& throwableObjectsList, float const& dt);
	void follow(sf::Vector2f playerPos, std::vector<Tile> const& _tiles);
	// 
private:
	//static int compteur;
	//int _ID;
	float _detectRange, _distPlayer;
	bool _follow;
};

