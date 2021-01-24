#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "PhysicsEngine.h"
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

	void launchTorpedo();
	void addFuel();
	void addMomentum(float xV, float yV, float angle);
	//void addMomentumAngle(float xV, float yV, float angle);

	fPoint GetPos() const;
	fPoint GetSpeed() const;

	void OnCollision(Collider* col1, Collider* col2);
	Collider* colliderPlayer;

	bool firstUpdate = true;
	fPoint spawnPos;
	fPoint position;
	float moveSpeed = 90;
	float gravity = 90;

	fPoint speed;
	fPoint acceleration;
	float angle;
	float mass;
	int hp = 5;
	int fuel = 1500;
	int ammo;

	bool moonLanding = false;
	bool safeReturn = false;

	PlayerState state = FALLING;

private:

	iPoint size;
	iPoint offset;

	SDL_Rect shipRect;
	SDL_Rect propellerRect;

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

};

#endif // !__PLAYER_H__