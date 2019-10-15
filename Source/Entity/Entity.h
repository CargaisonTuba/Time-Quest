#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable
{
public:
	Entity();
	Entity(std::string texturePath, int defaultLife, sf::Vector2f initPosition);
	~Entity();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f getPosition();

protected:
	sf::Texture _entityText[11][4];
	sf::Sprite _entitySprite;
	int _spritePosCount, _spritePosCountMax;
	int _dir;	//Haut, bas, ...
	float _animation_tick;

	float _life, _totalLife;
};
