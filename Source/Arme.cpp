#include "Arme.h"
#include <iostream>


Arme::Arme(std::string typeArme)
{
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
		for (int i = 0; (unsigned)i < listeArmeVect.size(); i++)
		{
			if (listeArmeVect[i] == typeArme)
			{
				//On charge la texture via le chemin dans le mot suivant
				if (!_objectText.loadFromFile(listeArmeVect[i + 1]))
					std::cout << "\x1B[31m[Erreur]\x1B[0m : Texture Arme : impossible de charger " << listeArmeVect[i + 1] << std::endl;
				//_armeSprite.setTexture(_armeText);

				//On charge le son via le chemin dans le 2è mot suivant
				if (!_tirBuffer.loadFromFile(listeArmeVect[i + 2]))
					std::cout << "\x1B[31m[Erreur]\x1B[0m : SoundBuffer : impossible de charger " << listeArmeVect[i + 2] << std::endl;

				//_tirSound.setBuffer(_tirBuffer);

				//On attribue au cool down le 3è mot suivant (casté de string à int via stoi)
				_coolDown = std::stoi(listeArmeVect[i+3]);

				//On attribue la capacité du chargeur au 4è mot suivant casté de string à int
				_capacite = std::stoi(listeArmeVect[i + 4]);

				//De la même façon paramètre l'origine de l'arme
				_objectSprite.setOrigin(std::stof(listeArmeVect[i + 5]), std::stof(listeArmeVect[i + 6]));

				//Idem pour dégâts de l'arme
				_damages = std::stof(listeArmeVect[i + 7]);

				//Idem pour la portée
				_range = std::stof(listeArmeVect[i + 8]);

				//Temps de rechargement
				_reloadTime = std::stof(listeArmeVect[i + 9]);

				//Imprécision de l'arme
				_impr = std::stof(listeArmeVect[i + 10]);

				//Chemin de la texture de la balle de l'arme
				_ballePath = listeArmeVect[i + 11];

				//Chemin du son de rechargement
				if (!_reloadBuffer.loadFromFile(listeArmeVect[i + 12]))
					std::cout << "\x1B[31m[Erreur]\x1B[0m : SoundBuffer : impossible de charger " << listeArmeVect[i + 12] << std::endl;

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

	_angle = 0;
	_longueurX = 0;
	_longueurY = 0;
	_hypo = 0;
	_munRest = _capacite;
	_readyState = true;

	if (!_emptyBuffer.loadFromFile("Time-Quest/Source/assets/sound/clicpasboum.wav"))
		std::cout << "\x1B[31m[Erreur]\x1B[0m : SoundBuffer : impossible de charger " << "Time-Quest/Source/assets/sound/clicpasboum.wav" << std::endl;
	_type = WEAPON;
}

Arme::Arme(std::string typeArme, sf::Vector2f initPosition, bool dropped) : Arme(typeArme) {
	_initPosition = initPosition;
	_isDropped = dropped;
	if (_isDropped) {
		std::cout << "dropped\n";
		_objectSprite.setScale(sf::Vector2f(0.2f, 0.2f));
		_objectSprite.setPosition(_initPosition);
	}
	_type = WEAPON;
}

Arme::Arme()
{
	_angle = 0;
	_longueurX = 0;
	_longueurY = 0;
	_hypo = 0;
	_damages = 0;
	_coolDown = 0;
	_capacite = 0;
	_munRest = 0;
	_range = 0;
	_readyState = 0;
	_reloadTime = 0;
	_type = 0;
}

Arme::~Arme()
{

}

//Setters
void Arme::setPosition(sf::Vector2f unePosition)
{
	_objectSprite.setPosition(unePosition);
}

//Getters
sf::Vector2f Arme::getOrigin()
{
	return _objectSprite.getOrigin();
}

sf::Vector2f Arme::getPosition()
{
	return _objectSprite.getPosition();
}

sf::Sprite Arme::getSprite()
{
	return this->_objectSprite;
}

sf::Sound Arme::getTir()
{
	return this->_tirSound;
}

std::string Arme::getBallePath()
{
	return this->_ballePath;
}

float Arme::getAngle()
{
	return this->_angle;
}

float Arme::getImpr()	//imprécision de l'arme
{
	return this->_impr;
}


float Arme::getDamages() const {
	return _damages;
}

int Arme::getCoolDown()
{
	return this->_coolDown;
}

int Arme::getMunRest()
{
	return this->_munRest;
}

int Arme::getMunTotal()
{
	return this->_capacite;
}

float Arme::getRange()
{
	return this->_range;
}

bool Arme::getReady()
{
	//std::cout << _readyState <<"\n";
	return this->_readyState;
}

//Méthodes
void Arme::playTir()
{
	if (_readyState) {
		_tirSound.setBuffer(_tirBuffer);
		_munRest--;
	}
	else {
		//clic pas boum
		_tirSound.setBuffer(_emptyBuffer);
	}
	_tirSound.play();


	//std::cout << "\x1B[33m[info]\x1B[0m : Munitions : \x1B[35m " << _munRest << " \x1B[0m / " << _capacite << "\n";
}

void Arme::recharger()
{
	if ((float)(_timeSinceReload.getElapsedTime().asMilliseconds()) > _reloadTime)
	{
		_reloadSound.setBuffer(_reloadBuffer);
		_reloadSound.play();
		//std::cout << "\x1B[33m[info]\x1B[0m : Rechargement ...\n";
		_timeSinceReload.restart();
		_readyState = false;
		this->_munRest = this->_capacite;
	}
}

//Update des armes
void Arme::update(sf::Vector2f entityPos, sf::Vector2f shootPosition)
{
	_longueurX = abs((shootPosition.x) - (entityPos.x));
	_longueurY = abs((shootPosition.y) - (entityPos.y));
	_hypo = sqrt(_longueurX * _longueurX + _longueurY * _longueurY);

	if (shootPosition.y < entityPos.y)
	{
		if (shootPosition.x < entityPos.x)
		{
			_angle = (180.f + acos(_longueurX / _hypo) * 180.0f / (float)3.141592653589793);
			_objectSprite.setScale(1.f / 6.f, -1.f / 6.f);
			this->setPosition(sf::Vector2f(entityPos.x - 15, entityPos.y - 10));
		}
		else if (shootPosition.x > entityPos.x)
		{
			_angle = 360.f - (acos(_longueurX / _hypo) * 180.0f / (float)3.141592653589793);
			_objectSprite.setScale(1.f / 6.f, 1.f / 6.f);
			this->setPosition(sf::Vector2f(entityPos.x - 12, entityPos.y - 10));
		}

	}
	else if (shootPosition.y > entityPos.y)
	{
		if (shootPosition.x > entityPos.x)
		{
			_angle = acos(_longueurX / _hypo) * 180.0f / (float)3.141592653589793;
			_objectSprite.setScale(1.f / 6.f, 1.f / 6.f);
			if (_angle > 45 && _angle < 135)
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
			_angle = 180.f - (acos(_longueurX / _hypo) * 180.0f / (float)3.141592653589793);
			_objectSprite.setScale(1.f / 6.f, -1.f / 6.f);
			if (_angle > 45 && _angle < 135)
			{
				this->setPosition(sf::Vector2f(entityPos.x - 15, entityPos.y - 8));
			}
			else
			{
				this->setPosition(sf::Vector2f(entityPos.x - 15, entityPos.y - 10));
			}
		}

	}
  
	_objectSprite.setRotation(_angle);
	if ((float)(_timeSinceReload.getElapsedTime().asMilliseconds()) > _reloadTime && this->_readyState == false && this->_munRest > 0)
	{
		this->_readyState = true;
		//std::cout << "\x1B[32m[OK]\x1B[0m : Arme prete !" << std::endl;
	}
	if (this->_munRest == 0 && this->_readyState)
	{
		this->_readyState = false;
	}
}

sf::Vector2f Arme::imprecision(sf::Vector2f shootDirection)
{

	float a = -_impr;
	float b = _impr;
	int imprX = rand() % (int)((b - a) + a);
	int imprY = rand() % (int)((b - a) + a);
	return sf::Vector2f(shootDirection.x + imprX, shootDirection.y + imprY);
}

void Arme::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite s = _objectSprite;
	s.setTexture(_objectText);

	s.move(13, 13);	//on centre l'arme
	target.draw(s);
}