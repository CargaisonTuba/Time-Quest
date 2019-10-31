#include "Arme.h"
#include <iostream>

Arme::Arme(std::string texturePath)
{
	if (!_armeText.loadFromFile(texturePath))
	{
		std::cout << "Erreur text arme\n";
	}
	_armeSprite.setTexture(_armeText);

	angle = 0;
	longueurX = 0;
	longueurY = 0;
	hypo = 0;
	std::cout << "Ceci est le constructeur normal\n";
}

Arme::Arme()
{
	std::cout << "Ceci est le constructeur par défaut\n";
}

Arme::~Arme()
{

}

void Arme::setPosition(sf::Vector2f unePosition)
{
	_armeSprite.setPosition(unePosition);
}

sf::Vector2f Arme::getPosition()
{
	return _armeSprite.getPosition();
}

void Arme::update(sf::Vector2f entityPos) {
	this->setPosition(entityPos);
	_armeSprite.setScale(0.1, 0.1);
}

void Arme::update(sf::Vector2f entityPos, Cursor cursor)
{
	this->setPosition(entityPos);
	
	sf::Vector2f mousePosition = cursor.getPosition();

	longueurX = abs((mousePosition.x) - (entityPos.x));
	longueurY = abs((mousePosition.y) - (entityPos.y));
	hypo = sqrt(longueurX * longueurX + longueurY * longueurY);

	if (mousePosition.y < entityPos.y)
	{
		if (mousePosition.x < entityPos.x)
		{
			angle = (180 + acos(longueurX / hypo) * 180.0 / 3.141592653589793);
			_armeSprite.setScale(1 / 6.f, -1 / 6.f);
		}
		else if (mousePosition.x > entityPos.x)
		{
			angle = 360 - (acos(longueurX / hypo) * 180.0 / 3.141592653589793);
			_armeSprite.setScale(1 / 6.f, 1 / 6.f);
		}
	}
	else if (mousePosition.y > entityPos.y)
	{
		if (mousePosition.x > entityPos.x)
		{
			angle = acos(longueurX / hypo) * 180.0 / 3.141592653589793;
			_armeSprite.setScale(1 / 6.f, 1 / 6.f);

		}
		else if (mousePosition.x < entityPos.x)
		{
			angle = 180 - (acos(longueurX / hypo) * 180.0 / 3.141592653589793);
			_armeSprite.setScale(1 / 6.f, -1 / 6.f);
		}
	}

	_armeSprite.setRotation(angle);
}

void Arme::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite s = _armeSprite;
	s.setTexture(_armeText);
	s.setScale(s.getScale().x * 0.4, s.getScale().y * 0.4);

	s.move(13, 13);	//on centre l'arme
	target.draw(s);
}