#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "Collisions.h"
#include "Point.h"
#include "Animation.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL_render.h"

struct SDL_Texture;
struct SDL_Rect;

enum PlayerState
{
	IDLE,
	FIRING,
	FLYING,
	LEFT,
	RIGHT,
	FALLING,
	HIT,
	DEAD,
	GOD_MODE,
	MAX_STATES
};


class Player : public Module
{
public:
	Player();
	~Player() {};

	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	//bool GameWin();

	fPoint GetPos() const;
	fPoint GetSpeed() const;

	void OnCollision(Collider* c1, Collider* c2);
	Collider* colliderPlayer;

	bool firstUpdate = true;
	fPoint spawnPos = { 1050, -4500 };
	fPoint position;
	float moveSpeed = 90;
	float gravity = 90;


private:
	float contpeed = -25;

	iPoint size;
	iPoint offset;
	fPoint speed;
	fPoint acceleration;

	SDL_Rect shipRect;

	SDL_Texture* characterTex = nullptr;
	SDL_Texture* fire = nullptr;
	SDL_Texture* propulsion = nullptr;
	SDL_Texture* explosion = nullptr;

	Animation* currentAnim = nullptr;
	Animation idleAnim;
	Animation fireAnim;
	Animation flyAnim;
	Animation deathAnim;

	float deltaTime = 0;
	Uint32 lastTime = 0;
	Uint32 currTime = 0;

	PlayerState state = FALLING;

};

#endif // !__PLAYER_H__