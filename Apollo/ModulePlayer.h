#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
	PhysBody* spaceship;
	iPoint shipPos;
	uint fire;

	int spaceshipChain[34] = 
	{
	25, 0,
	25, -27,
	7, -54,
	4, -50,
	4, -35,
	0, -39,
	-4, -35,
	-4, -50,
	-7, -54,
	-25, -27,
	-25, 37,
	-18, 42,
	-18, 50,
	17, 50,
	17, 42,
	25, 37,
	25, -9
	};

};