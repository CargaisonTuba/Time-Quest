#include "Hud.h"
#include <stdlib.h>

Hud::Hud(sf::RenderWindow &window)
{
	_bodyMun.setFillColor(sf::Color::White);
	_bodyMun.setOutlineColor(sf::Color::Black);
	_bodyMun.setOutlineThickness(1);
	_bodyMun.setFillColor(sf::Color(255, 255, 255, 100));
	_bodyMun.setSize(sf::Vector2f(250, 125));
	_bodyMun.setPosition(1600, 800);

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

	_msgBorders.setPosition(sf::Vector2f(50, 800));
	_msgBorders.setSize(sf::Vector2f(1200, 200));
	_msgBorders.setOutlineColor(sf::Color::Black);
	_msgBorders.setFillColor(sf::Color(255, 255, 255, 128));
	_msgBorders.setOutlineThickness(2);

	_canAddMessages = true;

	_textPause.setFont(_font);
	_textPause.setString("pause");
	_textPause.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	
	_greyScreenPause.setSize((sf::Vector2f)window.getSize());
	_greyScreenPause.setFillColor(sf::Color(0, 0, 0, 128));

	_gameInit = true;
	_gamePause = false;

	sf::Text initMsg;
	initMsg.setFont(_font);
	initMsg.setFillColor(sf::Color::Black);
	initMsg.setPosition(sf::Vector2f(window.getSize().x / 4 , window.getSize().y / 4));
	initMsg.setString("time quest ecran de démarrage yo\n\nHugo, Fergal, Robin\n\nSi quelqu'un est motivé go il change le design mdr");
	_initMessages.push_back(initMsg);
	initMsg.setString("Vous etes un gendarme du temps blabla");
	_initMessages.push_back(initMsg);

	_initBg.setSize((sf::Vector2f)window.getSize());
	_initBg.setFillColor(sf::Color::White);

	_questExist = false;

	_questBorder.setPosition(sf::Vector2f(50, 80));
	_questBorder.setFillColor(sf::Color(255, 255, 255, 128));
	_questBorder.setSize(sf::Vector2f(1000, 60));

	_currentQuest.setFont(_font);
	_currentQuest.setPosition(sf::Vector2f(60, 90));
	_currentQuest.setFillColor(sf::Color::Red);
	_currentQuest.setString("[Quête en cours]");

	_questName.setFont(_font);
	_questName.setPosition(sf::Vector2f(300, 90));
	_questName.setFillColor(sf::Color::Black);
}

Hud::~Hud() {

}


void Hud::update(float pLife, float pTotalLife, int pMunRest, int pMunTotal)
{
	_infos.setString(std::to_string((int)pLife) + "\n" + std::to_string(pMunRest) + " / " + std::to_string(pMunTotal) + "\n" + "3");
	_lifeBar.setSize(sf::Vector2f((pLife * 225) / pTotalLife, 32));

	if (!_gamePause) {
		if (_timerMsg.getElapsedTime().asSeconds() > 3 && !_messages.empty() && !_messagesAuthors.empty()) {
			_messages.erase(_messages.begin());
			_messagesAuthors.erase(_messagesAuthors.begin());
			_timerMsg.restart();
		}
	}
	else {
		_timerMsg.restart();
	}

	if (_gameInit) {
		if (_initMessages.size() > 0) {
			if (_clockInit.getElapsedTime().asSeconds() > 0) {
				_clockInit.restart();
				_initMessages.erase(_initMessages.begin());
			}
		}
		else
			_gameInit = false;
	}
}

void Hud::addMessage(std::string who, std::string message) {
	if (_canAddMessages) {
		if (_messages.size() <= 0) {
			_timerMsg.restart();
		}
		sf::Text msg;
		msg.setFont(_font);
		msg.setFillColor(sf::Color::Black);
		msg.setPosition(sf::Vector2f(200, 850));

		//Pour que le message ne dépasse pas du cadre on fait des retours à la ligne
		/*if (message.size() > 15) {
			int i = 30;
			while (message[i] != ' ' && i < message.size()) {
				i++;
				std::cout << message[i] << ";";
			}
			message.insert(i, "\n");
		}*/
		msg.setString(message);
		_messages.push_back(msg);

		sf::Text msgAuthor;
		msgAuthor.setFont(_font);
		msgAuthor.setFillColor(sf::Color::Red);
		msgAuthor.setPosition(sf::Vector2f(100, 850));
		msgAuthor.setString(who);
		_messagesAuthors.push_back(msgAuthor);
	}
}

int Hud::getMessagesNumber() const {
	return _messages.size();
}

void Hud::lockMessages(bool cond) {
	_canAddMessages = !cond;	//issou
}

void Hud::setGamePaused(bool pause) {
	_gamePause = pause;
}

bool Hud::isGameInit() const {
	return _gameInit;
}

void Hud::setGameInit(bool init) {
	_gameInit = init;
	_clockInit.restart();
}

void Hud::setCurrentQuest(std::string curQuestName) {
	_questName.setString(curQuestName);
}

void Hud::setQuestActive(bool quest) {
	_questExist = quest;
	if (!quest) {
		_showNoMoreQuest = true;
		_questName.setString("Quêtes terminées !");
	}
	else
		_showNoMoreQuest = false;
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

	if (_messages.size() > 0 && _messagesAuthors.size() > 0) {
		target.draw(_msgBorders);
		target.draw(_messagesAuthors[0]);
		target.draw(_messages[0]);
	}

	if (_gamePause) {
		target.draw(_greyScreenPause);
		target.draw(_textPause);
	}

	if (_gameInit) {
		if (_initMessages.size() > 0) {
			target.draw(_initBg);
			target.draw(_initMessages[0]);
		}
	}

	if (_questExist || _showNoMoreQuest) {
		target.draw(_questBorder);
		if(_questExist)
			target.draw(_currentQuest);
		target.draw(_questName);
	}
}

