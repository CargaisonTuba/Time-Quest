/*
Le bug des balles qui se surperposent pour faire des traits ressemble � un nuage magique et genre ils volent dessus
*/


#include <SFML/Graphics.hpp>

#include "Scene/Map.h"
#include "Entity/Player.h"
#include "HUD/Cursor.h"

int main()
{
	//Nouvelle fenêtre
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Time Quest");
	sf::View gameView(sf::Vector2f(0, 0), sf::Vector2f(360, 280));
	window.setMouseCursorVisible(false);

	//On instancie une nouvelle map, coeur du jeu.
	Map map;
	Player player("Time-Quest/Source/assets/soldatFrancais40.png", 100, sf::Vector2f(30, 30));
	Cursor curseur("Time-Quest/Source/assets/curseur_tir.png");

	bool pause = false;

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			pause = !pause;

		if(!pause)
			map.update(player, curseur, gameView, window);

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