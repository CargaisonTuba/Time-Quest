#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Element/Tile.h"
#include "../Arme.h"
#include "../HUD/Cursor.h"

class Entity : public sf::Drawable
{
public:
	Entity(std::string texturePath, int defaultLife, sf::Vector2f initPosition);
	~Entity();

	sf::Vector2f getPosition() const;
	sf::FloatRect getHitbox();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	sf::Texture _entityText[11][4];
	sf::Sprite _entitySprite;
	int _spritePosCount, _spritePosCountMax;
	int _dir;	//Haut, bas, ...
	float _animation_tick;

	float _life, _totalLife;
};
