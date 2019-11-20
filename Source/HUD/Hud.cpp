#include "Hud.h"
#include <stdlib.h>

Hud::Hud(Player& player, sf::RenderWindow& window)
{
	_bodyMun.setFillColor(sf::Color::White);
	_bodyMun.setOutlineColor(sf::Color::Black);
	_bodyMun.setOutlineThickness(1);
	_bodyMun.setFillColor(sf::Color(255, 255, 255, 100));
	_bodyMun.setSize(sf::Vector2f(250, 125));
	_bodyMun.setPosition(800, 575);

	_lifeBar.setFillColor(sf::Color::Red);
	//_lifeBar.setPosition(sf::Vector2f(20, 680));
	_lifeBar.setPosition(_bodyMun.getPosition());

	if (!_font.loadFromFile("Time-Quest/Source/arial.ttf"))
	{
		std::cout << "Erreur de police \n";
	}
	_infos.setFont(_font);
	_infos.setCharacterSize(28);
	_infos.setFillColor(sf::Color::Black);
	_infos.setPosition(sf::Vector2f(_bodyMun.getPosition().x + 10, _bodyMun.getPosition().y - 5));
	_infos.setLineSpacing(1.4);
	_healthText.loadFromFile("Time-Quest/Source/assets/health2.png");
	_healthSprite.setTexture(_healthText);
	_healthSprite.setPosition(sf::Vector2f(_infos.getPosition().x + 208, _infos.getPosition().y + 5));

	_smgAmmoText.loadFromFile("Time-Quest/Source/assets/smgammo.png");
	_smgAmmoSprite.setTexture(_smgAmmoText);
	_smgAmmoSprite.setPosition(sf::Vector2f(_healthSprite.getPosition().x, _healthSprite.getPosition().y + 43));

	_grenadeText.loadFromFile("Time-Quest/Source/assets/grenade.png");
	_grenadeSprite.setTexture(_grenadeText);
	_grenadeSprite.setPosition(sf::Vector2f(_healthSprite.getPosition().x, _smgAmmoSprite.getPosition().y + 43));
	_totalAmmo = 200;
}

Hud::~Hud() {

}


void Hud::update(Player& player, sf::RenderWindow& window)
{
	_infos.setString(std::to_string((int)player.getLife()) + "\n" + std::to_string(player.getWeapon()->getMunRest()) + " / " + std::to_string(_totalAmmo) +  "\n" + "3");
	_lifeBar.setSize(sf::Vector2f((player.getLife() * 225) / player.getTotalLife(), 32));
}

void Hud::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	sf::Text infos = _infos;
	infos.setFont(_font);
	infos.setPosition(sf::Vector2f(_bodyMun.getPosition().x + 5, _bodyMun.getPosition().y - 1));

	sf::Sprite health = _healthSprite;
	health.setTexture(_healthText);

	sf::Sprite smgammo = _smgAmmoSprite;
	smgammo.setTexture(_smgAmmoText);
	smgammo.setScale(0.9, 0.9);


	sf::Sprite grenade = _grenadeSprite;
	grenade.setTexture(_grenadeText);
	grenade.setScale(0.9, 0.9);

	target.draw(_bodyMun);
	target.draw(_lifeBar);
	target.draw(infos);
	target.draw(health);
	target.draw(grenade);
	target.draw(smgammo);
}

