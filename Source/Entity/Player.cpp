#include "Player.h"

Player::Player(std::string texturePath, int defaultLife, sf::Vector2f initPosition) : Entity(texturePath, defaultLife, initPosition) {
	this->setWeapon(Arme("Time-Quest/Source/assets/mas36final2.png"));
}

Player::~Player() {

}

void Player::setWeapon(Arme arme)
{
	arme.setPosition(this->getPosition());
}

Arme Player::getWeapon()
{
	return this->_weaponJ;
}


sf::Vector2f Player::getPosition() const {
	return _entitySprite.getPosition();
}

//On met la position de la souris en paramètre pour pouvoir décider dans quelle direction pointe l'arme
void Player::update(Cursor curseur) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		_entitySprite.move(sf::Vector2f(0, -1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		_entitySprite.move(sf::Vector2f(-1, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_entitySprite.move(sf::Vector2f(0, 1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_entitySprite.move(sf::Vector2f(1, 0));
	_weaponJ.update(this->getPosition(), curseur);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Sprite s = _entitySprite;
	s.setTexture(_entityText[_spritePosCount][_dir]);
	target.draw(s);
	target.draw(_weaponJ);
}
