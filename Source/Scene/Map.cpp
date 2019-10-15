#include "Map.h"

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

			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

			_tiles.push_back(Tile(sf::Vector2f(i, j), (tileNumber == 0)));
			std::cout << "New tile at " << i << ";" << j << " wall=" << _tiles[_tiles.size() - 1].isWall() << std::endl;
		}
}

Map::~Map() {

}

void Map::update(Player& player) {
	player.update();
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//On dessine la map
	states.texture = &_tileset;
	target.draw(_vertices, states);

	//on dessine les pnjs
	for (unsigned int i = 0; i < _ennemies.size(); i++)
		target.draw(_ennemies[i]);

}
