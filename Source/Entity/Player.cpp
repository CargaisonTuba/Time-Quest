#include "Player.h"
#include <iostream>



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
void Player::update(Cursor curseur, std::vector<Tile> _tiles, std::vector<ThrowedObject> &throwableObjectsList) {
	if (!isDead())
	{

		float speed = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			_dir = 2;
			_entitySprite.move(sf::Vector2f(0, -speed));
			for (int i = 0; i < _tiles.size(); i++) {
				if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall()) {
					_entitySprite.move(sf::Vector2f(0, speed));
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			_dir = 3;
			_entitySprite.move(sf::Vector2f(-speed, 0));
			for (int i = 0; i < _tiles.size(); i++) {
				if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall()) {
					_entitySprite.move(sf::Vector2f(speed, 0));
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			_dir = 0;
			_entitySprite.move(sf::Vector2f(0, speed));
			for (int i = 0; i < _tiles.size(); i++) {
				if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall()) {
					_entitySprite.move(sf::Vector2f(0, -speed));
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			_dir = 1;
			_entitySprite.move(sf::Vector2f(speed, 0));
			for (int i = 0; i < _tiles.size(); i++) {
				if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall()) {
					_entitySprite.move(sf::Vector2f(-speed, 0));
				}
			}
		}

		_weaponJ.update(this->getPosition(), curseur);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->fire(throwableObjectsList, curseur);
		}

	}
}

bool Player::fire(std::vector<ThrowedObject> &throwableObjectsList, Cursor &cursor)
{
	if (_timeSinceShot.getElapsedTime() > sf::seconds(1.f))
	{
		std::cout << "shoot !\n";
		_timeSinceShot.restart();
		sf::Vector2f positionPlayer = this->getPosition();

		sf::Vector2f positionMouse = cursor.getPosition();
		sf::Vector2f aim(positionMouse.x - positionPlayer.x, positionMouse.y - positionPlayer.y);
		float lenAim = sqrt(aim.x * aim.x + aim.y * aim.y);
		sf::Vector2f direction(aim.x / lenAim, aim.y / lenAim);

		Bullet newBullet = Bullet(positionPlayer, direction);
		
		throwableObjectsList.push_back(newBullet);
		
	}
  
	return true;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Sprite s = _entitySprite;
	s.setTexture(_entityText[_spritePosCount][_dir]);
	target.draw(s);
	target.draw(_weaponJ);
}
