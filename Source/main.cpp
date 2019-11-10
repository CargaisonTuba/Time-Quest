#include <SFML/Graphics.hpp>

#include "Scene/Map.h"
#include "Entity/Player.h"
#include "HUD/Cursor.h"

#define VERSION "\x1B[33m1.0 beta\x1B[0m"

int main()
{
	//Nouvelle fenêtre
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Time Quest");
	sf::View gameView(sf::Vector2f(0, 0), sf::Vector2f(400, 267));
	window.setMouseCursorVisible(false);

	std::cout << "Time-Quest " << VERSION << std::endl;
	//On instancie une nouvelle map, coeur du jeu.
	Map map;
	Player player("Time-Quest/Source/assets/soldatFrancais40.png", 100, sf::Vector2f(200, 200));
	Cursor curseur("Time-Quest/Source/assets/curseur_tir.png");

	bool pause = false, pauseJustActivated = false;

	//Delta-time
	//Cela nous permet d'avoir un jeu qui n'est pas en fonction des fps
	//Par exemple, pour éviter que le joueur aille à 100 km/h si on a bcp de FPS et qu'il soit ultra lent en cas de lag
	//On va alors, à chaque frame, calculer le temps qu'il s'est écoulé depuis la dernière frame, et le jeu se basera là dessus
	sf::Clock deltaClock;
	sf::Time deltaTime;
	float dt = 0;

	//seed pour l'aléatoire
	srand(time(NULL));

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

		if(!pause)
			map.update(player, curseur, gameView, dt);

		curseur.update(window);

		window.setView(gameView);
		
		window.draw(map);
		window.draw(player);
		window.draw(curseur);

		//Fin du code. On affiche tout d'un coup, puis on passe à la frame suivante
		window.display();
	}

	//Tout s'est bien passé, on retourne la valeur 0.
	return 0;
}