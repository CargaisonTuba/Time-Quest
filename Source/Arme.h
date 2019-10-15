#pragma once
#include <SFML/Graphics.hpp>
#include "./Entity/Entity.h"

class Arme : public sf::Drawable
{
public:
	Arme(std::string texturePath);
	~Arme();

	sf::Vector2i position;
	sf::Vector2f getPosition();
	void setProprio(Entity proprioP);
	Entity getProprio();
	void setPosition(sf::Vector2f unePosition);
	void update(sf::Vector2f mousePosition);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Texture _armeText;
	sf::Sprite _armeSprite;
	Entity _proprio;
};

