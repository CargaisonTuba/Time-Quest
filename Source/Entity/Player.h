#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(std::string texturePath, float defaultLife, sf::Vector2f initPosition);
	~Player();

	sf::Vector2f getPosition() const;

	void update(Cursor const& curseur, std::vector<std::vector<Tile>> const& _tiles, std::vector<ThrowedObject>& throwableObjectsList, std::vector<Object*> &droppedObjectsList, float const& dt);
	bool fire(std::vector<ThrowedObject>& throwableObjectsList, sf::Vector2f shootDirection, std::vector<std::vector<Tile>> const& _tiles);


private:
	bool _justPressed;	//pour savoir si on vient de changer l'item selectionné
	bool _justChanged;	//pour savoir si on vient de change d'arme
	bool _justLoot;	//pour savoir si on vient de loot un objet au sol

	std::vector<Object*> _inventory;
	int _inventoryIndex;
	int tempX;
	int tempY;
};
