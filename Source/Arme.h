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
	//Constructeurs 
	Arme(std::string typeArme);
	Arme();
	~Arme();
	
	//Setters
	void setPosition(sf::Vector2f unePosition);

	//Getters	
	sf::Vector2f getOrigin();
	sf::Vector2f getPosition();

	sf::Sprite getSprite();
		
	float getAngle(); //renvoie l'angle d'inclinaison de l'arme (l'orientation de l'arme quoi)
	float getImpr(); //renvoie la valeur de l'impr�cision de l'arme
	float getDamages() const;

	int getCoolDown();
	int getMunRest();
	int getRange();
	
	bool getReady(); //renvoie si l'arme est pr�t � tirer ou pas
	
	//M�thodes	
	void playTir(); //joue le son du tir et diminue le nombre de balle de 1 dans le chargeur (infonctionnel)
	void recharger();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::Vector2f entityPos, sf::Vector2f playerPos);

	sf::Vector2f imprecision(sf::Vector2f shootDirection);

private:
	sf::Texture _armeText;
	sf::Sprite _armeSprite;
	sf::Vector2i _position;

	float _longueurX, _longueurY, _hypo, _angle, _damages;
	int _capacite, _coolDown, _munRest, _reloadTime, _range, _impr;

	std::string _soundPath;
	sf::SoundBuffer _tirBuffer;
	sf::Sound _tirSound;
	sf::Clock _timeSinceReload;
	bool _readyState;
};

