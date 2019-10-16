#pragma once
#include <SFML/Graphics.hpp>

class Object
{
public:
	Object();
	~Object();

	bool update();
	sf::CircleShape* getBody();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	sf::CircleShape _body;

};

