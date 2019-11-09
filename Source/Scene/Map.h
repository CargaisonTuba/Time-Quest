#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

#include "../Entity/Player.h"
#include "../Entity/NPC/Ennemy.h"
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

	void update(Player &player, Cursor curseur, sf::View &view, float const& dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<ThrowedObject> getThrowableObjectsList();

private:
	//Entités
	std::vector<Ennemy> _ennemies;

	//TileMap
	sf::VertexArray _vertices;
	sf::Texture _tileset;

	std::vector<Tile> _tiles;

	std::vector<ThrowedObject> _throwableObjectsList;
	
	sf::RectangleShape _playerLifebar;	//sert de variable transitoire pour dessiner l'HUD
};
