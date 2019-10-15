#pragma once
#include "Entity.h"
#include "../Arme.h"

class Player : public Entity
{
public:
	Player(std::string texturePath, int defaultLife, sf::Vector2f initPosition);
	~Player();

	sf::Vector2f getPosition() const;
	//Le joueur a une arme comme attribut
	/*Arme _armeJ;
	void setWeapon(Arme);*/
	void update();
};
