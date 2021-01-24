#ifndef __PHYSICS_ENGINE_H__
#define __PHYSICS_ENGINE_H__

#include "App.h"
#include "Module.h"
#include "Point.h"
//#include "Body.h"
#include "SDL/include/SDL_rect.h"

#define MAX_COLLIDERS 300

struct SDL_Rect;

enum ColliderType
{
	COLLIDER_NONE = -1,
	COLLIDER,
	COLLIDER_PLAYER,
	COLLIDER_ASTEROID,
	COLLIDER_TORPEDO,
	COLLIDER_PLANET,
	COLLIDER_EARTH,
	COLLIDER_MOON,
	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	float radius;
	float x;
	float y;
	bool to_delete = false;
	ColliderType type;
	Module* callback = nullptr;
	float damage = 1.0;

	Collider(SDL_Rect rect, ColliderType type, Module* callback = nullptr) :
		rect(rect),
		type(type),
		callback(callback)
	{}

	Collider(float x, float y, float radius, ColliderType type, Module* callback = nullptr) :
		radius(radius),
		x(x),
		y(y),
		type(type),
		callback(callback)
	{}

	void SetPos(float x, float y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class PhysicsEngine : public Module
{
public:

	PhysicsEngine();
	virtual ~PhysicsEngine();

    bool Start();
	bool PreUpdate();
    bool Update(float dt);
    bool CleanUp();
	void physicsUpdate(Collider collider, float dt);
	void DebugDraw();

	Collider* AddCollider(SDL_Rect rect, ColliderType type, Module* callback = nullptr);
	Collider* AddColliderCircle(float x, float y, float radius, ColliderType type, Module* callback = nullptr);

	//void AddBody(Collider collider);
	//void DeleteBody(Collider collider);

	//void updatePlayerStates();

	fPoint Gravity(float gravity, float mass1, float mass2, float distance, fPoint direction);
	fPoint forceAeroDrag(float density, float relativeVelocity, float surface, float dragCoefficient);
	fPoint forceAeroLift();
	//fPoint forceHydroBuoy();
	//fPoint forceHydroDrag();
	void VerletIntegrator(fPoint position, fPoint speed, fPoint acceleration, float dt);
	void doCollisions(Collider* col1, Collider* col2);


public:
    //Planet* CreatePlanet(fPoint position, float mass, float rad);


    float gravity = 0.f;

    float earthPos = 0.f;
    float earthGrav = 9.8f;
    float earthGravRadius = 0.f;

    float moonPos = 0.f;
    float moonGrav = 1.6f;
    float moonGravRadius = 0.f;

	Collider* colliders[MAX_COLLIDERS];

    //Rocket* rocket;
    fPoint position;

	bool debug = false;

private:

	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	

    List<Collider*> ColliderList;
};

#endif // !__PHYSICSENGINE_H__
