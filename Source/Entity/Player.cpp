#include "Player.h"
#include <iostream>

Player::Player(std::string texturePath, float defaultLife, sf::Vector2f initPosition) : Entity(texturePath, defaultLife, initPosition) {
	this->setWeapon(Arme("mas36"));

	_lifeBar.setFillColor(sf::Color::Red);
	_lifeBar.setOutlineColor(sf::Color::Magenta);
	_lifeBar.setOutlineThickness(2);
	_lifeBar.setPosition(sf::Vector2f(20, 680));
}

Player::~Player() {

}

sf::Vector2f Player::getPosition() const {
	return _entitySprite.getPosition();
	
}

//On met la position de la souris en paramètre pour pouvoir décider dans quelle direction pointe l'arme
void Player::update(Cursor curseur, std::vector<Tile> _tiles, std::vector<ThrowedObject> &throwableObjectsList, float const& dt) {
	//déplacement du joueur
	float speed = 0.15f * dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		_dir = 2;
		_entitySprite.move(sf::Vector2f(0, -speed));
		for (unsigned int i = 0; i < _tiles.size(); i++) {
			if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall()) {
				_entitySprite.move(sf::Vector2f(0, speed));
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		_dir = 3;
		_entitySprite.move(sf::Vector2f(-speed, 0));
		for (unsigned int i = 0; i < _tiles.size(); i++) {
			if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall()) {
				_entitySprite.move(sf::Vector2f(speed, 0));
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		_dir = 0;
		_entitySprite.move(sf::Vector2f(0, speed));
		for (unsigned int i = 0; i < _tiles.size(); i++) {
			if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall()) {
				_entitySprite.move(sf::Vector2f(0, -speed));
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		_dir = 1;
		_entitySprite.move(sf::Vector2f(speed, 0));
		for (unsigned int i = 0; i < _tiles.size(); i++) {
			if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall()) {
				_entitySprite.move(sf::Vector2f(-speed, 0));
			}
		}
	}

	//l'arme accompagne le joueur, logique
	_curWeapon.update(this->getPosition(), curseur);

	//On fait en sorte que le joueur tire avec clic gauche.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->fire(throwableObjectsList, curseur);

	//On met la barre de vie du joueur à jour
	_lifeBar.setSize(sf::Vector2f((_life * 300) / _totalLife, 20));
}
