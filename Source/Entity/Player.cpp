#include "Player.h"

Player::Player(std::string texturePath, int defaultLife, sf::Vector2f initPosition) : Entity(texturePath, defaultLife, initPosition) {

}

Player::~Player() {

}

sf::Vector2f Player::getPosition() const {
	return _entitySprite.getPosition();
}

void Player::update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		_entitySprite.move(sf::Vector2f(0, -1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		_entitySprite.move(sf::Vector2f(-1, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_entitySprite.move(sf::Vector2f(0, 1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_entitySprite.move(sf::Vector2f(1, 0));
}