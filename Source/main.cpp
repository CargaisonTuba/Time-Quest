#include <SFML/Graphics.hpp>

#include <SFML/Graphics/Texture.hpp>
#include "Scene/Map.h"
#include "Entity/Player.h"
#include "HUD/Cursor.h"
#include "HUD/Hud.h"

#define VERSION "\x1B[34mtimequest-\x1B[33m1.2-pre-alpha\x1B[0m"

int main()
{
	//Nouvelle fenêtre
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Time Quest");
	sf::View gameView(sf::Vector2f(0, 0), sf::Vector2f(400, 267));
	gameView.setSize(sf::Vector2f(400, 267));
	window.setMouseCursorVisible(false);

	//On désactive les erreurs SFML pour que ça ne pollue pas la console
	//(enlever cette ligne s'il y a des erreurs inconnues
	sf::err().rdbuf(NULL);

	std::cout <<  VERSION << std::endl;
	std::cout << "\nHugo, Fergal, Robin - G3S3 - PTUT S2S3\n\n\n";

	//On instancie une nouvelle map, coeur du jeu.
	Map map;
	Player player("Time-Quest/Source/assets/soldatFrancais40.png", 500, map.getPlayerSpawn());
	Cursor curseur("Time-Quest/Source/assets/curseur_tir.png");
	Hud hud(player, window);

	bool pause = false, pauseJustActivated = false;

	//Delta-time
	//Cela nous permet d'avoir un jeu qui n'est pas en fonction des fps
	//Par exemple, pour éviter que le joueur aille à 100 km/h si on a bcp de FPS et qu'il soit ultra lent en cas de lag
	//On va alors, à chaque frame, calculer le temps qu'il s'est écoulé depuis la dernière frame, et le jeu se basera là dessus
	sf::Clock deltaClock;
	sf::Time deltaTime;
	float dt = 0;
	//seed pour l'aléatoire
	srand((unsigned int)time(NULL));

	//Attributs d'instances (Je sais pas quels noms y donner)
	bool run = true;
	bool play = false;
	bool option = false;

	//Menu principal
	sf::Texture playButton;
	sf::Texture optionsButton;
	sf::Texture quitButton;

	sf::Sprite playSprite;
	sf::Sprite optionsSprite;
	sf::Sprite quitSprite;

	if (!playButton.loadFromFile("Time-Quest/Source/assets/playButton.png"))
		std::cout << "couldn't load playButton";
	if (!optionsButton.loadFromFile("Time-Quest/Source/assets/optionsButton.png"))
		std::cout << "couldn't load optionsButton";
	if (!quitButton.loadFromFile("Time-Quest/Source/assets/quitButton.png"))
		std::cout << "couldn't load quitButton";

	playSprite.setTexture(playButton);
	optionsSprite.setTexture(optionsButton);
	quitSprite.setTexture(quitButton);

	//Boucle principale
	while (window.isOpen() && run)
	{
		while (window.isOpen() && run && !play && !option)
		{
			//Menu principal
			//On regarde si on ferme la fenêtre
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					run = false;
				}

			}

			//On efface la frame précédente
			window.clear();

			//le code commence là

			//deltaTime
			deltaTime = deltaClock.restart();

			dt = (float)deltaTime.asMilliseconds();

			//Menu principal
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2f mousePos = curseur.getPosition();
				if (mousePos.x > window.getSize().x / 2 - 150 && mousePos.x < window.getSize().x / 2 + 150)
				{
					if (mousePos.y > window.getSize().y / 4 - 25 && mousePos.y < window.getSize().y / 4 + 25)
					{
						//playButton
						play = true;
					}
					if (mousePos.y > 2 * window.getSize().y / 4 - 25 && mousePos.y < 2 * window.getSize().y / 4 + 25)
					{
						//optionsButton
					}
					if (mousePos.y > 3 * window.getSize().y / 4 - 25 && mousePos.y < 3 * window.getSize().y / 4 + 25)
					{
						//quitButton
						run = false;
						window.close();
					}
				}
			}
			
			playSprite.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 4 - 25);
			optionsSprite.setPosition(window.getSize().x / 2 - 150, 2*window.getSize().y / 4 - 25);
			quitSprite.setPosition(window.getSize().x / 2 - 150, 3*window.getSize().y / 4 - 25);
			window.draw(playSprite);
			window.draw(optionsSprite);
			window.draw(quitSprite);

			curseur.update(window);
			window.draw(curseur);

			//Fin du code. On affiche tout d'un coup, puis on passe à la frame suivante
			window.display();

		}
		while (window.isOpen() && run && !play && option)
		{
			//Option dans le menu principal
			//On regarde si on ferme la fenêtre
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					run = false;
				}

			}

			//On efface la frame précédente
			window.clear();

			//le code commence là

			//deltaTime
			deltaTime = deltaClock.restart();

			dt = (float)deltaTime.asMilliseconds();

			//Menu principal
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

			}

			//Fin du code. On affiche tout d'un coup, puis on passe à la frame suivante
			window.display();

		}
		while (window.isOpen() && run && play && !option)
		{
			//Déroulement du  jeu normal
			//On regarde si on ferme la fenêtre
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					run = false;
				}

			}

			//On efface la frame précédente
			window.clear();

			//le code commence là

			//deltaTime
			deltaTime = deltaClock.restart();

			dt = (float)deltaTime.asMilliseconds();

			//Ancienne Pause
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
				if (!pauseJustActivated) {
					pause = !pause;
					pauseJustActivated = !pauseJustActivated;
					if (pause)
						std::cout << "\x1B[33m[info] : Jeu en pause\n\x1B[0m";
					else
						std::cout << "\x1B[33m[info] : Reprise du jeu\n\x1B[0m";
				}
			}
			else
				pauseJustActivated = false;

			//Nouvelle pause
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				option = true;
			}


			//Ancienne pause partie 2
			if (!pause && window.hasFocus())
			{
				map.update(player, curseur, gameView, dt);
				hud.update(player, window);
			}
				
			curseur.update(window);
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
		while (window.isOpen() && run && play && option)
		{
			//Menu pause
			//On regarde si on ferme la fenêtre
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					run = false;
				}

			}

			//On efface la frame précédente
			window.clear();

			//le code commence là

			//deltaTime
			deltaTime = deltaClock.restart();

			dt = (float)deltaTime.asMilliseconds();

			//Retour au jeu
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				option = false;
			}

			curseur.update(window);
			window.setView(gameView);

			window.draw(map);
			window.draw(player);
			window.setView(window.getDefaultView());
			window.draw(hud);
			window.setView(gameView);
			window.draw(curseur);

			//Il faut Draw le  menu par dessus

			//Fin du code. On affiche tout d'un coup, puis on passe à la frame suivante
			window.display();
		}
		
	}

	std::cout << "\x1B[31m[fin] : fermeture de " << VERSION << "\x1B[0m "<< std::endl;

	//Tout s'est bien passé, on retourne la valeur 0.
	return 0;
}