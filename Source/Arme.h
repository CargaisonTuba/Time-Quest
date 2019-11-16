#pragma once
#include <SFML/Graphics.hpp>
#include "./HUD/Cursor.h"
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <time.h>

class Arme : public sf::Drawable
{
public:
	
	Arme(std::string typeArme);
	Arme();
	~Arme();

	sf::Vector2f getOrigin();
	sf::Vector2f getPosition();
	sf::Vector2f imprecision(sf::Vector2f shootDirection);
	void setPosition(sf::Vector2f unePosition);
	void update(sf::Vector2f entityPos, sf::Vector2f playerPos);
	//void update(sf::Vector2f entityPos, sf::Vector2f shootDirection, int a);

	float getDamages() const;
	int getCoolDown();
	
	int getRange();

	//joue le son du tir et diminue le nombre de balle de 1 dans le chargeur (infonctionnel)
	void playTir();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//renvoie l'angle d'inclinaison de l'arme (l'orientation de l'arme quoi)
	float getAngle();
	//renvoie la valeur de l'imprécision de l'arme
	float getImpr();
	int getMunRest();
	void recharger();

	//renvoie si l'arme est prêt à tirer ou pas
	bool getReady();
	sf::Sprite getSprite();

private:
	sf::Texture _armeText;
	sf::Sprite _armeSprite;
	sf::Vector2i _position;
	int _coolDown;

	float longueurX, longueurY;
	float hypo, angle;
	int _impr;

	float _damages;
	int _capacite;
	int _munRest;
	int _reloadTime;
	int _range;

	std::string _soundPath;
	sf::SoundBuffer _tirBuffer;
	sf::Sound _tirSound;
	sf::Clock _timeSinceReload;
	bool _readyState;
};

