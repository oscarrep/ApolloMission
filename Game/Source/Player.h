#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Collisions.h"
#include "Entity.h"
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


class Player : public Entity
{
public:
	Player(const fPoint& position);
	~Player() {};

	void Awake();
	bool Start() override;
	void PreUpdate(float dt) override;
	void Update(float dt);
	void PostUpdate(float dt);
	void CleanUp();

	//bool GameWin();

	fPoint GetPos() const;
	fPoint GetSpeed() const;

	void OnCollision(Collider* c1, Collider* c2);

	bool firstUpdate = true;
	fPoint spawnPos = { 100, 100 };
	fPoint position;
	float moveSpeed = 90;
	SDL_Rect shipRect;


private:
	float contpeed = -25;

	//SDL_Rect shipRect;

	float deltaTime = 0;
	Uint32 lastTime = 0;
	Uint32 currTime = 0;

	PlayerState state = FALLING;

};

#endif // !__PLAYER_H__