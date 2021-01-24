#ifndef __EARTH_H__
#define __EARTH_H__

#include "Module.h"
#include "PhysicsEngine.h"
#include "Point.h"
#include "Animation.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL_render.h"
#include "Body.h"

struct SDL_Texture;
struct SDL_Rect;

class Earth : public Module
{
public:
	Earth();
	~Earth() {};

	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	iPoint GetPos() const;

	void OnCollision(Collider* col1, Collider* col2);
	void LoadAnim();

	Collider* colliderEarth;

	bool firstUpdate = true;
	iPoint spawnPos = {950, 5600};
	int radius = 150;
	float gravity = 90;

	float mass;

private:

	iPoint size;
	iPoint offset;

	SDL_Rect rect;

	SDL_Texture* earthTex = nullptr;

	Animation* currentAnim = nullptr;
	Animation earthAnim;

};

#endif // !__EARTH_H__