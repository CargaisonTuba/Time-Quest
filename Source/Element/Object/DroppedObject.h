#pragma once

#include <SFML/Graphics.hpp>

class DroppedObject : public sf::Drawable
{
public:
	DroppedObject();
	~DroppedObject();

	int getID() const;
	sf::Vector2f getPosition() const;
	sf::FloatRect getHitbox();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	int _id;

	sf::Sprite _sprite;
	sf::Texture _text;
};
