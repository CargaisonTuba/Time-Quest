#pragma once
#include <SFML/Graphics.hpp>
class Cursor : public sf::Drawable
{
public:
	Cursor(std::string texturePath);
	~Cursor();

	sf::Vector2i position;
	sf::Vector2f getPosition();
	void update(sf::Window& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Texture _cursorText;
	sf::Sprite _cursorSprite;
};

