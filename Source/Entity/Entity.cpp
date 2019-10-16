#include "Entity.h"

Entity::Entity(std::string texturePath, int defaultLife, sf::Vector2f initPosition) //Constructeur par défaut, sans paramètre
{
	//A la création d'un nouveau joueur, on lui attribue des caractéristiques:

	//Les 5 prochaines variables sont utilisées dans l'animation du joueur. Pas important, juste 1 animation
	_spritePosCount = 0;
	_spritePosCountMax = 11;
	_dir = 0;	//0 = down / 1 = right / 2 = up / 3 = left
	_animation_tick = 0;

	//On charge chaque position de Link dans un tableau 2D :
	//chaque ligne = link qui va vers le haut / le bas / gauche / droite
	//chaque colonne = l'animation de link qui cours dans cette direction
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_entityText[i][j].loadFromFile(texturePath, sf::IntRect(i * 26, j * 26, 26, 26));
		}
	}

	//Le sprite de link sera placé initialement dans le coin haut gauche de la map. (0, 0)
	_entitySprite.setPosition(initPosition);

	_life = defaultLife;	//ca représentera la vie ACTUELLE du joueur
	_totalLife = defaultLife;		//ca représente la vie TOTALE du joueur (c'est une sorte de constante, on y touchera plus après)
	_timeSinceShot.restart();
}

Entity::~Entity() {

}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Sprite s = _entitySprite;
	s.setTexture(_entityText[_spritePosCount][_dir]);

	target.draw(s);
}
