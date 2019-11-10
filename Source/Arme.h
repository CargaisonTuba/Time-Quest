#pragma once
#include <SFML/Graphics.hpp>
#include "./HUD/Cursor.h"
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>

class Arme : public sf::Drawable
{
public:
	
	Arme(std::string typeArme);
	Arme();
	~Arme();

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f unePosition);
	void update(sf::Vector2f entityPos);
	void update(sf::Vector2f entityPos, Cursor cursor);

	float getDamages() const;
	int getCoolDown();
	
	void playTir();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Texture _armeText;
	sf::Sprite _armeSprite;
	sf::Vector2i _position;
	int _coolDown;

	float longueurX, longueurY;
	float hypo, angle;

	float _damages;
	int _capacite;
	int _munRest;

	std::string _soundPath;
	sf::SoundBuffer _tirBuffer;
	sf::Sound _tirSound;
};

