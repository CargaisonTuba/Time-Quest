#pragma once
#include <SFML/Graphics.hpp>
#include "./HUD/Cursor.h"

class Arme : public sf::Drawable
{
public:
	
	Arme(std::string texturePath, float damages);
	Arme();
	~Arme();

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f unePosition);
	void update(sf::Vector2f entityPos);
	void update(sf::Vector2f entityPos, Cursor cursor);

	float getDamages() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Texture _armeText;
	sf::Sprite _armeSprite;
	sf::Vector2i position;

	float longueurX, longueurY;
	float hypo, angle;

	float _damages;
};

