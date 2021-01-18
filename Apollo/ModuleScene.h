#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Animation.h"

class PhysBody;

class ModuleScene : public Module
{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	void LoadEarth();
	void LoadMoon();

	void LoadAsteroid();

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	PhysBody* spaceship;
	p2List<PhysBody*> triangles;

	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	SDL_Texture* background;
	SDL_Texture* ship;
	SDL_Texture* earth;
	SDL_Texture* moon;
	SDL_Texture* asteroids;
	SDL_Texture* satellite;
	SDL_Texture* fire;

	Animation asteroidAnim;
	Animation moonAnim;
	Animation earthAnim;
	Animation fireAnim;

	uint bonus_fx;

	SDL_Rect backgroundrect;

	int spaceshipChain[34] = {
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
