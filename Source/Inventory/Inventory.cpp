#include "Inventory.h"

Inventory::Inventory() {

}

Inventory::~Inventory() {

}

void Inventory::addItem(Object const& object) {
	_items.push_back(object);
}

void Inventory::draw(sf::RenderTarget& target, sf::RenderStates states) const {

}