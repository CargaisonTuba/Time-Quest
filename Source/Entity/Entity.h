#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <SFML/Audio.hpp>

#include "../Element/Tile.h"
#include "../Arme.h"
#include "../HUD/Cursor.h"
#include "../Element/Object/ThrowedObject.h"
#include "../Element/Object/ThrowedObject/Bullet.h"
#include "../Element/Object/Medkit.h"

class Entity : public sf::Drawable
{
public:
	Entity(std::string texturePath, float defaultLife, sf::Vector2f initPosition, float id);
	~Entity();

	sf::Vector2f getPosition() const;
	sf::FloatRect getHitbox();
	int getID() const;

	bool isDead() const;

	void setWeapon(Arme newWeapon);

	Arme* getWeapon();
	void blast(sf::Vector2f source, float distanceLimit, float damage);
	void pushBack(sf::Vector2f directionOfPush);

	float getLife() const;
	sf::RectangleShape getLifebar() const;

	bool fire(std::vector<ThrowedObject>& throwableObjectsList, sf::Vector2f const& shootDirection, std::vector<Tile> const& _tiles);
	float getTotalLife() const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;



protected:
	sf::Texture _entityText[11][4];
	sf::Sprite _entitySprite;
	sf::Vector2f _initPos;
	int _spritePosCount, _spritePosCountMax;
	int _dir;	//Haut, bas, ...
	float _animation_tick;

	int _id;

	bool _isPushed;
	sf::Vector2f _pushingForce;
	sf::Clock _timeSincePushed;

	float _life, _totalLife;
	sf::Clock _timeSinceShot;

	//Stuff
	Arme *_curWeapon;

	//Barre de vie, assez simple pour le moment.
	sf::RectangleShape _lifeBar;
	float longueurX, longueurY;
	float hypo, angle;
};
