#pragma once
#include <SFML/Graphics.hpp>

class Cursor : public sf::Drawable
{
public:
	Cursor(std::string texturePath);
	~Cursor();

	sf::Vector2f getPosition();
	void update(sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Texture _cursorText;
	sf::Sprite _cursorSprite;
	sf::Vector2i position;
};

