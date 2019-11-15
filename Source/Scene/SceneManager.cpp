#include "SceneManager.h"
#include "Scene.h"
#include "GamingScene.h"
#include "MenuScene.h"
#include "../Entity/Player.h"

SceneManager::SceneManager()
{
	this->currentScene = GamingScene(Map("Time-Quest/Source/map.txt"), Hud());
	this->player = Player("Time-Quest/Source/assets/soldatFrancais40.png", 500, this->currentScene.getMap().getPlayerSpawn());
	this->cursor = Cursor("Time-Quest/Source/assets/curseur_tir.png");
	//Nouvelle fenêtre
	this->window = sf::RenderWindow(sf::VideoMode(1080, 720), "Time Quest");
	this->gameView = sf::View(sf::Vector2f(0, 0), sf::Vector2f(400, 267));
}

void runGame()
{

}