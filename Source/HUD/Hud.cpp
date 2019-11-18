#include "Hud.h"
#include <stdlib.h>

Hud::Hud(Player& player, sf::RenderWindow &window)
{
	_bodyMun.setFillColor(sf::Color::White);
	_bodyMun.setOutlineColor(sf::Color::Black);
	_bodyMun.setOutlineThickness(1);
	_bodyMun.setFillColor(sf::Color(255, 255, 255, 100));
	_bodyMun.setSize(sf::Vector2f(100,50));

	_lifeBar.setFillColor(sf::Color::Red);
	_lifeBar.setPosition(sf::Vector2f(20, 680));

	if (!_font.loadFromFile("Time-Quest/Source/arial_narrow_7.ttf"))
	{
		std::cout << "Erreur de police \n";
	}
	_mun.setFont(_font);
	_mun.setCharacterSize(15);
	_mun.setFillColor(sf::Color::Black);

	_healthText.loadFromFile("Time-Quest/Source/assets/health.png");
	_healthSprite.setTexture(_healthText);

	_smgAmmoText.loadFromFile("Time-Quest/Source/assets/smgammoico.png");
	_smgAmmoSprite.setTexture(_smgAmmoText);

	_grenadeText.loadFromFile("Time-Quest/Source/assets/grenadeico.png");
	_grenadeSprite.setTexture(_grenadeText);
}

Hud::~Hud() 
{

}

void Hud::update(Player& player, sf::RenderWindow &window) 
{
	_bodyMun.setPosition(window.mapPixelToCoords(sf::Vector2i(800, 550)));
	_lifeBar.setPosition(window.mapPixelToCoords(sf::Vector2i(800, 550)));
	_mun.setPosition(window.mapPixelToCoords(sf::Vector2i(810, 560)));
	_mun.setString(std::to_string((int)player.getLife()) + "\n" + std::to_string(player.getWeapon().getMunRest()) + " / 200 \n"  + "3");
	//On met la barre de vie du joueur à jour
	_lifeBar.setSize(sf::Vector2f((player.getLife()*70) / player.getTotalLife(), 16));
}

void Hud::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	
	sf::Text mun = _mun;
	mun.setFont(_font);
	mun.setPosition(sf::Vector2f(_bodyMun.getPosition().x + 5, _bodyMun.getPosition().y-1));
	
	sf::Sprite health;
	health.setTexture(_healthText);
	health.setPosition(sf::Vector2f(mun.getPosition().x + 65, mun.getPosition().y + 1));

	sf::Sprite smgammo;
	smgammo.setTexture(_smgAmmoText);
	smgammo.setScale(0.9, 0.9);
	smgammo.setPosition(sf::Vector2f(mun.getPosition().x + 65, mun.getPosition().y + 17));
	

	sf::Sprite grenade;
	grenade.setTexture(_grenadeText);
	grenade.setScale(0.9, 0.9);
	grenade.setPosition(sf::Vector2f(mun.getPosition().x + 65, mun.getPosition().y + 32));

	target.draw(_bodyMun);
	target.draw(_lifeBar);
	target.draw(mun);
	target.draw(health);
	target.draw(grenade);
	target.draw(smgammo);
}
