#pragma once
#include "Scene.h"


class SceneManager
{
private:
	Scene currentScene;
	Player player;
	Cursor cursor;
	sf::RenderWindow window;
	sf::View gameView;
	bool run;
	bool pause;
	bool pauseJustActivated;

public:
	SceneManager();
	SceneManager(bool& run);
	~SceneManager();
	void update(Player& player, Cursor& curseur, sf::View& view, float const& dt, bool pause);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void runGame();

	//Méthodes pour charger les différentes scènes
	void loadLevel1();
	void loadLevel2();
	void loadLevel3();
	void loadMainMenu();
	void loadSavesMenu();
	void loadOptionsMenu();
};