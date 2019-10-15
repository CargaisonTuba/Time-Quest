#include "Player.h"
#include "../Element/Object/ThrowedObject/Bullet.h"
#include "../Element/Object/ObjectsList.h"

Player::Player(std::string texturePath, int defaultLife, sf::Vector2f initPosition) : Entity(texturePath, defaultLife, initPosition) {

}

Player::~Player() {

}

sf::Vector2f Player::getPosition() const {
	return _entitySprite.getPosition();
}

void Player::update(ObjectsList &throwableObjectsList) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		_entitySprite.move(sf::Vector2f(0, -1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		_entitySprite.move(sf::Vector2f(-1, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_entitySprite.move(sf::Vector2f(0, 1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_entitySprite.move(sf::Vector2f(1, 0));
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->fire(throwableObjectsList);
}

bool Player::fire(ObjectsList& throwableObjectsList)
{
	sf::Vector2f positionPlayer = this->getPosition();
	sf::Vector2i positionMouse = sf::Mouse::getPosition();

	sf::Vector2f aim(positionMouse.x - positionPlayer.x, positionMouse.y - positionPlayer.y);
	float lenAim = sqrt(aim.x * aim.x + aim.y * aim.y);

	sf::Vector2f direction(aim.x / lenAim, aim.y / lenAim);

	Bullet newBullet = Bullet(positionPlayer, direction);

	throwableObjectsList.addObject(newBullet);

	return true;
}