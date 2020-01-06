#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Hud : public sf::Drawable
{
public:
	Hud(sf::RenderWindow& window);
	~Hud();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float pLife, float pTotalLife, int pMunRest, int pMunTotal);
	void addMessage(std::string who, std::string message);
	int getMessagesNumber() const;
	void lockMessages(bool cond = true);
	void setGamePaused(bool pause);
	bool isGameInit() const;
	void setGameInit(bool init);
	void setCurrentQuest(std::string curQuestName);
	void setQuestActive(bool quest);
	//void addMessage(std::string &who, std::vector<std::string> &message);

private:
	int _totalAmmo;
	sf::RectangleShape _bodyMun;
	sf::RectangleShape _lifeBar;
	sf::Font _font;
	sf::Text _infos;
	sf::Text _life;
	sf::Text _grenade;

	sf::Text _textPause;
	sf::RectangleShape _greyScreenPause;

	bool _canAddMessages;
	std::vector<sf::Text> _messages, _messagesAuthors;
	sf::RectangleShape _msgBorders;
	sf::Clock _timerMsg;
	sf::Text _currentQuestName, _currentQuestDescription;
	sf::Texture _healthText;
	sf::Texture _smgAmmoText;
	sf::Texture _grenadeText;
	sf::Sprite _healthSprite;
	sf::Sprite _smgAmmoSprite;
	sf::Sprite _grenadeSprite;
	bool _gamePause;

	bool _gameInit;
	sf::Clock _clockInit;
	std::vector<sf::Text> _initMessages;
	sf::RectangleShape _initBg;

	sf::RectangleShape _questBorder;
	sf::Text _questName;
	sf::Text _currentQuest;
	bool _questExist, _showNoMoreQuest;
};
