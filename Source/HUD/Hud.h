#pragma once
#include <SFML/Graphics.hpp>
#include "../Entity/Player.h"

class Hud : public sf::Drawable
{
public:
	Hud(Player& player, sf::RenderWindow &window);
	~Hud();

	void update(Player& player, sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::RectangleShape _bodyMun;
	sf::RectangleShape _lifeBar;
	sf::Font _font;
	sf::Text _mun;
	sf::Text _life;
	sf::Text _grenade;
	sf::Texture _healthText;
	sf::Texture _smgAmmoText;
	sf::Texture _grenadeText;
	sf::Sprite _healthSprite;
	sf::Sprite _smgAmmoSprite;
	sf::Sprite _grenadeSprite;
};

