#include "Cursor.h"
#include <iostream>

Cursor::Cursor(std::string texturePath)
{
	if (!_cursorText.loadFromFile(texturePath))
	{
		std::cout << "Erreur text curseur\n";
	}
}

Cursor::~Cursor() {

}

sf::Vector2i Cursor::getPosition()
{
	return position;
}

void Cursor::update() 
{
	position = sf::Mouse::getPosition();
}

void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite _cursorSprite;
	_cursorSprite.setTexture(_cursorText);
	target.draw(_cursorSprite);
}