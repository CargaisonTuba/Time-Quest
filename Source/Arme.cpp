#include "Arme.h"
#include <iostream>

Arme::Arme(std::string texturePath)
{
	if (!_armeText.loadFromFile(texturePath))
	{
		std::cout << "Erreur text arme\n";
	}
	_armeSprite.setTexture(_armeText);
	_armeSprite.setScale(sf::Vector2f(1, 1));

	angle = 0;
	longueurX = 0;
	longueurY = 0;
	hypo = 0;
	std::cout << "Ceci est le constructeur normal\n";
}

Arme::Arme()
{
	angle = 0;
	longueurX = 0;
	longueurY = 0;
	hypo = 0;
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

void Arme::update(sf::Vector2f playPos, Cursor curseur)
{
	this->setPosition(playPos);
	
	sf::Vector2f mousePosition = curseur.getPosition();

	//std::cout << "Pos x : " << this->getPosition().x << " Pos y : " << this->getPosition().y << " Curseur X : " << mousePosition.x << " Curseur Y : " << mousePosition.y << "\n";

	longueurX = abs((mousePosition.x) - (playPos.x));
	longueurY = abs((mousePosition.y) - (playPos.y));
	hypo = sqrt(longueurX * longueurX + longueurY * longueurY);

	if (mousePosition.y < playPos.y)
	{
		if (mousePosition.x < playPos.x)
		{
			angle = (180 + acos(longueurX / hypo) * 180.0 / 3.141592653589793);
			_armeSprite.setScale(1 / 6.f, -1 / 6.f);
		}
		else if (mousePosition.x > playPos.x)
		{
			angle = 360 - (acos(longueurX / hypo) * 180.0 / 3.141592653589793);
			_armeSprite.setScale(1 / 6.f, 1 / 6.f);
		}
	}
	else if (mousePosition.y > playPos.y)
	{
		if (mousePosition.x > playPos.x)
		{
			angle = acos(longueurX / hypo) * 180.0 / 3.141592653589793;
			_armeSprite.setScale(1 / 6.f, 1 / 6.f);

		}
		else if (mousePosition.x < playPos.x)
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
	sf::Texture t;
	t.loadFromFile("Time-Quest/Source/assets/mas36final2.png");
	s.setTexture(t);
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		s.setScale(sf::Vector2f(0.05f, 0.05f));

	target.draw(s);
}