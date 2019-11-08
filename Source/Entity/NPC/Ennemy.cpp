#include "Ennemy.h"

Ennemy::Ennemy(std::string texturePath, int defaultLife, sf::Vector2f initPosition) : NPC(texturePath, defaultLife, initPosition) {
	this->setWeapon(Arme("Time-Quest/Source/assets/mas38final.png", 5));
}

Ennemy::~Ennemy() {

}

void Ennemy::update(sf::Vector2f playerPos) {
	_curWeapon.update(getPosition());

	//mise à jour de la barre de vie avec la vie et la position actuelle de l'ennemi
	_lifeBar.setSize(sf::Vector2f(_totalLife, 5));
	_lifeBar.setPosition(getPosition());
	_lifeBar.setOutlineColor(sf::Color::White);

	//si le joueur est proche, l'ennemi tire sur le joueur.
	//à faire
}
