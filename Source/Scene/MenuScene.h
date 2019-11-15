#pragma once
#include "Map.h"
#include "Scene.h"
#include "../HUD/Hud.h"

class MenuScene : public Scene
{
private:
	
public:
	MenuScene(Map background, Hud menu);
	~MenuScene();
	
};