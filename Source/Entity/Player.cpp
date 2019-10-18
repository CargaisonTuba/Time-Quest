#include "Player.h"
#include <iostream>



Player::Player(std::string texturePath, int defaultLife, sf::Vector2f initPosition) : Entity(texturePath, defaultLife, initPosition) {

}

Player::~Player() {

}

sf::Vector2f Player::getPosition() const {
	return _entitySprite.getPosition();
	
}

void Player::update(std::vector<ThrowedObject> &throwableObjectsList, sf::RenderWindow& window) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		_entitySprite.move(sf::Vector2f(0, -1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		_entitySprite.move(sf::Vector2f(-1, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_entitySprite.move(sf::Vector2f(0, 1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_entitySprite.move(sf::Vector2f(1, 0));
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->fire(throwableObjectsList, window);
	}
		

		
}

bool Player::fire(std::vector<ThrowedObject> &throwableObjectsList, sf::RenderWindow &window)
{
	if (_timeSinceShot.getElapsedTime() > sf::seconds(1.f))
	{
		std::cout << "shoot !\n";
		_timeSinceShot.restart();
		sf::Vector2f positionPlayer = this->getPosition();

		sf::Vector2i positionMouse = sf::Mouse::getPosition(window);
		sf::Vector2f aim(positionMouse.x - positionPlayer.x, positionMouse.y - positionPlayer.y);
		float lenAim = sqrt(aim.x * aim.x + aim.y * aim.y);
		sf::Vector2f direction(aim.x / lenAim, aim.y / lenAim);
		//std::cout << "x: " << direction.x << " y: " << direction.y << "\n";
		Bullet newBullet = Bullet(positionPlayer, direction);
		
		throwableObjectsList.push_back(newBullet);
		
	}
	

	
	return true;
}