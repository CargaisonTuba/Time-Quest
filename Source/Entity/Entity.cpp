#include "Entity.h"
#include <cmath>
#include <ctgmath>


Entity::Entity(std::string texturePath, float defaultLife, sf::Vector2f initPosition, float id) //Constructeur par d�faut, sans param�tre
{
	//A la cr�ation d'un nouveau Personnage, on lui attribue des caract�ristiques:

	//Les 5 prochaines variables sont utilis�es dans l'animation du personnage. Pas important, juste 1 animation
	_spritePosCount = 0;
	_spritePosCountMax = 10;
	_dir = 0;	//0 = down / 1 = right / 2 = up / 3 = left
	_animation_tick = 0;
	_isPushed = false;

	//On charge chaque position de personnage dans un tableau 2D :
	//chaque ligne = personnage qui va vers le haut / le bas / gauche / droite
	//chaque colonne = l'animation de personnage qui cours dans cette direction
	for (int i = 0; i < 10; i++)

	{
		for (int j = 0; j < 4; j++)
		{
			_entityText[i][j].loadFromFile(texturePath, sf::IntRect(i * 16, j * 26, 16, 26));
		}
	}

	//Le sprite du personnage sera plac� initialement dans le coin haut gauche de la map. (0, 0)
	_entitySprite.setPosition(initPosition);
	_entitySprite.setOrigin(8.f, 13.f);
	_initPos = initPosition;


	_life = defaultLife;	//ca repr�sentera la vie ACTUELLE du joueur
	_totalLife = defaultLife;		//ca repr�sente la vie TOTALE du joueur (c'est une sorte de constante, on y touchera plus apr�s)
	_timeSinceShot.restart();

	_curWeapon = new Arme();

	_id = id;
}

Entity::Entity()
{

}

Entity::~Entity() {
	//delete _curWeapon;
	//_curWeapon = nullptr;
}

sf::Vector2f Entity::getPosition() const
{
	return _entitySprite.getPosition();
}

sf::FloatRect Entity::getHitbox() {
	_entitySprite.setTexture(_entityText[0][0]);
	return _entitySprite.getGlobalBounds();
}

int Entity::getID() const {
	return _id;
}

bool Entity::isDead() const {
	return (_life <= 0);
}

/*void Entity::killEntity(std::vector<Object*> &droppedObjects) {
	droppedObjects.push_back(new Arme(_curWeapon));
}*/

void Entity::setWeapon(Arme newWeapon)
{
	std::cout << "\x1B[33m[info]\x1B[0m : changement d'arme\n";
	_curWeapon = new Arme(newWeapon);
}

Arme* Entity::getWeapon()
{
	return this->_curWeapon;
}

void Entity::blast(sf::Vector2f source, float distanceLimit, float damage)
{
	float lengthVectorOfBlastFromSource = sqrt(pow(_entitySprite.getPosition().x - source.x, 2) + pow(_entitySprite.getPosition().y - source.y, 2));

	if (lengthVectorOfBlastFromSource < distanceLimit*30)
	{
		if (_life > damage)
		{
			_life = _life - damage;
		}
		else
		{
			_life = 0;
		}
		sf::Vector2f directionOfPush = sf::Vector2f(_entitySprite.getPosition().x - source.x / lengthVectorOfBlastFromSource,
													_entitySprite.getPosition().y - source.y / lengthVectorOfBlastFromSource);
		pushBack(directionOfPush);
		std::cout << "Pushed\n";
	}
	std::cout << "afterCondition\n" << lengthVectorOfBlastFromSource << "\n";
	
	
}

void Entity::pushBack(sf::Vector2f directionOfPush)
{
	_isPushed = true;
	_pushingForce = directionOfPush;
	_timeSincePushed.restart();
}

float Entity::getLife() const {
	return _life;
}

sf::RectangleShape Entity::getLifebar() const {
	return _lifeBar;
}

float Entity::getTotalLife() const
{
	return _totalLife;
}

bool Entity::fire(std::vector<ThrowedObject>& throwableObjectsList, Entity cible, std::vector<std::vector<Tile>> const& _tiles)
{
	if (_timeSinceShot.getElapsedTime() > sf::milliseconds(_curWeapon->getCoolDown()))
	{
		this->_curWeapon->playTir();
		_timeSinceShot.restart();
		if (_curWeapon->getReady() == true)
		{
			sf::Vector2f pos = this->getPosition();
			sf::Vector2f shootImpr = this->_curWeapon->imprecision(cible.getPosition());
			sf::Vector2f aim(shootImpr.x - pos.x, shootImpr.y - pos.y);
			float lenAim = sqrt(aim.x * aim.x + aim.y * aim.y);
			sf::Vector2f direction(aim.x / lenAim, aim.y / lenAim);

			sf::Vector2f posBalle;
			posBalle.x = pos.x + aim.x - (aim.x * (lenAim - 16)) / lenAim;
			posBalle.y = pos.y + aim.y - (aim.y * (lenAim - 20)) / lenAim;
			this->_curWeapon->update(_entitySprite.getPosition(), shootImpr);
			
			GhostBullet newGhostBullet = GhostBullet(this->_curWeapon->getAngle(), posBalle, direction, this->getHitbox(), cible.getPosition());
			if (newGhostBullet.travel(_tiles))
			{
				Bullet newBullet = Bullet(this->_curWeapon->getAngle(), this->_curWeapon->getBallePath(), posBalle, direction, _curWeapon->getRange(), _curWeapon->getDamages());
				throwableObjectsList.push_back(newBullet);
			}
			
			_curWeapon->getSprite().move(sf::Vector2f(-direction.x * 5, -direction.y * 5));
		}
	}
	
	return true;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Sprite s = _entitySprite;
	s.setTexture(_entityText[_spritePosCount][_dir]);

	target.draw(s);
	target.draw(*_curWeapon);
}
