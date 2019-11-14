#include "Entity.h"


Entity::Entity(std::string texturePath, float defaultLife, sf::Vector2f initPosition) //Constructeur par d�faut, sans param�tre
{
	//A la cr�ation d'un nouveau joueur, on lui attribue des caract�ristiques:

	//Les 5 prochaines variables sont utilis�es dans l'animation du joueur. Pas important, juste 1 animation
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

	//Le sprite de link sera plac� initialement dans le coin haut gauche de la map. (0, 0)
	_entitySprite.setPosition(initPosition);
	_entitySprite.setOrigin(13.f, 13.f);
	_initPos = initPosition;


	_life = defaultLife;	//ca repr�sentera la vie ACTUELLE du joueur
	_totalLife = defaultLife;		//ca repr�sente la vie TOTALE du joueur (c'est une sorte de constante, on y touchera plus apr�s)
	_timeSinceShot.restart();
}

Entity::~Entity() {

}

sf::Vector2f Entity::getPosition() const
{
	return _entitySprite.getPosition();
}

sf::FloatRect Entity::getHitbox() {
	_entitySprite.setTexture(_entityText[0][0]);
	return _entitySprite.getGlobalBounds();
}

void Entity::setWeapon(Arme newWeapon)
{
	std::cout << "\x1B[33m[info]\x1B[0m : changement d'arme\n";
	_curWeapon = newWeapon;
}

Arme Entity::getWeapon()
{
	return this->_curWeapon;
}

float Entity::getLife() const {
	return _life;
}

sf::RectangleShape Entity::getLifebar() const {
	return _lifeBar;
}

bool Entity::fire(std::vector<ThrowedObject>& throwableObjectsList, sf::Vector2f const& shootDirection, std::vector<Tile> const& _tiles)
{
	if (_timeSinceShot.getElapsedTime() > sf::milliseconds(_curWeapon.getCoolDown()) && _curWeapon.getReady()==true)
	{
		this->getWeapon().playTir();
		_timeSinceShot.restart();
		sf::Vector2f pos = this->getPosition();

		sf::Vector2f aim(shootDirection.x - pos.x, shootDirection.y - pos.y);
		float lenAim = sqrt(aim.x * aim.x + aim.y * aim.y);
		sf::Vector2f direction(aim.x / lenAim, aim.y / lenAim);

		sf::Vector2f posBalle;
		posBalle.x = pos.x + aim.x - (aim.x * (lenAim - 25)) / lenAim;
		posBalle.y = pos.y + aim.y - (aim.y * (lenAim - 25)) / lenAim;
		
		Bullet newBullet = Bullet(posBalle, direction, _curWeapon.getRange(), _curWeapon.getDamages());
		_entitySprite.move(sf::Vector2f(-direction.x/2, -direction.y/2));
		for (unsigned int i = 0; i < _tiles.size(); i++) {
			if (getHitbox().intersects(_tiles[i].getHitbox()) && _tiles[i].isWall()) {
				_entitySprite.move(sf::Vector2f(direction.x/2, direction.y/2));
			}
		}

		throwableObjectsList.push_back(newBullet);

	}

	return true;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Sprite s = _entitySprite;
	s.setTexture(_entityText[_spritePosCount][_dir]);

	target.draw(s);
	target.draw(_curWeapon);
}
