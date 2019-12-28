#include <SFML/Graphics.hpp>

#include "Scene/Map.h"
#include "Entity/Player.h"
#include "HUD/Cursor.h"
#include "HUD/Hud.h"

#define VERSION "\x1B[34mtimequest-\x1B[33m2.0-pre-alpha\x1B[0m"

int main()
{
	//Nouvelle fenêtre
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Time Quest");
	sf::View gameView(sf::Vector2f(0, 0), sf::Vector2f(400, 267));
	window.setMouseCursorVisible(false);

	//On désactive les erreurs SFML pour que ça ne pollue pas la console
	//(enlever cette ligne s'il y a des erreurs inconnues
	sf::err().rdbuf(NULL);

	std::cout <<  VERSION << std::endl;
	std::cout << "\nHugo, Fergal, Robin - G3S3 - PTUT S2S3, S4 on espere\n\n\n";

	//On instancie une nouvelle map, coeur du jeu.
	Map map;
	Player player("Time-Quest/Source/assets/soldatFrancais40.png", 500, map.getPlayerSpawn());
	Cursor curseur("Time-Quest/Source/assets/curseur_tir.png");
	Hud hud(window);

	bool pause = false, pauseJustActivated = false, mapChanged = false;

	//Delta-time
	//Cela nous permet d'avoir un jeu qui n'est pas en fonction des fps
	//Par exemple, pour éviter que le joueur aille à 100 km/h si on a bcp de FPS et qu'il soit ultra lent en cas de lag
	//On va alors, à chaque frame, calculer le temps qu'il s'est écoulé depuis la dernière frame, et le jeu se basera là dessus
	sf::Clock deltaClock;
	sf::Time deltaTime;
	float dt = 0;
	//seed pour l'aléatoire
	srand((unsigned int)time(NULL));

	//Boucle principale
	while (window.isOpen())
	{
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

		dt = (float)deltaTime.asMilliseconds();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			if (!pauseJustActivated) {
				pause = !pause;
				pauseJustActivated = !pauseJustActivated;
				hud.setGamePaused(pause);
			}
		}
		else
			pauseJustActivated = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
			if (!mapChanged) {
				mapChanged = true;
				map = Map();
			}
		}
		else
			mapChanged = false;

		gameView.setSize(sf::Vector2f(400, 267));
		if(!pause && window.hasFocus())
			map.update(player, curseur, gameView, hud, dt);

		curseur.update(window);
		hud.update(player.getLife(), player.getTotalLife(), player.getMunRest(), player.getMunTotal());

		window.setView(gameView);
		
		window.draw(map);
		window.draw(player);
		window.setView(window.getDefaultView());
		window.draw(hud);
		window.setView(gameView);
		window.draw(curseur);

		//Fin du code. On affiche tout d'un coup, puis on passe à la frame suivante
		window.display();
	}

	std::cout << "\x1B[31m[fin] : fermeture de " << VERSION << "\x1B[0m "<< std::endl;

	//Tout s'est bien passé, on retourne la valeur 0.
	return 0;
}