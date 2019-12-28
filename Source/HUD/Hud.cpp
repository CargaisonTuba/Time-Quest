#include "Hud.h"
#include <stdlib.h>

Hud::Hud()
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

	_msgBorders.setPosition(sf::Vector2f(20, 600));
	_msgBorders.setSize(sf::Vector2f(600, 100));
	_msgBorders.setOutlineColor(sf::Color::Black);
	_msgBorders.setFillColor(sf::Color(255, 255, 255, 128));
	_msgBorders.setOutlineThickness(2);

	_canAddMessages = true;
}

Hud::~Hud() {

}


void Hud::update(float pLife, float pTotalLife, int pMunRest, int pMunTotal)
{
	_infos.setString(std::to_string((int)pLife) + "\n" + std::to_string(pMunRest) + " / " + std::to_string(pMunTotal) +  "\n" + "3");
	_lifeBar.setSize(sf::Vector2f((pLife * 225) / pTotalLife, 32));

	if (_timerMsg.getElapsedTime().asSeconds() > 3 && !_messages.empty()) {
		_messages.erase(_messages.begin());
		_timerMsg.restart();
	}
}

void Hud::addMessage(std::string who, std::string message) {
	if (_canAddMessages) {
		if (_messages.size() <= 0) {
			_timerMsg.restart();
		}
		sf::Text msg;
		msg.setFont(_font);
		msg.setString(message);
		msg.setFillColor(sf::Color::Red);
		msg.setPosition(sf::Vector2f(30, 610));
		_messages.push_back(msg);
	}
}

int Hud::getMessagesNumber() const {
	return _messages.size();
}

void Hud::lockMessages(bool cond) {
	_canAddMessages = !cond;	//issou
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

	if (_messages.size() > 0) {
		target.draw(_msgBorders);
		target.draw(_messages[0]);
	}
}

