#pragma once
#include "Map.h"
#include "../HUD/Hud.h"
class Scene
{
public:
	Scene();
	~Scene();
	void update(Player& player, Cursor& curseur, sf::View& view, float const& dt, bool pause);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	Map getMap();
	Hud getHud();

private:
	Map gameplayLayer;
	Hud hud;

};