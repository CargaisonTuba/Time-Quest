#include "Player.h"
#include <iostream>

Player::Player(std::string texturePath, float defaultLife, sf::Vector2f initPosition) : Entity(texturePath, defaultLife, initPosition) {
	this->setWeapon(Arme("mas38"));

	_lifeBar.setFillColor(sf::Color::Red);
	_lifeBar.setOutlineColor(sf::Color::Magenta);
	_lifeBar.setOutlineThickness(2);
	_lifeBar.setPosition(sf::Vector2f(20, 680));

	_justChanged = false;
}

Player::~Player() {

}

sf::Vector2f Player::getPosition() const {
	return _entitySprite.getPosition();
	
}

//On met la position de la souris en paramètre pour pouvoir décider dans quelle direction pointe l'arme
void Player::update(Cursor const &curseur, std::vector<Tile> const &_tiles, std::vector<ThrowedObject> &throwableObjectsList, float const& dt) 
{
	//changement d'arme (TEST)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (!_justChanged) {
			_justChanged = true;
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				setWeapon(Arme("mas38"));
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				setWeapon(Arme("mp40"));
		}
	}
	else
		_justChanged = false;

	//déplacement du joueur
	float speed = 0.1f * dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		speed = speed * 1.5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		
		_entitySprite.move(sf::Vector2f(0, -speed));
		for (unsigned int i = 0; i < _tiles.size(); i++) {
			if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall()) {
				_entitySprite.move(sf::Vector2f(0, speed));
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		
		_entitySprite.move(sf::Vector2f(-speed, 0));
		for (unsigned int i = 0; i < _tiles.size(); i++) {
			if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall()) {
				_entitySprite.move(sf::Vector2f(speed, 0));
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		
		_entitySprite.move(sf::Vector2f(0, speed));
		for (unsigned int i = 0; i < _tiles.size(); i++) {
			if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall()) {
				_entitySprite.move(sf::Vector2f(0, -speed));
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		
		_entitySprite.move(sf::Vector2f(speed, 0));
		for (unsigned int i = 0; i < _tiles.size(); i++) {
			if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall()) {
				_entitySprite.move(sf::Vector2f(-speed, 0));
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::S)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		_animation_tick += dt;
		if (_animation_tick >= 50) {
			_animation_tick = 0;
			_spritePosCount++;
			if (_spritePosCount >= _spritePosCountMax)
				_spritePosCount = 0;
		}
	}
	else
		_spritePosCount = 0;

	if (this->getWeapon().getAngle() > 45) {
		if (this->getWeapon().getAngle() < 135)
			_dir = 0;
		else if (this->getWeapon().getAngle() < 225)
			_dir = 3;
		else if (this->getWeapon().getAngle() < 315)
			_dir = 2;
		else
			_dir = 1;
	}
	else
		_dir = 1;

	//recharger l'arme
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		this->getWeapon().recharger();

	//l'arme accompagne le joueur, logique
	_curWeapon.update(this->getPosition(), curseur.getPosition());

	//On fait en sorte que le joueur tire avec clic gauche.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->fire(throwableObjectsList, curseur.getPosition(), _tiles);

	//Si le joueur se fait toucher, il perd de la vie
	//l'ennemi perd de la vie s'il est touché par une balle
	for (unsigned int i = 0; i < throwableObjectsList.size(); i++)
		if (getHitbox().intersects(throwableObjectsList[i].getHitbox())) {
			_life -= throwableObjectsList[i].getDamages();
			throwableObjectsList.erase(throwableObjectsList.begin() + i);
			if (_life <= 0) {
				_life = 0;
				std::cout << "\x1B[33m[info]\x1B[0m : \x1B[35mmort\x1B[0m du joueur\n";
				_entitySprite.setPosition(_initPos);
				_life = _totalLife;
			}
		}

	//On met la barre de vie du joueur à jour
	_lifeBar.setSize(sf::Vector2f((_life * 300) / _totalLife, 20));
}
