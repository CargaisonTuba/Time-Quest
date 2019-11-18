#include "Scene.h"


Scene::Scene(Map gameplayLayer, Hud hud)
{
	this->gameplayLayer = gameplayLayer;
	this->hud = hud;
}



Scene::~Scene()
{

}

void Scene::update(Player& player, Cursor& cursor, sf::View& view, float const& dt, bool pause)
{
	gameplayLayer.update(player, cursor, view, dt);
	hud.update(pause);
}
void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	gameplayLayer.draw(target, states);
	hud.draw(target, states);
}
Map Scene::getMap()
{
	return this->gameplayLayer;
}
Hud Scene::getHud()
{
	return this->hud;
}