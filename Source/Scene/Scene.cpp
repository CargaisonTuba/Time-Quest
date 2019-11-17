#include "Scene.h"

Scene::Scene(Map& gameplayLayer, Hud& hud)
{
	this->gameplayLayer = gameplayLayer;
	this->hud = hud;
}

void Scene::update(Player& player, Cursor& curseur, sf::View& view, float const& dt, bool pause)
{

}
void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}
Map Scene::getMap()
{
	return this->gameplayLayer;
}
Hud getHud();