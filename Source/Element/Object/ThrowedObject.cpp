#include "ThrowedObject.h"
#include "iostream"

ThrowedObject::ThrowedObject(sf::Vector2f throwerPosition, sf::Vector2f direction)
{

	//std::cout << "direction x:" << direction.x << " y: " << direction.y << "\n";
	//std::cout << "_direction x:" << _direction.x << " y: " << _direction.y << "\n";
	this->_direction = direction;
	//std::cout << "_direction x:" << this->_direction.x << " y: " << this->_direction.y << "\n";
	this->_body.setPosition(throwerPosition);
	this->_body.setFillColor(sf::Color::Black);
	this->_body.setOutlineColor(sf::Color::White);
	this->_body.setOutlineThickness(1);
	this->_body.setRadius(5);
	this->_clock.restart();
}

ThrowedObject::ThrowedObject()
{

}

ThrowedObject::~ThrowedObject()
{

}

bool ThrowedObject::update()
{
	if (_clock.getElapsedTime() > sf::seconds(5.f))
	{
		return false;
	}
	//std::cout << "x: " << _direction.x << " y: " << _direction.y << "\n";
	this->_body.move(_direction);
	return true;
}