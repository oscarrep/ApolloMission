#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "App.h"
#include "Point.h"
#include "Textures.h"
#include "Audio.h"
#include "Animation.h"
#include "SDL_image/include/SDL_image.h"

#include "List.h"

enum class COLLIDER_DIRECTION;

enum class EntityState 
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
	UNKNOWN,
	MAX_STATES
};

enum class EntityType
{
	NO_ENTITY,
	PLAYER,
	ASTEROID,
	MOON,
	EARTH,
	BULLET,
};

class Entity
{
public:

	Entity(const fPoint& position, const char* name, EntityType type);
	~Entity();

	virtual bool Start() = 0;
	virtual void PreUpdate(float dt) = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw();
	virtual void CleanUp() = 0;

	virtual void OnCollision(Collider* c1, Collider* c2) = 0;
	virtual bool Load(pugi::xml_node&) { return true; };
	virtual bool Save(pugi::xml_node&) const { return true; };

	virtual void AwakeEntity(pugi::xml_node&);


public:
	SString name;

	fPoint position;
	fPoint spawnPos;
	fPoint checkpointPos;
	fPoint speed;
	iPoint size;
	iPoint offset;
	fPoint acceleration;

	float gravity;
	bool checkpoint = false;
	int checkpointFx;
	int hp;
	int pickupCount;
	int ammo;

	EntityType type = EntityType::NO_ENTITY;
	EntityState states = EntityState::UNKNOWN;
	float animSpeed;
	Animation* currentAnim = nullptr;
	bool toDelete = false;
	bool debugUI = false;

	SDL_Texture* characterTex = nullptr;
	SDL_Texture* fire = nullptr;
	SDL_Texture* propulsion = nullptr;
	SDL_Texture* explosion = nullptr;

	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	SDL_Texture* background;
	SDL_Texture* ship;
	SDL_Texture* earth;
	SDL_Texture* moon;
	SDL_Texture* asteroids;

	Animation idleAnim;
	Animation fireAnim;
	Animation flyAnim;
	Animation deathAnim;

	Animation asteroidAnim;
	Animation moonAnim;
	Animation earthAnim;

	Collider* collider = nullptr;
	Collider* colliderPlayer;
	Collider* moonColl;
	Collider* earthColl;
	Collider* asteroidColl;

	pugi::xml_node entNode;
};

#endif
