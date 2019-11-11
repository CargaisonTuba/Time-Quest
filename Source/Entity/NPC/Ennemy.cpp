#include "Ennemy.h"

Ennemy::Ennemy(std::string texturePath, float defaultLife, sf::Vector2f initPosition) : NPC(texturePath, defaultLife, initPosition) {
	this->setWeapon(Arme("mas36"));
}

Ennemy::~Ennemy() {

}

bool Ennemy::update(sf::Vector2f playerPos, std::vector<Tile> const& _tiles, std::vector<ThrowedObject>& throwableObjectsList, float const& dt) {
	_curWeapon.update(getPosition(), playerPos);

	//mise à jour de la barre de vie avec la vie et la position actuelle de l'ennemi
	_lifeBar.setSize(sf::Vector2f((_life * 20) / _totalLife, 5));
	
	_lifeBar.setPosition(sf::Vector2f(getPosition().x -10, getPosition().y -20));
	_lifeBar.setOutlineColor(sf::Color::White);

	//si le joueur est proche, l'ennemi tire sur le joueur.
	float playerX = playerPos.x, ennemyX = getPosition().x;
	float playerY = playerPos.y, ennemyY = getPosition().y;
	float dist = sqrt((playerX - ennemyX) * (playerX - ennemyX) + (playerY - ennemyY) * (playerY - ennemyY));
	sf::Vector2f direction((playerX - ennemyX) / dist, (playerY - ennemyY) / dist);

	if (dist <= MIN_DIST_PLAYER) {
		if (dist >= _curWeapon.getRange())
		{
			_entitySprite.move(direction);
			for (unsigned int i = 0; i < _tiles.size(); i++) {
				if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall()) {
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
			fire(throwableObjectsList, playerPos);
		}
	}

	//l'ennemi perd de la vie s'il est touché par une balle
	for(unsigned int i = 0; i < throwableObjectsList.size(); i++)
		if (getHitbox().intersects(throwableObjectsList[i].getHitbox())) {
			_life -= throwableObjectsList[i].getDamages();
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
