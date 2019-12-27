#pragma once
#include <SFML/Graphics.hpp>
#include "../Entity/Player.h"
#include "../Scene/Map.h"

class Hud : public sf::Drawable
{
public:
	Hud(Player& player, sf::RenderWindow& window);
	~Hud();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(Player& player, sf::RenderWindow& window, Map& map);

private:
	int _totalAmmo;
	sf::RectangleShape _bodyMun;
	sf::RectangleShape _lifeBar;
	sf::Font _font;
	sf::Text _infos;
	sf::Text _life;
	sf::Text _grenade;
	sf::Text _currentQuestName, _currentQuestDescription;
	sf::Texture _healthText;
	sf::Texture _smgAmmoText;
	sf::Texture _grenadeText;
	sf::Sprite _healthSprite;
	sf::Sprite _smgAmmoSprite;
	sf::Sprite _grenadeSprite;
};
