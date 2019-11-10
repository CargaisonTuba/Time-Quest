#include <iostream>

#include "Map.h"
#include "../Element/Object/ThrowedObject/Bullet.h"

Map::Map() {
	//On charge la map depuis le fichier
	std::cout << "\x1B[33m[Info]\x1B[0m : Chargement de la map...\n";

	std::vector<int> level;	//contient tous les ID des tiles

	//On remplit ce tableau avec les valeurs du fichier map.txt, sortit tout droit de l'éditeur
	std::ifstream mapFile("Time-Quest/Source/map.txt");
	if(!mapFile)
		std::cerr << "\x1B[31m[Erreur]\x1B[0m : impossible d'ouvrir map.txt\n";
	else {
		int tileID;
		while (mapFile >> tileID) {
			level.push_back(tileID);
		}
	}

	sf::Vector2u tileSize(30, 30);
	unsigned int width = 12, height = 8;	//Le niveau est découpé en 1 carré.
	std::cout << "\x1B[33m[Info]\x1B[0m : " << level.size() << " tiles en cours de chargement..." << std::endl;

	const std::string path = "Time-Quest/Source/assets/tilesheet.png";

	//on charge les textures
	if (!_tileset.loadFromFile(path))
		std::cout << "\x1B[31m[Erreur]\x1B[0m : impossible de charger " << path << std::endl;

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

			_tiles.push_back(Tile(sf::Vector2f((float)i * 30, (float)j * 30), (tileNumber == 0)));
		}

	//On initialise les ennemis
	std::cout << "\x1B[33m[info]\x1B[0m : chargement des entites...\n";
	for (unsigned int i = 0; i < 5; i++)
		_ennemies.push_back(Ennemy("Time-Quest/Source/assets/soldatAllemand40.png", 100, sf::Vector2f((float)(rand() % 200), (float)(rand() % 200))));
	std::cout << "\x1B[32m[OK]\x1B[0m : " << _ennemies.size() << " entites chargees\n";
	std::cout << "\x1B[32m[OK]\x1B[0m : Map chargee\n";
}

Map::~Map() {

}

void Map::update(Player& player, Cursor &curseur, sf::View &view, float const& dt) {
	player.update(curseur, _tiles, _throwableObjectsList, dt);

	for (unsigned int i = 0; i < _ennemies.size(); i++)
		if (_ennemies[i].update(player.getPosition(), _throwableObjectsList, dt))	//si l'ennemi est mort, on le retire de la liste
			_ennemies.erase(_ennemies.begin() + i);
  
	for (unsigned int i = 0; i < _throwableObjectsList.size(); i++)
	{
		bool cond = _throwableObjectsList[i].update(dt);

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
