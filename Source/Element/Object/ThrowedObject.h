#pragma once

#include <SFML/Graphics.hpp>

#include "Object.h"

class ThrowedObject : public Object
{
public:
	ThrowedObject();
	~ThrowedObject();

	bool update();
};

