#pragma once
#include <SFML/Graphics.hpp>
#include "CollectedItem.h"

class Inventory : public sf::Drawable
{
public:
	Inventory();
	~Inventory();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::vector<ColletedItem> _items;
};
