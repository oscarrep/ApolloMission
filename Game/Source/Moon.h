#ifndef __MOON_H__
#define __MOON_H__

#include "Module.h"
#include "PhysicsEngine.h"
#include "Point.h"
#include "Animation.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL_render.h"

struct SDL_Texture;
struct SDL_Rect;

class Moon : public Module
{
public:
	Moon();
	~Moon() {};

	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	iPoint GetPos() const;

	void OnCollision(Collider* col1, Collider* col2);
	void LoadAnim();

	Collider* colliderMoon;

	bool firstUpdate = true;
	iPoint spawnPos = { 900, 1000 };
	int radius = 150;
	float gravity = 90;

	float mass;

private:

	iPoint size;
	iPoint offset;

	SDL_Rect rect;

	SDL_Texture* moonTex = nullptr;

	Animation* currentAnim = nullptr;
	Animation moonAnim;

};

#endif // !__MOON_H__