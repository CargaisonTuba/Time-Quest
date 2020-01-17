#include "Medkit.h"

Medkit::Medkit(sf::Vector2f pos) : Object("Time-Quest/Source/assets/medkit.png", pos)
{
	_type = MEDKIT;
}

Medkit::~Medkit(){

}