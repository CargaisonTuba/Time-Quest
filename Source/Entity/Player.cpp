#include "Player.h"

Player::Player(std::string texturePath, int defaultLife, sf::Vector2f initPosition) : Entity(texturePath, defaultLife, initPosition) {

}

Player::~Player() {

}

/*void Player::setWeapon(Arme arme)
{
	arme.setPosition(this->getPosition);
}*/


sf::Vector2f Player::getPosition() const {
	return _entitySprite.getPosition();
}

//On met la position de la souris en paramètre pour pouvoir décider dans quelle direction pointe l'arme
void Player::update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		_entitySprite.move(sf::Vector2f(0, -1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		_entitySprite.move(sf::Vector2f(-1, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_entitySprite.move(sf::Vector2f(0, 1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_entitySprite.move(sf::Vector2f(1, 0));
	/*if (mousePosition.y < spriteMecChelou.getPosition().y)
	{
		arme.setPosition(spriteMecChelou.getPosition().x - 10, spriteMecChelou.getPosition().y + 6);
		if (mousePosition.x < spriteMecChelou.getPosition().x)
		{

			spriteArme.setScale(1 / 6.f, -1 / 6.f);
		}
		else if (mousePosition.x > spriteMecChelou.getPosition().x)
		{
			spriteArme.setPosition(spriteMecChelou.getPosition().x, spriteMecChelou.getPosition().y + 6);
			spriteArme.setScale(1 / 6.f, 1 / 6.f);
		}
	}
	else if (mousePosition.y > spriteMecChelou.getPosition().y)
	{
		spriteArme.setPosition(spriteMecChelou.getPosition().x - 10, spriteMecChelou.getPosition().y + 6);
		if (mousePosition.x > spriteMecChelou.getPosition().x)
		{
			spriteArme.setPosition(spriteMecChelou.getPosition().x, spriteMecChelou.getPosition().y + 6);
			spriteArme.setScale(1 / 6.f, 1 / 6.f);

		}
		else if (mousePosition.x < spriteMecChelou.getPosition().x)
		{
			spriteArme.setScale(1 / 6.f, -1 / 6.f);
	}*/
}