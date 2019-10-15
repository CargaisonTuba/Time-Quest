#pragma once
#include <SFML/Graphics.hpp>
#include "./Entity/Entity.h"
#include "./HUD/Cursor.h"

class Arme : public sf::Drawable
{
public:
	
	Arme(std::string texturePath);
	Arme();
	~Arme();

	sf::Vector2i position;
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f unePosition);
	void update(sf::Vector2f playPos, Cursor curseur);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Texture _armeText;
	sf::Sprite _armeSprite;


	float longueurX;
	float longueurY;
	float hypo;
	float angle;
};

