#include "Cursor.h"
#include <iostream>

Cursor::Cursor(std::string texturePath)
{
	if (!_cursorText.loadFromFile(texturePath))
	{
		std::cout << "Erreur text curseur\n";
	}
	_cursorSprite.setTexture(_cursorText);
	_cursorSprite.setScale(sf::Vector2f(1.f, 1.f));
	_cursorSprite.setOrigin(sf::Vector2f(2.5, 2.5));
}

Cursor::~Cursor() {

}

sf::Vector2f Cursor::getPosition() const
{
	return _cursorSprite.getPosition();
}

void Cursor::update(sf::RenderWindow &window) 
{
	_cursorSprite.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}

void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_cursorSprite);
}