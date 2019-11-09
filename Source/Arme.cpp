#include "Arme.h"
#include <iostream>

Arme::Arme(std::string texturePath, float damages)
{
	if (!_armeText.loadFromFile(texturePath))
	{
		std::cout << "Erreur text arme\n";
	}
	
	_armeSprite.setTexture(_armeText);
	if (texturePath == "Time-Quest/Source/assets/mas36.png")
	{
		_armeSprite.setOrigin(65.f, -15.f);
		_coolDown = 1000;
		_capacite = 5;
		_soundPath = "Time-Quest/Source/assets/sound/mas36shoot.wav";
	}
	if (texturePath == "Time-Quest/Source/assets/mas38.png")
	{
		_armeSprite.setOrigin(55.f, -15.f);
		_coolDown = 200;
		_capacite = 30;
		_soundPath = "Time-Quest/Source/assets/sound/mas38shoot.wav";
	}
	if (texturePath == "Time-Quest/Source/assets/mp40s.png")
	{
		_armeSprite.setOrigin(55.f, -15.f);
		_coolDown = 200;
		_capacite = 30;
	}
	if (!_tirBuffer.loadFromFile(_soundPath))
	{
		std::cout << "Erreur sound buffer\n";
	}
	_tirSound.setBuffer(_tirBuffer);
	angle = 0;
	longueurX = 0;
	longueurY = 0;
	hypo = 0;
	_damages = damages;
	_munRest = _capacite;
	
}

Arme::Arme()
{
	angle = 0;
	longueurX = 0;
	longueurY = 0;
	hypo = 0;
	_damages = 0;
	_coolDown = 0;
	_capacite = 0;
	_munRest = 0;
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

float Arme::getCoolDown()
{
	return this->_coolDown;
}


//Update des armes des ennemis
void Arme::update(sf::Vector2f entityPos) {
	this->setPosition(entityPos);
	_armeSprite.setScale(0.3f, 0.3f);
}

//update de l'arme du joueur
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
			angle = (180.f + acos(longueurX / hypo) * 180.0f / (float)3.141592653589793);
			_armeSprite.setScale(1.f / 6.f, -1.f / 6.f);
		}
		else if (mousePosition.x > entityPos.x)
		{
			angle = 360.f - (acos(longueurX / hypo) * 180.0f / (float)3.141592653589793);
			_armeSprite.setScale(1.f / 6.f, 1.f / 6.f);
		}
	}
	else if (mousePosition.y > entityPos.y)
	{
		if (mousePosition.x > entityPos.x)
		{
			angle = acos(longueurX / hypo) * 180.0f / (float)3.141592653589793;
			_armeSprite.setScale(1.f / 6.f, 1.f / 6.f);

		}
		else if (mousePosition.x < entityPos.x)
		{
			angle = 180.f - (acos(longueurX / hypo) * 180.0f / (float)3.141592653589793);
			_armeSprite.setScale(1.f / 6.f, -1.f / 6.f);
		}
	}

	_armeSprite.setRotation(angle);
}

void Arme::playTir()
{
	_tirSound.play();
	std::cout << "poum!\n";
}

float Arme::getDamages() const {
	return _damages;
}

void Arme::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite s = _armeSprite;
	s.setTexture(_armeText);
	

	s.move(13, 13);	//on centre l'arme
	target.draw(s);
}