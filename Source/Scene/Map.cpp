#include <iostream>

#include "Map.h"
#include "../Element/Object/ThrowedObject/Bullet.h"

Map::Map() {
	//On charge la map depuis le fichier

	std::vector<int> level;	//contient tous les ID des tiles

	//On remplit ce tableau avec les valeurs du fichier map.txt, sortit tout droit de l'éditeur
	std::ifstream mapFile("Time-Quest/Source/map.txt");
	if(!mapFile)
		std::cerr << "[Erreur] : impossible d'ouvrir map.txt\n";
	else {
		std::cout << "Fichier ouvert. Lecture...\n";
		int tileID;
		while (mapFile >> tileID) {
			level.push_back(tileID);
			std::cout << "Nouvelle tile\n";
		}
	}

	sf::Vector2u tileSize(30, 30);
	unsigned int width = 12, height = 8;	//Le niveau est découpé en 1 carré.
	std::cout << level.size() << std::endl;

	const std::string path = "Time-Quest/Source/assets/tilesheet.png";

	//on charge les textures
	if (!_tileset.loadFromFile(path))
		std::cout << "[Erreur] : chargement " << path << std::endl;

	_vertices.setPrimitiveType(sf::Quads);
	_vertices.resize(width * height * 4);

	//Remplissage du tableau
	for(unsigned int i = 0; i < width; i++)
		for (unsigned int j = 0; j < height; j++) {
			int tileNumber = level[i + j * width];

			int tu = tileNumber % (_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (_tileset.getSize().x / tileSize.x);

			//std::cout << "TID = " << tileNumber << " / tu = " << tu << " / tv = " << tv << std::endl;

			sf::Vertex* quad = &_vertices[(i + j * width) * 4];

			quad[0].position = sf::Vector2f((float)(i * tileSize.x), (float)(j * tileSize.y));
			quad[1].position = sf::Vector2f((float)((i + 1.) * tileSize.x), (float)(j * tileSize.y));
			quad[2].position = sf::Vector2f((float)((i + 1) * tileSize.x), (float)((j + 1) * tileSize.y));
			quad[3].position = sf::Vector2f((float)(i * tileSize.x), (float)((j + 1) * tileSize.y));

			quad[0].texCoords = sf::Vector2f((float)(tu * tileSize.x), (float)(tv * tileSize.y));
			quad[1].texCoords = sf::Vector2f((float)((tu + 1) * tileSize.x), (float)(tv * tileSize.y));
			quad[2].texCoords = sf::Vector2f((float)((tu + 1) * tileSize.x), (float)((tv + 1) * tileSize.y));
			quad[3].texCoords = sf::Vector2f((float)(tu * tileSize.x), (float)((tv + 1) * tileSize.y));

			_tiles.push_back(Tile(sf::Vector2f(i * 30, j * 30), (tileNumber == 0)));
			std::cout << "New tile at " << i << ";" << j << " wall=" << _tiles[_tiles.size() - 1].isWall() << std::endl;
		}

	//On initialise les ennemis
	for (unsigned int i = 0; i < 10; i++)
		_ennemies.push_back(Ennemy("Time-Quest/Source/assets/soldatAllemand40.png", 20, sf::Vector2f(rand() % 100, rand() % 100)));
}

Map::~Map() {

}

void Map::update(Player& player, Cursor curseur, sf::View &view) {
	player.update(curseur, _tiles, _throwableObjectsList);

	for (unsigned int i = 0; i < _ennemies.size(); i++)
		_ennemies[i].update(player.getPosition());
  
	for (unsigned int i = 0; i < _throwableObjectsList.size(); i++)
	{
		bool cond = _throwableObjectsList[i].update();
		//_throwableObjectsList[i].getBody().move(_throwableObjectsList[i].getDirection());

		if (!cond)
			_throwableObjectsList.erase(_throwableObjectsList.begin() + i);
	}

	_playerLifebar = player.getLifebar();
  
	view.setCenter(player.getPosition());
}

std::vector<ThrowedObject> Map::getThrowableObjectsList()
{
	return this->_throwableObjectsList;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//On dessine la map
	states.texture = &_tileset;
	target.draw(_vertices, states);

	//on dessine les pnjs
	for (unsigned int i = 0; i < _ennemies.size(); i++)
		target.draw(_ennemies[i]);
  
	//On dessines les throwableObjects
	for (unsigned int i = 0; i < _throwableObjectsList.size(); i++)
		_throwableObjectsList[i].draw(target, states);

	//dessin de l'HUD
	sf::View baseView = target.getView();
	target.setView(target.getDefaultView());
	target.draw(_playerLifebar);
	target.setView(baseView);
}
