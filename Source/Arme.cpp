#include "Arme.h"
#include <iostream>


Arme::Arme(std::string typeArme)
{
	srand(time(NULL));
	std::ifstream listeArme("Time-Quest/Source/arme.txt");
	if (listeArme)
	{
		std::vector<std::string> listeArmeVect;
		std::string mot;

		//On stocke tous les mots du fichier arme.txt dans un tableau
		while (listeArme >> mot)
		{
			//std::cout << mot << "\n";
			listeArmeVect.push_back(mot);
		}

		//On parcourt le table et si on trouve dans le tableau le nom de l'arme (typeArme), alors :
		for (int i = 0; i < listeArmeVect.size(); i++)
		{
			if (listeArmeVect[i] == typeArme)
			{
				//On charge la texture via le chemin dans le mot suivant
				if (!_armeText.loadFromFile(listeArmeVect[i + 1]))
				{
					std::cout << "\x1B[31m[Erreur]\x1B[0m : Texture Arme : impossible de charger " << listeArmeVect[i + 1] << std::endl;;
				}
				_armeSprite.setTexture(_armeText);

				//On charge le son via le chemin dans le 2è mot suivant
				if (!_tirBuffer.loadFromFile(listeArmeVect[i + 2]))
				{
					std::cout << "\x1B[31m[Erreur]\x1B[0m : SoundBuffer : impossible de charger " << listeArmeVect[i + 2] << std::endl;
				}
				_tirSound.setBuffer(_tirBuffer);

				//On attribue au cool down le 3è mot suivant (casté de string à int via stoi)
				_coolDown = std::stoi(listeArmeVect[i+3]);

				//On attribue la capacité du chargeur au 4è mot suivant casté de string à int
				_capacite = std::stoi(listeArmeVect[i + 4]);

				//De la même façon paramètre l'origine de l'arme
				_armeSprite.setOrigin(std::stoi(listeArmeVect[i + 5]), std::stoi(listeArmeVect[i + 6]));

				//Idem pour dégâts de l'arme
				_damages = std::stof(listeArmeVect[i + 7]);

				//Idem pour la portée
				_range = std::stoi(listeArmeVect[i + 8]);

				//Temps de rechargement
				_reloadTime = std::stoi(listeArmeVect[i + 9]);

				_impr = std::stof(listeArmeVect[i + 11]);

				break;

			}
		}
	}
	else
	{
		_damages = 0;
		_coolDown = 0;
		_munRest = 0;
		_readyState = false;
		_capacite = 0;
		_reloadTime = 0;
	}
	angle = 0;
	longueurX = 0;
	longueurY = 0;
	hypo = 0;
	_munRest = _capacite;
	_readyState = true;
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
	_range = 0;
	_readyState = 0;
	_reloadTime = 0;
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
sf::Vector2f Arme::getOrigin()
{
	return _armeSprite.getOrigin();
}

int Arme::getCoolDown()
{
	return this->_coolDown;
}

//Update des armes
void Arme::update(sf::Vector2f entityPos, sf::Vector2f shootPosition) 
{
	longueurX = abs((shootPosition.x) - (entityPos.x));
	longueurY = abs((shootPosition.y) - (entityPos.y));
	hypo = sqrt(longueurX * longueurX + longueurY * longueurY);

	if (shootPosition.y < entityPos.y)
	{
		if (shootPosition.x < entityPos.x)
		{
			angle = (180.f + acos(longueurX / hypo) * 180.0f / (float)3.141592653589793);
			_armeSprite.setScale(1.f / 6.f, -1.f / 6.f);
			this->setPosition(sf::Vector2f(entityPos.x - 15, entityPos.y - 10));
		}
		else if (shootPosition.x > entityPos.x)
		{
			angle = 360.f - (acos(longueurX / hypo) * 180.0f / (float)3.141592653589793);
			_armeSprite.setScale(1.f / 6.f, 1.f / 6.f);
			this->setPosition(sf::Vector2f(entityPos.x - 12, entityPos.y - 10));
		}

	}
	else if (shootPosition.y > entityPos.y)
	{
		if (shootPosition.x > entityPos.x)
		{
			angle = acos(longueurX / hypo) * 180.0f / (float)3.141592653589793;
			_armeSprite.setScale(1.f / 6.f, 1.f / 6.f);
			if (angle > 45 && angle < 135)
			{
				this->setPosition(sf::Vector2f(entityPos.x - 12, entityPos.y - 8));
			}
			else
			{
				this->setPosition(sf::Vector2f(entityPos.x - 12, entityPos.y - 10));
			}
		}
		else if (shootPosition.x < entityPos.x)
		{
			angle = 180.f - (acos(longueurX / hypo) * 180.0f / (float)3.141592653589793);
			_armeSprite.setScale(1.f / 6.f, -1.f / 6.f);
			if (angle > 45 && angle < 135)
			{
				this->setPosition(sf::Vector2f(entityPos.x - 15, entityPos.y - 8));
			}
			else
			{
				this->setPosition(sf::Vector2f(entityPos.x - 15, entityPos.y - 10));
			}
		}

	}
	_armeSprite.setRotation(angle);
	if (_timeSinceReload.getElapsedTime() > sf::milliseconds(_reloadTime))
	{
		this->_readyState = true;
	}
	if (this->_munRest == 0)
	{
		this->_readyState = false;
	}
}


void Arme::playTir()
{
	_tirSound.setBuffer(_tirBuffer);
	_tirSound.play();
	_munRest--;
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

float Arme::getAngle()
{
	return this->angle;
}

float Arme::getImpr()
{
	return this->_impr;
}

int Arme::getMunRest()
{
	return this->_munRest;
}

void Arme::recharger()
{
	//std::cout << _readyState << " recharchement\n";
	_timeSinceReload.restart();
	_readyState = false;
	//std::cout << _readyState << "\n";
	this->_munRest = this->_capacite;
}

bool Arme::getReady()
{
	//std::cout << _readyState <<"\n";
	return this->_readyState;
}

int Arme::getRange()
{
	return this->_range;
}

sf::Sprite Arme::getSprite()
{
	return this->_armeSprite;
}

sf::Vector2f Arme::imprecision(sf::Vector2f shootDirection)
{
	
	int a = -_impr;
	int b = _impr;
	int imprX = rand() % (b - a) + a;
	int imprY = rand() % (b - a) + a;
	std::cout << "Imprévision vaut : " << _impr << " a vaut : " << a << " b vaut : " << b << " imprX vaut : " << imprX << " imprX vaut : " << imprY << "\n";
	return sf::Vector2f(shootDirection.x + imprX, shootDirection.y + imprY);
}