#pragma once
#include <SFML/Graphics.hpp>

class Object
{
public:
	Object(sf::Vector2f throwerPosition, sf::Vector2f direction);
	Object();
	~Object();

	bool update();
	sf::CircleShape* getBody();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	sf::CircleShape _body;
	std::time_t _creationDate;
	sf::Vector2f _direction;
	
};

