#include "GhostBullet.h"

GhostBullet::GhostBullet(float angle, sf::Vector2f throwerPosition, sf::Vector2f direction, sf::Vector2f dest)
{
	_clock = sf::Clock();
	this->_clock.restart();
	_direction = direction;
	_creationDate = (time_t)0;
	_initPos = throwerPosition;
	_dest = dest;
	_ghostSprite.setPosition(_initPos);
}

GhostBullet::~GhostBullet()
{

}

bool GhostBullet::travel(std::vector<std::vector<Tile>> _tiles)
{
	bool a = true;
	std::cout << "Cible X : " << _dest.x << " Y : " << _dest.y << std::endl;
	while (a)
	{
		_ghostSprite.move(sf::Vector2f(_direction.x, _direction.y));
		std::cout << "Position X : " << _ghostSprite.getPosition().x << " Y : " << _ghostSprite.getPosition().y << std::endl;
		for (int i = fmin(floor(_initPos.x/30)+1, floor(_dest.x/30)+1); i < fmax(floor(_initPos.x/30)+1,floor(_dest.x/30)+1); i++)
		{
			for (int j = fmin(floor(_initPos.y / 30) + 1, floor(_dest.y / 30) + 1); j < fmax(floor(_initPos.y / 30) + 1, floor(_dest.y / 30) + 1); j++)
			{
				if (_ghostSprite.getGlobalBounds().intersects(_tiles[i][j].getHitbox()) && _tiles[i][j].isWall())
				{
					std::cout << "obstacleu" << std::endl;
					return false;
				}
				std::cout << "Tile[" << i << "][" << j << "]"<< std::endl;
			}
			std::cout << "toast" << std::endl;
		}
		if (_ghostSprite.getPosition() == _dest)
		{
			return true;
		}
	}
	return a;
}