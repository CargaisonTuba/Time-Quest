#include "Ennemy.h"

Ennemy::Ennemy(std::string texturePath, int defaultLife, sf::Vector2f initPosition) : NPC(texturePath, defaultLife, initPosition) {
	this->setWeapon(Arme("Time-Quest/Source/assets/mas38final.png"));
}

Ennemy::~Ennemy() {

}

void Ennemy::update() {
	_curWeapon.update(this->getPosition());
}
