#include "NPC.h"

NPC::NPC(std::string texturePath, float defaultLife, sf::Vector2f initPosition) : Entity(texturePath, defaultLife, initPosition) {

}

NPC::~NPC() {

}
void NPC::killNPC(std::vector<Object*>& droppedObjects) {
	droppedObjects.push_back(new Arme(*_curWeapon));
}

void NPC::update(sf::Vector2f playerPos) {
	_curWeapon->update(getPosition(), playerPos);

	//mise à jour de la barre de vie avec la vie et la position actuelle de l'ennemi
	_lifeBar.setSize(sf::Vector2f(_totalLife, 5));
	_lifeBar.setPosition(getPosition());
	_lifeBar.setOutlineColor(sf::Color::White);
}

void NPC::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Sprite s = _entitySprite;
	s.setTexture(_entityText[_spritePosCount][_dir]);

	target.draw(s);
	target.draw(*_curWeapon);
	target.draw(_lifeBar);
}
