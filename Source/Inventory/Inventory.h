#pragma once
#include <SFML/Graphics.hpp>
#include "../Element/Object/Object.h"

class Inventory : public sf::Drawable
{
public:
	Inventory();
	~Inventory();

	void addItem(Object const& object);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::vector<Object> _items;
	std::vector<std::string> _table_ID_to_path;
};
