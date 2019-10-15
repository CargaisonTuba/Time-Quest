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
}

Arme::~Arme()
{

}

void Arme::setProprio(Entity proprioP)
{
	_proprio = proprioP;
}

Entity Arme::getProprio()
{
	return _proprio;
}

void Arme::setPosition(sf::Vector2f unePosition)
{
	_armeSprite.setPosition(unePosition.x, unePosition.y);
}

sf::Vector2f Arme::getPosition()
{
	return _armeSprite.getPosition();
}

void Arme::update(sf::Vector2f mousePosition)
{
	this->setPosition(_proprio.getPosition());

	longueurX = abs((mousePosition.x) - (_proprio.getPosition().x));
	longueurY = abs((mousePosition.y) - (_proprio.getPosition().y));
	hypo = sqrt(longueurX * longueurX + longueurY * longueurY);

	if (mousePosition.y < _proprio.getPosition().y)
	{
		if (mousePosition.x < _proprio.getPosition().x)
		{
			angle = (180 + acos(longueurX / hypo) * 180.0 / 3.141592653589793);
			_armeSprite.setScale(1 / 6.f, -1 / 6.f);
		}
		else if (mousePosition.x > _proprio.getPosition().x)
		{
			angle = 360 - (acos(longueurX / hypo) * 180.0 / 3.141592653589793);
			_armeSprite.setScale(1 / 6.f, 1 / 6.f);
		}
	}
	else if (mousePosition.y > _proprio.getPosition().y)
	{
		if (mousePosition.x > _proprio.getPosition().x)
		{
			angle = acos(longueurX / hypo) * 180.0 / 3.141592653589793;
			_armeSprite.setScale(1 / 6.f, 1 / 6.f);

		}
		else if (mousePosition.x < _proprio.getPosition().x)
		{
			angle = 180 - (acos(longueurX / hypo) * 180.0 / 3.141592653589793);
			_armeSprite.setScale(1 / 6.f, -1 / 6.f);
		}
	}

	_armeSprite.setRotation(angle);
}

void Arme::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_armeSprite);
}