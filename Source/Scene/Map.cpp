#include <iostream>

#include "Map.h"
#include "../Element/Object/ThrowedObject/Bullet.h"

Map::Map() {

}

Map::~Map() {
	for (unsigned int i = 0; i < _droppedObjectsList.size(); i++) {
		delete _droppedObjectsList[i];
		_droppedObjectsList[i] = 0;
	}
}

void Map::load(std::string mapPath) 
{
	//On charge la map depuis le fichier spécifié
	std::cout << "\x1B[33m[Info]\x1B[0m : Chargement de la map \x1B[33m" << mapPath << "\x1B[0m...\n";

	_waitingToChangeMap = false;
	_justLoaded = true;
	_ennemies.clear();
	_mates.clear();
	_tiles.clear();
	_vertices.clear();
	_throwableObjectsList.clear();
	_droppedObjectsList.clear();
	_quests.clear();

	std::vector<int> level;	//contient tous les ID des tiles
	sf::Vector2u tileSize(30, 30);
	unsigned int width = 0, height = 0;	//Le niveau est découpé en 1 carré.

	std::string currentOperation = "";
	std::string tilesheet_path = "", mate_texture = "", ennemy_texture = "", quest_path = "", cible_texture = "";
	_nextMapPath = "no-next-map";

	//On remplit ce tableau avec les valeurs du fichier map.txt, sortit tout droit de l'éditeur
	std::ifstream mapFile("Time-Quest/Source/" + mapPath);
	if (!mapFile)
		std::cerr << "\x1B[31m[Erreur]\x1B[0m : impossible d'ouvrir \x1B[31m" << mapPath << "\x1B[0m...\n";
	else {
		int tileID;
		int bossID = -1;
		while (mapFile >> currentOperation) {	//on charge les infos de la map dans le jeu
			if (currentOperation == "#tilesheet")
				mapFile >> tilesheet_path;

			else if (currentOperation == "#playertexture")
				mapFile >> _playerTextPath;

			else if (currentOperation == "#matetexture")
				mapFile >> mate_texture;

			else if (currentOperation == "#ennemytexture")
				mapFile >> ennemy_texture;
			else if (currentOperation == "#cibletexture")
				mapFile >> cible_texture;

			else if (currentOperation == "#mapsize") {
				mapFile >> width;
				mapFile >> height;
			}
			else if (currentOperation == "#playerspawn") {
				mapFile >> _playerSpawn.x;
				mapFile >> _playerSpawn.y;
			}
			else if (currentOperation == "#bossID") {
				mapFile >> bossID;
				std::cout << bossID << std::endl;
			}
			else if (currentOperation == "#nextmap") {
				mapFile >> _nextMapPath;
			}
			else if (currentOperation == "#quest") {
				mapFile >> quest_path;
			}
			else if (currentOperation == "#ennemy") {
				float eLife = 0;
				float eID = -2;
				sf::Vector2f ePos(0, 0);
				mapFile >> eLife;
				mapFile >> ePos.x;
				mapFile >> ePos.y;
				mapFile >> eID;
				_ennemies.push_back(Ennemy(ennemy_texture, eLife, ePos, eID));
			}
			else if (currentOperation == "#mate")
			{
				float eLife = 0;
				float id = -2;
				sf::Vector2f ePos(0, 0);
				std::string mateMsg;
				std::string mateNom;
				mapFile >> eLife;
				mapFile >> ePos.x;
				mapFile >> ePos.y;
				mapFile >> id;
				mapFile.ignore();
				std::getline(mapFile, mateMsg);
				std::getline(mapFile, mateNom);
				bool isBoss = false;
				if (id == bossID)
					isBoss = true;
				_mates.push_back(Mate(mate_texture, eLife, ePos, id, mateMsg, mateNom, isBoss));
			}
			else if (currentOperation == "#cible")
			{
				float eLife = 0;
				float id = -2;
				sf::Vector2f ePos(0, 0);
				std::string cibleMsg;
				std::string cibleNom;
				mapFile >> eLife;
				mapFile >> ePos.x;
				mapFile >> ePos.y;
				mapFile >> id;
				mapFile.ignore();
				std::getline(mapFile, cibleMsg);
				std::getline(mapFile, cibleNom);
				bool isBoss = false;
				if (id == bossID)
					isBoss = true;
				_mates.push_back(Mate(cible_texture, eLife, ePos, id, cibleMsg, cibleNom, isBoss));
			}

			else if (currentOperation == "#gun")
			{
				sf::Vector2f pos;
				std::string type;
				mapFile >> type;
				mapFile >> pos.x;
				mapFile >> pos.y;
				_droppedObjectsList.push_back(new Arme(type, pos, true));
			}

			else if (currentOperation == "#medkit")
			{
				sf::Vector2f pos;
				mapFile >> pos.x;
				mapFile >> pos.y;
				_droppedObjectsList.push_back(new Medkit(pos));
			}
			else if (currentOperation == "#outfit")
			{
				sf::Vector2f pos;
				std::string path;
				mapFile >> pos.x;
				mapFile >> pos.y;
				mapFile.ignore();
				std::getline(mapFile, path);
				_droppedObjectsList.push_back(new Outfit(pos, path));
			}
			
			else if (currentOperation == "#tiles") {
				while (mapFile >> tileID)
					level.push_back(tileID);
			}
			currentOperation = "";
		}
	}

	if (width == 0 && height == 0)
		std::cerr << "\x1B[31m[Erreur]\x1B[0m : map vide ou erreur de lecture\n";

	std::cout << "\x1B[33m[Info]\x1B[0m : " << level.size() << " tiles en cours de chargement..." << std::endl;

	const std::string path = "Time-Quest/Source/assets/" + tilesheet_path;

	//on charge les textures
	if (!_tileset.loadFromFile(path))
		std::cout << "\x1B[31m[Erreur]\x1B[0m : impossible de charger " << path << std::endl;

	_vertices.setPrimitiveType(sf::Quads);
	_vertices.resize(width * height * 4);

	//Remplissage du tableau
	for (unsigned int i = 0; i < width; i++)
	{
		std::vector<Tile> row;
		for (unsigned int j = 0; j < height; j++)
		{
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

			int status = NORMAL;
			if (tileNumber == 0 || tileNumber == 6)
				status = WALL;
			if (tileNumber == 1)
				status = WATER;

			row.push_back(Tile(sf::Vector2f((float)i * TSIZE, (float)j * TSIZE), status));
		}
		_tiles.push_back(row);
	}

	std::cout << "\x1B[32m[OK]\x1B[0m : " << _ennemies.size() + _mates.size() << " entites chargees\n";
	std::cout << "\x1B[32m[OK]\x1B[0m : " << _droppedObjectsList.size() << " objets charges\n";
	std::cout << "\x1B[32m[OK]\x1B[0m : Map chargee\n";

	_mapSize.x = (float)width;
	_mapSize.y = (float)height;

	//Quêtes
	std::cout << "\x1B[33m[Info]\x1B[0m : Chargement des quetes..." << std::endl;

	std::ifstream questFile("Time-Quest/Source/" + quest_path);
	if (!questFile)
		std::cerr << "\x1B[31m[Erreur]\x1B[0m : impossible d'ouvrir quest.txt\n";
	else {
		while (questFile >> currentOperation) {	//on charge les infos de la map dans le jeu
			if (currentOperation == "#quest") {
				std::string sqName = "e", sqType;
				std::vector<std::string> sqList;
				std::vector<int> qList;
				int qType;

				questFile.ignore();
				std::getline(questFile, sqName);

				questFile >> sqType;
				if (sqType == "kill")
					qType = TYPE_KILL;
				else
					qType = TYPE_FIND;


				currentOperation = "";
				while (questFile >> currentOperation) {
					if (currentOperation != "\n")
						sqList.push_back(currentOperation);
					else
						break;
				}
				
				for (int k = 0; k < sqList.size(); k++)
					qList.push_back(std::stoi(sqList[k]));

				std::cout << "->" << sqName << std::endl;

				_quests.push_back(Quest(sqName, qType, qList));
				std::cout << "\n";
			}

			std::cout << currentOperation << std::endl;
			currentOperation = "";
		}
	}
	std::cout << "\x1B[32m[OK]\x1B[0m : " << _quests.size() << " quetes chargees\n";

	std::cout << "\x1B[32m[lancement du jeu !]\x1B[0m\n";
}

void Map::loadNext() 
{
	load(_nextMapPath);
}

void Map::update(Player& player, Cursor& curseur, sf::View& view, Hud& hud, float const& dt) {
	if (_justLoaded) {
		player.setInitPos(_playerSpawn);
		player.setPosition(_playerSpawn);
		player.setTexture(_playerTextPath);
		_justLoaded = false;
	}

	if (player.update(curseur, _tiles, _throwableObjectsList, _droppedObjectsList, _mates, hud, dt) == NEXT_MAP)
	{
		hud.addMessage("Jeu", "Il est temps de changer de monde...");
		//hud.lockMessages(true);
		_waitingToChangeMap = true;
	}

	float tx = view.getCenter().x;
	float ty = view.getCenter().y;
	float sizex = view.getSize().x / 2;
	float sizey = view.getSize().y / 2;

	for (unsigned int i = 0; i < _ennemies.size(); i++) {
		float posX = _ennemies[i].getPosition().x;
		float posY = _ennemies[i].getPosition().y;

		if (posX >= tx - sizex && posX < tx + sizex && posY >= ty - sizey && posY < ty + sizey) 
		{
			int ennemyID = _ennemies[i].update(_mates, player.getPosition(), _tiles, _throwableObjectsList, _droppedObjectsList, dt);
			if (ennemyID != -2) {	//si l'ennemi est mort, on le retire de la liste
				//On regarde si l'ennemi que l'on vient d'exterminer est un ennemi à tuer dans la quête en cours.
				if (_quests.size() > 0)
					for (int j = 0; j < _quests[0].getList().size(); j++)
						if (_quests[0].getList()[j] == ennemyID)
							_quests[0].setDoneIndex(j);
				_ennemies.erase(_ennemies.begin() + i);
			}
		}
	}

	for (unsigned int i = 0; i < _mates.size(); i++) 
	{
		float posX = _mates[i].getPosition().x;
		float posY = _mates[i].getPosition().y;

		if (posX >= tx - sizex && posX < tx + sizex && posY >= ty - sizey && posY < ty + sizey)
		{
			if (_mates[i].update(_ennemies, player.getPosition(), _tiles, _throwableObjectsList, _droppedObjectsList, _mates, dt))	//si l'allié est mort, on le retire de la liste
				_mates.erase(_mates.begin() + i);
		}
	}

	for (unsigned int i = 0; i < _throwableObjectsList.size(); i++)
	{
		bool cond = _throwableObjectsList[i].update(dt, _tiles);

		if (!cond)
			_throwableObjectsList.erase(_throwableObjectsList.begin() + i);
	}

	_playerLifebar = player.getLifebar();

	//On regarde si la quête en cours est terminée
	if (_quests.size() > 0)
		if (_quests[0].getList().size() == 0) {
			std::cout << "\x1B[35m[Quest Success]\x1B[0m : Vous venez de terminer la quete " << _quests[0].getName() << " ! " << std::endl;
			if(_quests.size() > 1)
				std::cout << "\x1B[33m[Info]\x1B[0m : Prochaine quete : " << _quests[1].getName() << std::endl;
			else
				std::cout << "\x1B[33m[Info]\x1B[0m : Il n'y a pas de nouvelle quete." << std::endl;
			_quests.erase(_quests.begin());
		}

	if (_quests.size() > 0) {
		hud.setQuestActive(true);
		hud.setCurrentQuest(_quests[0].getName());
	}
	else
		hud.setQuestActive(false);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		view.setCenter(player.getPosition());
		view.setSize(sf::Vector2f(2000, 2000));
	}

	view.setCenter(player.getPosition());

	if (_waitingToChangeMap)
		if (hud.getMessagesNumber() <= 0)
			load(_nextMapPath);
}

sf::Vector2f Map::getPlayerSpawn() const {
	return _playerSpawn;
}

std::vector<ThrowedObject> Map::getThrowableObjectsList() const
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

	for (unsigned int i = 0; i < _mates.size(); i++)
		target.draw(_mates[i]);
  
	//On dessines les throwableObjects
	for (unsigned int i = 0; i < _throwableObjectsList.size(); i++)
		target.draw(_throwableObjectsList[i]);

	//dessin des droppedObjects
	for (unsigned int i = 0; i < _droppedObjectsList.size(); i++) {
		target.draw(*_droppedObjectsList[i]);
	}

	//dessin de l'HUD
	sf::View baseView = target.getView();
	target.setView(target.getDefaultView());
	target.draw(_playerLifebar);
	target.setView(baseView);
}