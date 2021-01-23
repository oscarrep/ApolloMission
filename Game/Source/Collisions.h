#ifndef __COLLISIONS_H__
#define __COLLISIONS_H__

#define MAX_COLLIDERS 300

#include "Module.h"
#include "SDL/include/SDL_rect.h"

enum ColliderType
{
	COLLIDER_NONE = -1,
	COLLIDER,
	COLLIDER_PLAYER,
	COLLIDER_ASTEROID,
	COLLIDER_TORPEDO,
	COLLIDER_PLANET,
	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	int radius;
	int x;
	int y;
	bool to_delete = false;
	ColliderType type;
	Module* callback = nullptr;
	float damage = 1.0;

	Collider(SDL_Rect rect, ColliderType type, Module* callback = nullptr) :
		rect(rect),
		type(type),
		callback(callback)
	{}

	Collider(int x, int y, int radius, ColliderType type, Module* callback = nullptr) :
		radius(radius),
		x(x),
		y(y),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

/*struct ColliderCircle
{
	int radius;
	fPoint position;
	bool to_delete = false;
	ColliderType type;
	Module* callback = nullptr;
	float damage = 1.0;

	ColliderCircle(int radius, fPoint position, ColliderType type, Module* callback = nullptr) :
		radius(radius),
		position(position),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		position.x = x;
		position.y = y;
	}

	bool CheckCollisionCircle(const SDL_Rect& r) const;
};*/

class Collisions : public Module
{
public:

	Collisions();
	~Collisions();

	bool PreUpdate() override;
	bool Update(float dt) override;
	bool CleanUp() override;

	Collider* AddCollider(SDL_Rect rect, ColliderType type, Module* callback = nullptr);
	Collider* AddColliderCircle(int x, int y, int radius, ColliderType type, Module* callback = nullptr);

	void DebugDraw();
	Collider* colliders[MAX_COLLIDERS];
	bool debug = true;

private:

	bool matrix[COLLIDER_MAX][COLLIDER_MAX];

};

#endif
