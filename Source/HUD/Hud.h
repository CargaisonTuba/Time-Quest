#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Hud : public sf::Drawable
{
public:
	Hud();
	~Hud();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float pLife, float pTotalLife, int pMunRest, int pMunTotal);
	void addMessage(std::string who, std::string message);
	int getMessagesNumber() const;
	void lockMessages(bool cond = true);
	//void addMessage(std::string &who, std::vector<std::string> &message);

private:
	int _totalAmmo;
	sf::RectangleShape _bodyMun;
	sf::RectangleShape _lifeBar;
	sf::Font _font;
	sf::Text _infos;
	sf::Text _life;
	sf::Text _grenade;
	bool _canAddMessages;
	std::vector<sf::Text> _messages;
	sf::RectangleShape _msgBorders;
	sf::Clock _timerMsg;
	sf::Text _currentQuestName, _currentQuestDescription;
	sf::Texture _healthText;
	sf::Texture _smgAmmoText;
	sf::Texture _grenadeText;
	sf::Sprite _healthSprite;
	sf::Sprite _smgAmmoSprite;
	sf::Sprite _grenadeSprite;
};
