#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

#include "../Entity/Player.h"
#include "../Entity/NPC/Ennemy.h"


#include "../Element/Tile.h"
#include "../Element/Object/ThrowedObject.h"
#include "../Element/Object/DroppedObject.h"
#include "../Element/Object/SolidObject.h"

class Map : public sf::Drawable
{
public:
	Map();
	~Map();
	
	void update(Player &player);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	//Entités
	std::vector<Ennemy> _ennemies;

	//TileMap
	sf::VertexArray _vertices;
	sf::Texture _tileset;

	std::vector<Tile> _tiles;
};
