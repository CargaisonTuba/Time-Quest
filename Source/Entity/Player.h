#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(std::string texturePath, int defaultLife, sf::Vector2f initPosition);
	~Player();

	sf::Vector2f getPosition() const;
	//Le joueur a une arme comme attribut
	
	void setWeapon(Arme);
	Arme getWeapon();
	void update(Cursor curseur, std::vector<Tile> _tiles);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Arme _weaponJ;
};
