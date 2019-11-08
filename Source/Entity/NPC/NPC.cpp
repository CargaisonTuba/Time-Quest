#include "NPC.h"

NPC::NPC(std::string texturePath, int defaultLife, sf::Vector2f initPosition) : Entity(texturePath, defaultLife, initPosition) {
	_lifeBar.setFillColor(sf::Color::Red);
	_lifeBar.setOutlineThickness(1);
}

NPC::~NPC() {

}

void NPC::update() {
	_curWeapon.update(getPosition());

	//mise à jour de la barre de vie avec la vie et la position actuelle de l'ennemi
	_lifeBar.setSize(sf::Vector2f(_totalLife, 5));
	_lifeBar.setPosition(getPosition());
	_lifeBar.setOutlineColor(sf::Color::White);
}

void NPC::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Sprite s = _entitySprite;
	s.setTexture(_entityText[_spritePosCount][_dir]);

	target.draw(s);
	target.draw(_curWeapon);
	target.draw(_lifeBar);
}
