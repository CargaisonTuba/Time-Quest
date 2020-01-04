#include "GhostBullet.h"

GhostBullet::GhostBullet(float angle, sf::Vector2f throwerPosition, sf::Vector2f direction, sf::FloatRect cible, sf::Vector2f ciblePos)
{
	_clock = sf::Clock();
	this->_clock.restart();
	_direction = direction;
	_creationDate = (time_t)0;
	_initPos = throwerPosition;
	_cibleHitbox = cible;
	_ciblePos = ciblePos;
	_ghostText.loadFromFile("Time-Quest/Source/assets/ballemas36.png");
	_ghostSprite.setTexture(_ghostText);
	_ghostSprite.setPosition(_initPos);
}

GhostBullet::GhostBullet()
{

}

GhostBullet::~GhostBullet()
{

}

bool GhostBullet::travel(std::vector<std::vector<Tile>> _tiles)
{
	bool a = true;
	//std::cout << "Cible X : " << _cible.getPosition().x << " Y : " << _cible.getPosition().y << std::endl;
	while (a)
	{
		_ghostSprite.move(sf::Vector2f(_direction.x, _direction.y));
		std::cout << "Position X : " << _ghostSprite.getPosition().x << " Y : " << _ghostSprite.getPosition().y << std::endl;
		for (int i = fmin(floor(_initPos.x/30)+1, floor(_ciblePos.x/30)+1); i < fmax(floor(_initPos.x/30)+1,floor(_ciblePos.x/30)+1); i++)
		{
			for (int j = fmin(floor(_initPos.y / 30) + 1, floor(_ciblePos.y / 30) + 1); j < fmax(floor(_initPos.y / 30) + 1, floor(_ciblePos.y / 30) + 1); j++)
			{
				std::cout << "Tile[" << i << "][" << j << "]" << std::endl;
				if (_ghostSprite.getGlobalBounds().intersects(_tiles[i][j].getHitbox()) && _tiles[i][j].isWall())
				{
					std::cout << "obstacleu" << std::endl;
					return false;
				}
				
			}
			std::cout << "toast" << std::endl;
		}
		if (_ghostSprite.getGlobalBounds().intersects(_cibleHitbox))
		{
			return true;
		}
	}
	return a;
}