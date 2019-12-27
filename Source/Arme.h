#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <time.h>

#include "./HUD/Cursor.h"
#include "Element/Object/Object.h"

class Arme : public Object
{
public:
	//Constructeurs 
	Arme(std::string typeArme);
	Arme(std::string typeArme, sf::Vector2f initPosition, bool dropped = false);
	Arme();
	~Arme();
	
	//Setters
	void setPosition(sf::Vector2f unePosition);

	//Getters	
	sf::Vector2f getOrigin();
	sf::Vector2f getPosition();
	sf::Sprite getSprite();
	sf::Sound getTir();
	std::string getBallePath();	
	float getAngle(); //renvoie l'angle d'inclinaison de l'arme (l'orientation de l'arme quoi)
	float getImpr(); //renvoie la valeur de l'imprécision de l'arme
	float getDamages() const;
	int getCoolDown();
	int getMunRest();
	int getMunTotal();
	float getRange();
	bool getReady(); //renvoie si l'arme est prêt à tirer ou pas
	
	//Méthodes	
	void playTir(); //joue le son du tir et diminue le nombre de balle de 1 dans le chargeur (infonctionnel)
	void recharger();

	void update(sf::Vector2f entityPos, sf::Vector2f playerPos);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2f imprecision(sf::Vector2f shootDirection);

private:
	sf::Vector2i _position;

	float _longueurX, _longueurY, _hypo, _angle, _damages, _reloadTime, _impr, _range;
	int _capacite, _coolDown, _munRest;

	std::string _soundPath, _ballePath;
	sf::SoundBuffer _tirBuffer, _emptyBuffer, _reloadBuffer;
	sf::Sound _tirSound, _reloadSound;
	sf::Clock _timeSinceReload;
	bool _readyState;
};

