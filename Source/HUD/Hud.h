#pragma once
#include <SFML/Graphics.hpp>

class Hud : public sf::Drawable
{
public:
	Hud();
	~Hud();

	void update(bool pause);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

