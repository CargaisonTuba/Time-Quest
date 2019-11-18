#include "Mate.h"


Mate::Mate(std::string texturePath, float defaultLife, sf::Vector2f initPosition) : Ally(texturePath, defaultLife, initPosition) {
	this->setWeapon(Arme("mas36"));
	_lifeBar.setFillColor(sf::Color::Blue);
	_lifeBar.setOutlineThickness(1);
	//compteur++;
	//this->_ID = compteur;
	_detectRange = 200;
	_distPlayer = 50;
	_follow = false;
}

Mate::~Mate() {

}

bool Mate::update(std::vector<Ennemy>& _ennemies, sf::Vector2f playerPos, std::vector<Tile> const& _tiles, std::vector<ThrowedObject>& throwableObjectsList, float const& dt) {
	//std::vector<Ennemy>& _ennemies, 

	//mise à jour de la barre de vie avec la vie et la position actuelle de l'allié
	_lifeBar.setSize(sf::Vector2f((_life * 20) / _totalLife, 5));

	_lifeBar.setPosition(sf::Vector2f(getPosition().x - 10, getPosition().y - 20));
	_lifeBar.setOutlineColor(sf::Color::Transparent);

	//si le joueur appuie sur F, on passe follow en true
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		_follow = !_follow;
	}

	//si un ennemi est proche, l'allié lui tire dessus
	float dist = _detectRange;
	sf::Vector2f direction;
	sf::Vector2f targetPos;
	float mateY = getPosition().y;
	float mateX = getPosition().x;
	float ennemyX, ennemyY;
	for (unsigned int i = 0; i < _ennemies.size(); i++)
	{
		ennemyX = _ennemies[i].getPosition().x; 
		ennemyY = _ennemies[i].getPosition().y;
		if (sqrt((ennemyX - mateX) * (ennemyX - mateX) + (ennemyY - mateY) * (ennemyY - mateY)) < dist)
		{
			dist = sqrt((ennemyX - mateX) * (ennemyX - mateX) + (ennemyY - mateY) * (ennemyY - mateY));
			direction = sf::Vector2f((ennemyX - mateX) / dist, (ennemyY - mateY) / dist);
			targetPos = _ennemies[i].getPosition();
		}
	}
	
	
	if (dist <= _detectRange) {
		if (dist >= _curWeapon.getRange())
		{
			if (_follow)
			{
				follow(playerPos, _tiles);
			}
			else
			{
				_entitySprite.move(sf::Vector2f(direction.x / 2, direction.y / 2));
			}
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
			if (_follow)
			{
				follow(playerPos, _tiles);
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
			}
			if (_curWeapon.getReady())
			{
				fire(throwableObjectsList, targetPos, _tiles);
			}
			else
			{
				_curWeapon.recharger();
			}
		}
	}

	_curWeapon.update(getPosition(), targetPos);
	
	//l'allié perd de la vie s'il est touché par une balle
	for (unsigned int i = 0; i < throwableObjectsList.size(); i++)
		if (getHitbox().intersects(throwableObjectsList[i].getHitbox())) {
			_life -= throwableObjectsList[i].getDamages();
			this->_entitySprite.move(sf::Vector2f(throwableObjectsList[i].getDirection().x * 2, throwableObjectsList[i].getDirection().y * 2));
			throwableObjectsList.erase(throwableObjectsList.begin() + i);
			if (_life <= 0) {
				_life = 0;
				std::cout << "\x1B[33m[info]\x1B[0m : \x1B[35mmort\x1B[0m d'un ennemi !\n";
				return true;
			}
		}

	//On retourne true ou false, selon si l'ennemi n'a plus de vie ou non.
	//Ainsi, s'il est mort, il sera supprimé de la liste des annemis de la map.
	return false;
}

void Mate::follow(sf::Vector2f playerPos, std::vector<Tile> const& _tiles)
{
	//initialisation de la cible à la position du joueur
	float selfX = getPosition().x;
	float selfY = getPosition().y;
	sf::Vector2f targetPos = playerPos;
	float dist = sqrt((playerPos.x - selfX) * (playerPos.x - selfX) + (playerPos.y - selfY) * (playerPos.y - selfY));
	sf::Vector2f direction((playerPos.x - selfX) / dist, (playerPos.y - selfY) / dist);

	if (dist <= _detectRange) {
		if (dist >= _distPlayer)
		{
			_entitySprite.move(sf::Vector2f(direction.x / 2, direction.y / 2));
			for (unsigned int i = 0; i < _tiles.size(); i++)
			{
				if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall())
				{
					_entitySprite.move(-direction);
				}
			}
		}
	}
}