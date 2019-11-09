#include "Ennemy.h"

Ennemy::Ennemy(std::string texturePath, float defaultLife, sf::Vector2f initPosition) : NPC(texturePath, defaultLife, initPosition) {
	this->setWeapon(Arme("Time-Quest/Source/assets/mp40S.png", 5));
}

Ennemy::~Ennemy() {

}

bool Ennemy::update(sf::Vector2f playerPos, std::vector<ThrowedObject>& throwableObjectsList, float const& dt) {
	_curWeapon.update(getPosition());

	//mise à jour de la barre de vie avec la vie et la position actuelle de l'ennemi
	_lifeBar.setSize(sf::Vector2f((_life * 20) / _totalLife, 5));
	_lifeBar.setPosition(getPosition());
	_lifeBar.setOutlineColor(sf::Color::White);

	//si le joueur est proche, l'ennemi tire sur le joueur.
	//à faire

	//l'ennemi meurt si il est touché par une balle (logique)
	for(unsigned int i = 0; i < throwableObjectsList.size(); i++)
		if (getHitbox().intersects(throwableObjectsList[i].getHitbox())) {
			_life -= throwableObjectsList[i].getDamages();
			throwableObjectsList.erase(throwableObjectsList.begin() + i);
			if (_life <= 0) {
				_life = 0;
				return true;
			}
		}

	//On retourne true ou false, selon si l'ennemi n'a plus de vie ou non.
	//Ainsi, s'il est mort, il sera supprimé de la liste des annemis de la map.
	return false;
}
