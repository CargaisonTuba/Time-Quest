#include "Player.h"
#include <iostream>

Player::Player(std::string texturePath, float defaultLife, sf::Vector2f initPosition) : Entity(texturePath, defaultLife, initPosition) {


	_justPressed = false;
	_justChanged = false;

	_inventory.push_back(new Arme("fm2429"));
	_inventory.push_back(new Arme("mas36"));
	_inventory.push_back(new Arme("mas38"));
	_inventory.push_back(new Arme("mp40"));

	_inventoryIndex = 0;
	_curWeapon = (Arme*)(_inventory[_inventoryIndex]);
}

Player::~Player() {

}

sf::Vector2f Player::getPosition() const {
	return _entitySprite.getPosition();
	
}

//On met la position de la souris en paramètre pour pouvoir décider dans quelle direction pointe l'arme
void Player::update(Cursor const& curseur, std::vector<Tile> const& _tiles, std::vector<ThrowedObject>& throwableObjectsList, std::vector<Object*>& droppedObjectsList, float const& dt)
{
	//déplacement du joueur
	float speed = 0.1f * dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		speed *= 1.5f;

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

	if (this->getWeapon()->getAngle() > 45) {
		if (this->getWeapon()->getAngle() < 135)
			_dir = 0;
		else if (this->getWeapon()->getAngle() < 225)
			_dir = 3;
		else if (this->getWeapon()->getAngle() < 315)
			_dir = 2;
		else
			_dir = 1;
	}
	else
		_dir = 1;

	//recharger l'arme
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		this->_curWeapon->recharger();

	//Changer d'item dans l'inventaire
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (!_justPressed) {
			_justPressed = true;
			_inventory[_inventoryIndex] = _curWeapon;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				if (_inventoryIndex > 0)
					_inventoryIndex--;
				else
					_inventoryIndex = 0;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				if (_inventoryIndex < _inventory.size() - 1 && _inventory.size() > 0)
					_inventoryIndex++;
			}
			std::cout << "\x1B[33m[info]\x1B[0m : index de l'inventaire : " << _inventoryIndex << "/" << _inventory.size() << std::endl;
			_justChanged = true;
		}
	}
	else
		_justPressed = false;

	if (_inventory.size() > 0 && _justChanged) {
		_curWeapon = (Arme*)(_inventory[_inventoryIndex]);
		_justChanged = false;
	}

	//l'arme accompagne le joueur, logique
	_curWeapon->update(this->getPosition(), curseur.getPosition());

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


}
