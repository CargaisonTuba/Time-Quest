#include "Entity.h"


Entity::Entity(std::string texturePath, float defaultLife, sf::Vector2f initPosition) //Constructeur par défaut, sans paramètre
{
	//A la création d'un nouveau joueur, on lui attribue des caractéristiques:

	//Les 5 prochaines variables sont utilisées dans l'animation du joueur. Pas important, juste 1 animation
	_spritePosCount = 0;
	_spritePosCountMax = 10;
	_dir = 0;	//0 = down / 1 = right / 2 = up / 3 = left
	_animation_tick = 0;

	//On charge chaque position de Link dans un tableau 2D :
	//chaque ligne = link qui va vers le haut / le bas / gauche / droite
	//chaque colonne = l'animation de link qui cours dans cette direction
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_entityText[i][j].loadFromFile(texturePath, sf::IntRect(i * 16, j * 26, 16, 26));
		}
	}

	//Le sprite de link sera placé initialement dans le coin haut gauche de la map. (0, 0)
	_entitySprite.setPosition(initPosition);
	_entitySprite.setOrigin(8.f, 13.f);
	_initPos = initPosition;


	_life = defaultLife;	//ca représentera la vie ACTUELLE du joueur
	_totalLife = defaultLife;		//ca représente la vie TOTALE du joueur (c'est une sorte de constante, on y touchera plus après)
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

float Entity::getTotalLife() const
{
	return _totalLife;
}

sf::RectangleShape Entity::getLifebar() const {
	return _lifeBar;
}

bool Entity::fire(std::vector<ThrowedObject>& throwableObjectsList, sf::Vector2f const& shootDirection, std::vector<Tile> const& _tiles)
{
	if (_timeSinceShot.getElapsedTime() > sf::milliseconds(_curWeapon.getCoolDown()))
	{
		this->_curWeapon.playTir();
		_timeSinceShot.restart();
		if (_curWeapon.getReady() == true)
		{
			sf::Vector2f pos = this->getPosition();
			sf::Vector2f shootImpr = this->_curWeapon.imprecision(shootDirection);
			sf::Vector2f aim(shootImpr.x - pos.x, shootImpr.y - pos.y);
			float lenAim = sqrt(aim.x * aim.x + aim.y * aim.y);
			sf::Vector2f direction(aim.x / lenAim, aim.y / lenAim);

			sf::Vector2f posBalle;
			posBalle.x = pos.x + aim.x - (aim.x * (lenAim - 16)) / lenAim;
			posBalle.y = pos.y + aim.y - (aim.y * (lenAim - 20)) / lenAim;
			this->_curWeapon.update(_entitySprite.getPosition(), shootImpr);
			Bullet newBullet = Bullet(this->_curWeapon.getAngle(), this->_curWeapon.getBallePath(), posBalle, direction, _curWeapon.getRange(), _curWeapon.getDamages());
			throwableObjectsList.push_back(newBullet);
			_curWeapon.getSprite().move(sf::Vector2f(-direction.x * 5, -direction.y * 5));
		}
	}
	
	return true;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Sprite s = _entitySprite;
	s.setTexture(_entityText[_spritePosCount][_dir]);

	target.draw(s);
	target.draw(_curWeapon);
}
