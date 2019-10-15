#include "Arme.h"
#include <iostream>

Arme::Arme(std::string texturePath)
{
	if (!_armeText.loadFromFile(texturePath))
	{
		std::cout << "Erreur text arme\n";
	}
	_armeSprite.setTexture(_armeText);
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
	if (mousePosition.y < _proprio.getPosition().y)
	{
		if (mousePosition.x < _proprio.getPosition().x)
		{

			_armeSprite.setScale(1 / 6.f, -1 / 6.f);
		}
		else if (mousePosition.x > _proprio.getPosition().x)
		{
			_armeSprite.setScale(1 / 6.f, 1 / 6.f);
		}
	}
	else if (mousePosition.y > _proprio.getPosition().y)
	{
		if (mousePosition.x > _proprio.getPosition().x)
		{
			_armeSprite.setScale(1 / 6.f, 1 / 6.f);

		}
		else if (mousePosition.x < _proprio.getPosition().x)
		{
			_armeSprite.setScale(1 / 6.f, -1 / 6.f);
		}
	}
}

void Arme::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_armeSprite);
}