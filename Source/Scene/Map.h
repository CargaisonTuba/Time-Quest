#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

#include "../Entity/Player.h"
#include "../Entity/NPC/Ennemy.h"
#include"../Entity/NPC/Ally/Mate.h"
#include "../Arme.h"
#include "../Element/Object/Medkit.h"

#include "../HUD/Cursor.h"

#include "../Element/Tile.h"
#include "../Element/Object/ThrowedObject.h"

#include "../Quest.h"


class Map : public sf::Drawable
{
public:
	Map();
	~Map();

	void update(Player &player, Cursor &curseur, sf::View &view, float const& dt);
	sf::Vector2f getPlayerSpawn() const;
	std::vector<ThrowedObject> getThrowableObjectsList() const;
	//std::vector<Object> getDroppedObjectsList() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	//Entités
	std::vector<Ennemy> _ennemies;
	std::vector<Mate> _mates;

	//TileMap
	sf::VertexArray _vertices;
	sf::Texture _tileset;
	sf::Vector2f _mapSize;

	std::vector<std::vector<Tile>> _tiles;
	sf::Vector2f _playerSpawn;

	std::vector<ThrowedObject> _throwableObjectsList;
	std::vector<Object*> _droppedObjectsList;
	
	sf::RectangleShape _playerLifebar;	//sert de variable transitoire pour dessiner l'HUD

	//Quetes
	std::vector<Quest> _quests;
};
