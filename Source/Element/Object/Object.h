#pragma once
#include <SFML/Graphics.hpp>

class Object
{
public:
	Object(std::string texturePath, sf::Vector2f throwerPosition, sf::Vector2f direction);
	Object();
	~Object();

	bool update();
	//sf::CircleShape& getBody();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f getDirection();

	sf::FloatRect getHitbox() const;

protected:
	std::time_t _creationDate;
	sf::Vector2f _direction;
	sf::Vector2f _posInit;
	sf::Texture _objectText;
	sf::Sprite _objectSprite;
	
};

