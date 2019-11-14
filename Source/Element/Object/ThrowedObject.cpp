#include "ThrowedObject.h"
#include "iostream"

ThrowedObject::ThrowedObject(sf::Vector2f throwerPosition, sf::Vector2f direction, int range, float damages) :
	Object(throwerPosition, direction)
{
	this->_body.setFillColor(sf::Color::Black);
	this->_body.setOutlineColor(sf::Color::White);
	this->_body.setOutlineThickness(1);
	this->_body.setRadius(5);
	_clock = sf::Clock();
	this->_clock.restart();
	this->_range = range;

	_damages = damages;
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
	if (sqrt((_body.getPosition().x - _posInit.x) * (_body.getPosition().x - _posInit.x) + (_body.getPosition().y - _posInit.y) * (_body.getPosition().y - _posInit.y)) > _range)
	{
		return false;
	}

	this->_body.move(sf::Vector2f((_direction.x * dt)/5, (_direction.y * dt)/5));
	for (unsigned int i = 0; i < _tiles.size(); i++)
	{
		if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall())
		{
			_body.move(sf::Vector2f(-(_direction.x * dt) / 5, -(_direction.y * dt) / 5));
			return false;
		}
	}
	return true;
}