#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

#include "../Entity/Player.h"
#include "../Entity/NPC/Ennemy.h"
#include"../Entity/NPC/Ally/Mate.h"
#include "../Arme.h"

#include "../HUD/Cursor.h"

#include "../Element/Tile.h"
#include "../Element/Object/ThrowedObject.h"
#include "../Element/Object/DroppedObject.h"
#include "../Element/Object/SolidObject.h"


class Map : public sf::Drawable
{
public:
	Map();
	~Map();

	void update(Player &player, Cursor &curseur, sf::View &view, float const& dt);
	sf::Vector2f getPlayerSpawn() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<ThrowedObject> getThrowableObjectsList();


private:
	//Entités
	std::vector<Ennemy> _ennemies;
	std::vector<Mate> _mates;

	//TileMap
	sf::VertexArray _vertices;
	sf::Texture _tileset;
	sf::Vector2f _mapSize;

	std::vector<Tile> _tiles;
	sf::Vector2f _playerSpawn;

	std::vector<ThrowedObject> _throwableObjectsList;
	
	sf::RectangleShape _playerLifebar;	//sert de variable transitoire pour dessiner l'HUD
};
