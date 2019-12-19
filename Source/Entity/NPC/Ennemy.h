#pragma once
#include "NPC.h"
#include <vector>
#include "Ally/Mate.h"

class Mate;
class Ennemy : public NPC
{
public:
	Ennemy(std::string texturePath, float defaultLife, sf::Vector2f initPosition, float id);
	~Ennemy();

	int update(std::vector<Mate>& _mates,Entity player, std::vector<std::vector<Tile>> const& _tiles, std::vector<ThrowedObject>& throwableObjectsList, std::vector<Object*>& droppedObjects, float const& dt);
	
private:
	//static int compteur;
	//int _ID;
	int _detectRange;
};
