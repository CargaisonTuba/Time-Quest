#pragma once
#include "Ally.h"
#include <vector>
#include "../Ennemy.h"

class Ennemy;
class Mate : public Ally
{
public:
	Mate(std::string texturePath, float defaultLife, sf::Vector2f initPosition, float id, std::string msg);
	~Mate();

	bool update(std::vector<Ennemy>& _ennemies, sf::Vector2f playerPos, std::vector<Tile> const& _tiles, std::vector<ThrowedObject>& throwableObjectsList, std::vector<Object*>& droppedObjectsList, std::vector<Mate> &mates, float const& dt);
	void follow(sf::Vector2f playerPos, std::vector<Tile> const& _tiles, std::vector<Mate> &mates);
	// 
private:
	//static int compteur;
	//int _ID;
	float _detectRange, _distPlayer;
	bool _follow;
	bool _fPressed;
	std::string _msg;	//dialogues
};

