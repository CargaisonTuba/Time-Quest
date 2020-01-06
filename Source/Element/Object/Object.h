#pragma once
#include <SFML/Graphics.hpp>

class Object : public sf::Drawable
{
public:
	Object(std::string texturePath, sf::Vector2f initPosition);
	Object();
	~Object();

	bool update();
	void setDropped(bool dropped);
	void resetAngle();
	sf::Vector2f getPosition() const;
	sf::FloatRect getHitbox() const;

	int getType() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	std::time_t _creationDate;
	sf::Vector2f _initPosition;
	sf::Texture _objectText;
	sf::Sprite _objectSprite;

	int _type;

	bool _isDropped;
};

