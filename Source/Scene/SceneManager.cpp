#include "SceneManager.h"
#include "Scene.h"
#include "GamingScene.h"
#include "MenuScene.h"
#include "../Entity/Player.h"
#include "../Scene/Map.h"
#include "../HUD/Cursor.h"



SceneManager::SceneManager(bool& run)
{
	Scene currentScene(Map("Time-Quest/Source/map.txt"), Hud());

	Player player("Time-Quest/Source/assets/soldatFrancais40.png", 500, currentScene.getMap().getPlayerSpawn());
	Cursor cursor("Time-Quest/Source/assets/curseur_tir.png");
	//Nouvelle fenêtre
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Time Quest");
	window.setMouseCursorVisible(false);
	this->gameView = sf::View(sf::Vector2f(0, 0), sf::Vector2f(400, 267));
	this->run = run;
	this->pause = false;
	this->pauseJustActivated = false;
}

void SceneManager::runGame()
{
	//seed pour l'aléatoire
	srand(time(NULL));

	//Boucle principale
	while (this->window.isOpen())
	{
		//Delta-time
		//Cela nous permet d'avoir un jeu qui n'est pas en fonction des fps
		//Par exemple, pour éviter que le joueur aille à 100 km/h si on a bcp de FPS et qu'il soit ultra lent en cas de lag
		//On va alors, à chaque frame, calculer le temps qu'il s'est écoulé depuis la dernière frame, et le jeu se basera là dessus
		sf::Clock deltaClock;
		sf::Time deltaTime;
		float dt = 0;
		//On regarde si on ferme la fenêtre
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//On efface la frame précédente
		window.clear();

		//le code commence là

		//deltaTime
		deltaTime = deltaClock.restart();
		dt = deltaTime.asMilliseconds();

		//std::cout << dt << std::endl;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			if (!pauseJustActivated) {
				pause = !pause;
				pauseJustActivated = !pauseJustActivated;
				if (pause)
					std::cout << "\x1B[33m[Info] : Jeu en pause\n\x1B[0m";
				else
					std::cout << "\x1B[33m[Info] : Reprise du jeu\n\x1B[0m";
			}
		}
		else
			pauseJustActivated = false;

		gameView.setSize(sf::Vector2f(400, 267));
		if (!pause)
			currentScene.getMap().update(player, cursor, gameView, dt);

		cursor.update(window);

		window.setView(gameView);

		window.draw(currentScene.getMap());
		window.draw(player);
		window.draw(cursor);

		//Fin du code. On affiche tout d'un coup, puis on passe à la frame suivante
		window.display();
	}
}