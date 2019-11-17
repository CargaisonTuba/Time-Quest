#pragma once
#include "NPC.h"
#include <vector>
#include "Ally/Mate.h"

class Mate;
class Ennemy : public NPC
{
public:
	Ennemy(std::string texturePath, float defaultLife, sf::Vector2f initPosition);
	~Ennemy();

	bool update(std::vector<Mate>& _mates, sf::Vector2f playerPos, std::vector<Tile> const& _tiles, std::vector<ThrowedObject>& throwableObjectsList, float const& dt);
	
private:
	//static int compteur;
	//int _ID;
	int _detectRange;
};
