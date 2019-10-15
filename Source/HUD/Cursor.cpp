#include "Cursor.h"
#include <iostream>

Cursor::Cursor(std::string texturePath)
{
	if (!_cursorText.loadFromFile(texturePath))
	{
		std::cout << "Erreur text curseur\n";
	}
	_cursorSprite.setTexture(_cursorText);
	_cursorSprite.setScale(sf::Vector2f(5.f, 5.f));
}

Cursor::~Cursor() {

}

sf::Vector2f Cursor::getPosition()
{
	return _cursorSprite.getPosition();
}

void Cursor::update(sf::Window &window) 
{
	_cursorSprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
}

void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_cursorSprite);
}