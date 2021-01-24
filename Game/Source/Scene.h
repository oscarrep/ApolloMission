#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Animation.h"
#include "PhysicsEngine.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene();
	virtual ~Scene();

	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void LoadAsteroid();

private:
	SDL_Texture* img;

public:

	SDL_Texture* background;
	SDL_Texture* ship;
	SDL_Texture* earth;
	SDL_Texture* moon;
	SDL_Texture* asteroids;
	SDL_Texture* fire;

	Animation asteroidAnim;
	Animation moonAnim;
	Animation earthAnim;
	Animation fireAnim;

	Collider* moonColl;
	Collider* earthColl;
	Collider* asteroidColl;

	int volume = 5;

	SDL_Rect backgroundrect;
};

#endif // __SCENE_H__