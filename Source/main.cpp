#include <SFML/Graphics.hpp>

#include "Scene/Map.h"
#include "Entity/Player.h"
#include "HUD/Cursor.h"
#include "HUD/Hud.h"

#define VERSION "\x1B[34mtimequest-\x1B[33m1.0\x1B[0m"

int main()
{
	//Nouvelle fenêtre
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Time Quest", sf::Style::Fullscreen);
	//sf::RenderWindow window(sf::VideoMode(500, 500), "Time Quest");
	sf::View gameView(sf::Vector2f(0, 0), sf::Vector2f(960, 540));
	window.setMouseCursorVisible(false);

	//On désactive les erreurs SFML pour que ça ne pollue pas la console   
	//(enlever cette ligne s'il y a des erreurs inconnues
	sf::err().rdbuf(NULL);

	std::cout <<  VERSION << std::endl;
	std::cout << "\nHugo, Fergal, Robin - G3S3 - PTUT S2S3, S4 on espere\n\n\n";

	//On instancie une nouvelle map, coeur du jeu.
	Map map;
	map.load("map_transition.txt");

	Player player("soldatFrancais40.png", 500, map.getPlayerSpawn());
	Cursor curseur("Time-Quest/Source/assets/curseur_tir.png");
	Hud hud(window);
	hud.setGameInit(true);

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

	//Attributs d'instances (Je sais pas quels noms y donner)
	bool run = true;
	bool play = false;
	bool option = false;

	//Menu principal
	sf::Clock timer;
	float lastClickInMenu = 0;

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

	//Menu option
	sf::Texture backButton;

	sf::Sprite backSprite;

	if (!backButton.loadFromFile("Time-Quest/Source/assets/backButton.png"))
		std::cout << "couldn't load backButton";

	backSprite.setTexture(backButton);

	//Menu pause
	sf::Texture continueButton;
	sf::Texture backtomenuButton;

	sf::Sprite continueSprite;
	sf::Sprite backtomenuSprite;

	if (!continueButton.loadFromFile("Time-Quest/Source/assets/continueButton.png"))
		std::cout << "couldn't load continueButton";

	if (!backtomenuButton.loadFromFile("Time-Quest/Source/assets/backtomenuButton.png"))
		std::cout << "couldn't load backtomenuButton";

	continueSprite.setTexture(continueButton);
	backtomenuSprite.setTexture(backtomenuButton);

	//Boucle principale
	

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
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timer.getElapsedTime().asMilliseconds() - lastClickInMenu > 1000)
			{
				sf::Vector2f mousePos = curseur.getPosition();
				if (mousePos.x > window.getSize().x / 2 - 150 && mousePos.x < window.getSize().x / 2 + 150)
				{
					if (mousePos.y > window.getSize().y / 4 - 25 && mousePos.y < window.getSize().y / 4 + 25)
					{
						//playButton
						play = true;
						lastClickInMenu = timer.getElapsedTime().asMilliseconds();
					}
					if (mousePos.y > 2 * window.getSize().y / 4 - 25 && mousePos.y < 2 * window.getSize().y / 4 + 25)
					{
						//optionsButton
						option = true;
						lastClickInMenu = timer.getElapsedTime().asMilliseconds();
					}
					if (mousePos.y > 3 * window.getSize().y / 4 - 25 && mousePos.y < 3 * window.getSize().y / 4 + 25)
					{
						//quitButton
						run = false;
						window.close();
						lastClickInMenu = timer.getElapsedTime().asMilliseconds();
					}
				}
			}

			playSprite.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 4 - 25);
			optionsSprite.setPosition(window.getSize().x / 2 - 150, 2 * window.getSize().y / 4 - 25);
			quitSprite.setPosition(window.getSize().x / 2 - 150, 3 * window.getSize().y / 4 - 25);
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


			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timer.getElapsedTime().asMilliseconds() - lastClickInMenu > 1000)
			{
				sf::Vector2f mousePos = curseur.getPosition();
				if (mousePos.x > window.getSize().x / 2 - 150 && mousePos.x < window.getSize().x / 2 + 150)
				{

					if (mousePos.y > 3 * window.getSize().y / 4 - 25 && mousePos.y < 3 * window.getSize().y / 4 + 25)
					{
						//backButton
						option = false;
						lastClickInMenu = timer.getElapsedTime().asMilliseconds();

					}
				}
			}


			backSprite.setPosition(window.getSize().x / 2 - 150, 3 * window.getSize().y / 4 - 25);

			window.draw(backSprite);

			curseur.update(window);
			window.draw(curseur);

			//Fin du code. On affiche tout d'un coup, puis on passe à la frame suivante
			window.display();

		}
		while (window.isOpen() && run && play && !option)
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

			gameView.setSize(sf::Vector2f(768, 432));
			if (!pause && window.hasFocus() && !hud.isGameInit())
				map.update(player, curseur, gameView, hud, dt);

			curseur.update(window);
			hud.update(player.getLife(), player.getTotalLife(), player.getMunRest(), player.getMunTotal());

			window.setView(gameView);

			if (!hud.isGameInit()) {
				window.draw(map);
				window.draw(player);
			}

			window.setView(window.getDefaultView());
			window.draw(hud);
			window.setView(gameView);
			if (!hud.isGameInit())
				window.draw(curseur);

			//Fin du code. On affiche tout d'un coup, puis on passe à la frame suivante
			window.display();
		}

	}

	std::cout << "\x1B[31m[fin] : fermeture de " << VERSION << "\x1B[0m "<< std::endl;

	//Tout s'est bien passé (on espère), on retourne la valeur 0.
	return 0;
}