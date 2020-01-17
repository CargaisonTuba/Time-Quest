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

	//getters
	sf::Vector2f getPosition() const;
	sf::RectangleShape getLifebar() const;
	sf::FloatRect getHitbox();
	Arme* getWeapon();
	int getID() const;
	int getMunRest() const;
	int getMunTotal() const;
	float getTotalLife() const;	
	float getAngleCible() const;
	float getLife() const;
	bool isDead() const;


	//setters
	void setWeapon(Arme newWeapon);
	void setPosition(sf::Vector2f newPos);
	void setInitPos(sf::Vector2f pos);
	void setTexture(std::string texturePath);

	
	//méthodes
	bool fire(std::vector<ThrowedObject>& throwableObjectsList, sf::Vector2f const& shootDirection, std::vector<std::vector<Tile>> const& _tiles); //permet à l'entité de tirer
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void pushBack(sf::Vector2f directionOfPush);
	void blast(sf::Vector2f source, float distanceLimit, float damage);

protected:
	sf::Texture _entityText[11][4];
	sf::RectangleShape _ligne;
	sf::Sprite _entitySprite;
	sf::Vector2f _initPos;
	int _spritePosCount, _spritePosCountMax;
	int _dir;	//Haut, bas, ...
	float _animation_tick, _angleCible, _longueurX, _longueurY, _hypo;

	int _id;

	bool _isPushed;
	bool _isPlayer;
	sf::Vector2f _pushingForce;
	sf::Clock _timeSincePushed;

	float _life, _totalLife;


	//Stuff
	Arme *_curWeapon;

	//Barre de vie, assez simple pour le moment.
	sf::RectangleShape _lifeBar;
	float longueurX, longueurY;
	float hypo, angle;
};
