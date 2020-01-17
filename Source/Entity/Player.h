#pragma once
#include "Entity.h"
#include "NPC/Ally/Mate.h"
#include "../HUD/Hud.h"

#define NEXT_MAP 1

class Player : public Entity
{
public:
	Player(std::string texturePath, float defaultLife, sf::Vector2f initPosition);
	~Player();

	sf::Vector2f getPosition() const;
	void resetInventory();
	int update(Cursor const& curseur, std::vector<std::vector<Tile>> const& _tiles, std::vector<ThrowedObject>& throwableObjectsList, std::vector<Object*> &droppedObjectsList, std::vector<Mate>& mates, Hud& hud, float const& dt);

private:
	bool _justPressed;	//pour savoir si on vient de changer l'item selectionné
	bool _justChanged;	//pour savoir si on vient de change d'arme
	bool _a_justPressed;
	bool _justLoot;	//pour savoir si on vient de loot un objet au sol

	std::vector<Object*> _inventory;
	int _inventoryIndex;
};
