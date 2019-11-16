#include "ThrowedObject.h"
#include "iostream"

ThrowedObject::ThrowedObject(std::string texturePath, sf::Vector2f throwerPosition, sf::Vector2f direction, int range, float damages) :
	Object(texturePath, throwerPosition, direction)
{
	_clock = sf::Clock();
	this->_clock.restart();
	this->_range = range;

	_damages = damages;
	if (!_impactBuffer.loadFromFile("Time-Quest/Source/assets/sound/impact.wav"))
	{
		std::cout << "Echec impact \n";
	}
}

ThrowedObject::ThrowedObject()
{
	_damages = 0;
	_range = 0;
}

ThrowedObject::~ThrowedObject()
{

}


float ThrowedObject::getDamages() const {
	return _damages;
}

bool ThrowedObject::update(float const& dt,  std::vector<Tile> const& _tiles)
{
	if (_clock.getElapsedTime() > sf::seconds(5.f))
	{
		return false;
	}
	if (sqrt((_objectSprite.getPosition().x - _posInit.x) * (_objectSprite.getPosition().x - _posInit.x) + (_objectSprite.getPosition().y - _posInit.y) * (_objectSprite.getPosition().y - _posInit.y)) > _range)
	{
		return false;
	}

	this->_objectSprite.move(sf::Vector2f((_direction.x * dt)/5, (_direction.y * dt)/5));
	for (unsigned int i = 0; i < _tiles.size(); i++)
	{
		if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall())
		{
			_impactSound.setBuffer(_impactBuffer);
			_impactSound.play();
			_objectSprite.move(sf::Vector2f(-(_direction.x * dt) / 5, -(_direction.y * dt) / 5));
			return false;
		}
	}
	return true;
}