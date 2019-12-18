#include "Ennemy.h"

Ennemy::Ennemy(std::string texturePath, float defaultLife, sf::Vector2f initPosition) : NPC(texturePath, defaultLife, initPosition) 
{
	this->setWeapon(Arme("kar98"));
	_lifeBar.setFillColor(sf::Color::Red);
	_lifeBar.setOutlineThickness(1);
	//compteur++;
	//this->_ID = compteur;
	_detectRange = 200;
}

Ennemy::~Ennemy() 
{

}

bool Ennemy::update(std::vector<Mate>& _mates, sf::Vector2f playerPos, std::vector<Tile> const& _tiles, std::vector<ThrowedObject>& throwableObjectsList, std::vector<Object*> &droppedObjects, float const& dt)
{

	if (_isPushed)
	{
		if (_timeSincePushed.getElapsedTime().asMilliseconds() > 500)
		{
			_isPushed = false;
		}
		else
		{
			_entitySprite.move(_pushingForce);
			for (unsigned int i = 0; i < _tiles.size(); i++) {
				if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall()) {
					_entitySprite.move(-_pushingForce);
				}
			}
		}
	}

	//mise à jour de la barre de vie avec la vie et la position actuelle de l'ennemi
	_lifeBar.setSize(sf::Vector2f((_life * 20) / _totalLife, 5));
	
	_lifeBar.setPosition(sf::Vector2f(getPosition().x -10, getPosition().y -20));
	_lifeBar.setOutlineColor(sf::Color::Transparent);

	//initialisation de la cible à la position du joueur
	float mateX = playerPos.x, ennemyX = getPosition().x;
	float mateY = playerPos.y, ennemyY = getPosition().y;
	int a = 0;
	sf::Vector2f targetPos = playerPos;
	float dist = sqrt((mateX - ennemyX) * (mateX - ennemyX) + (mateY - ennemyY) * (mateY - ennemyY));
	sf::Vector2f direction((mateX - ennemyX) / dist, (mateY - ennemyY) / dist);

	//Chaque ennemi parcourt le tableau d'alliés
	for (unsigned int i = 0; i < _mates.size(); i++)
	{
		mateX = _mates[i].getPosition().x;
		mateY = _mates[i].getPosition().y;
		a = sqrt((mateX - ennemyX) * (mateX - ennemyX) + (mateY - ennemyY) * (mateY - ennemyY));
		if (a < dist)
		{
			dist = a;
			direction = sf::Vector2f((mateX - ennemyX) / dist, (mateY - ennemyY) / dist);
			targetPos = _mates[i].getPosition();
		}
	}
	
	
	//Une fois la cible la plus proche trouvée, on vérifie si elle est dans la zone de détection de l'ennemi ou à portée de tir
	if (dist <= _detectRange) 
	{
		_curWeapon->update(getPosition(), targetPos);
		if (dist >= _curWeapon->getRange())
		{
			_entitySprite.move(sf::Vector2f(direction.x/2, direction.y/2));
			for (unsigned int i = 0; i < _tiles.size(); i++) 
			{
				if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall()) 
				{
					_entitySprite.move(-direction);
				}
			}
			_animation_tick += dt;
			if (_animation_tick >= 50) {
				_animation_tick = 0;
				_spritePosCount++;
				if (_spritePosCount >= _spritePosCountMax)
					_spritePosCount = 0;
			}
		}
		else
		{
			_spritePosCount = 0;
			if (_curWeapon->getReady())
				fire(throwableObjectsList, playerPos, _tiles);
			else
				_curWeapon->recharger();
		}
	}
	else
	{
		//_curWeapon->update(getPosition(), sf::VectgetPosition);
	}

	//l'ennemi perd de la vie s'il est touché par une balle
	for(unsigned int i = 0; i < throwableObjectsList.size(); i++)
		if (getHitbox().intersects(throwableObjectsList[i].getHitbox())) {
			_life -= throwableObjectsList[i].getDamages();
			this->_entitySprite.move(sf::Vector2f(throwableObjectsList[i].getDirection().x * 2, throwableObjectsList[i].getDirection().y * 2));
			throwableObjectsList.erase(throwableObjectsList.begin() + i);
			if (isDead()) {
				std::cout << "\x1B[33m[info]\x1B[0m : \x1B[35mmort\x1B[0m d'un ennemi !\n";

				//l'ennemi drop son stuff ce desco
				killNPC(droppedObjects);

				return true;
			}
		}

	//On retourne true ou false, selon si l'ennemi n'a plus de vie ou non.
	//Ainsi, s'il est mort, il sera supprimé de la liste des annemis de la map.
	return false;
}

