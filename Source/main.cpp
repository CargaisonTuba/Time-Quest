#include <SFML/Graphics.hpp>

#include "Scene/Map.h"
#include "Entity/Player.h"
#include "HUD/Cursor.h"
#include "Scene/SceneManager.h"

#define VERSION "\x1B[34mtimequest-\x1B[33m1.1-beta\x1B[0m"

int main()
{

	//On désactive les erreurs SFML pour que ça ne pollue pas la console
	//(enlever cette ligne s'il y a des erreurs inconnues
	sf::err().rdbuf(NULL);

	std::cout <<  VERSION << std::endl;
	std::cout << "\nHugo, Fergal, Robin - G3S3 - PTUT S2S3\n\n\n";

	//Initialisation du SceneManager
	bool run = true;
	SceneManager sc = SceneManager(run);

	while (run)
	{
		sc.runGame();
	}

	std::cout << "\x1B[31m[fin] : fermeture de " << VERSION << "\x1B[0m "<< std::endl;

	//Tout s'est bien passé, on retourne la valeur 0.
	return 0;
}