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
	update_status Update(float dt);
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	void LoadEarth();
	void LoadMoon();

	void LoadAsteroid();

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> spaceship;
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
	SDL_Rect shipRect;
};
