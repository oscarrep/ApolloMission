#include "PhysicsEngine.h"
#include "Render.h"
#include "Input.h"
//#include "Body.h"
#include "Player.h"
#include <math.h>
#include "Log.h"

PhysicsEngine::PhysicsEngine() : Module()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER][COLLIDER] = false;
	matrix[COLLIDER][COLLIDER_PLAYER] = true;
	matrix[COLLIDER][COLLIDER_ASTEROID] = false;
	matrix[COLLIDER][COLLIDER_PLANET] = false;
	matrix[COLLIDER][COLLIDER_TORPEDO] = false;


	matrix[COLLIDER_TORPEDO][COLLIDER] = false;
	matrix[COLLIDER_TORPEDO][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_TORPEDO][COLLIDER_ASTEROID] = false;
	matrix[COLLIDER_TORPEDO][COLLIDER_PLANET] = false;
	matrix[COLLIDER_TORPEDO][COLLIDER_TORPEDO] = false;


	matrix[COLLIDER_PLAYER][COLLIDER] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ASTEROID] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLANET] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_TORPEDO] = false;


	matrix[COLLIDER_PLANET][COLLIDER] = false;
	matrix[COLLIDER_PLANET][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_PLANET][COLLIDER_ASTEROID] = true;
	matrix[COLLIDER_PLANET][COLLIDER_PLANET] = false;
	matrix[COLLIDER_PLANET][COLLIDER_TORPEDO] = false;

	matrix[COLLIDER_EARTH][COLLIDER] = false;
	matrix[COLLIDER_EARTH][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_EARTH][COLLIDER_ASTEROID] = true;
	matrix[COLLIDER_EARTH][COLLIDER_PLANET] = false;
	matrix[COLLIDER_EARTH][COLLIDER_TORPEDO] = false;

	matrix[COLLIDER_MOON][COLLIDER] = false;
	matrix[COLLIDER_MOON][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_MOON][COLLIDER_ASTEROID] = true;
	matrix[COLLIDER_MOON][COLLIDER_PLANET] = false;
	matrix[COLLIDER_MOON][COLLIDER_TORPEDO] = false;

	matrix[COLLIDER_ASTEROID][COLLIDER] = false;
	matrix[COLLIDER_ASTEROID][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ASTEROID][COLLIDER_ASTEROID] = true;
	matrix[COLLIDER_ASTEROID][COLLIDER_PLANET] = true;
	matrix[COLLIDER_ASTEROID][COLLIDER_TORPEDO] = true;
}

PhysicsEngine::~PhysicsEngine()
{
}

bool PhysicsEngine::Start()
{
	//gravity = fPoint(0, 0.2);
	return true;
}

bool PhysicsEngine::PreUpdate()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{

		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];


		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{

			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	return true;
}

bool PhysicsEngine::Update(float dt)
{
	
	DebugDraw();

	return true;
}

bool PhysicsEngine::CleanUp()
{
	return true;
}

void PhysicsEngine::VerletIntegrator(fPoint position, fPoint speed, fPoint acceleration, float dt)
{
	//position = position - speed * dt + (1 / 2) * acceleration * (dt) ^ 2;
	
	position.x += (speed.x * dt) + (acceleration.x * powf(dt, 2)) / 2;
	position.y += (speed.y * dt) + (acceleration.y * powf(dt, 2)) / 2;
	
	speed.x += acceleration.x * dt;
	speed.y += acceleration.y * dt;

}

fPoint PhysicsEngine::Gravity(float gravity, float mass1, float mass2, float distance, fPoint direction)
{
	fPoint pull;

	float grav = (gravity * (mass1 * mass2) / (distance * distance));
	pull.x = direction.x * grav;
	pull.y = direction.y * grav;

	return pull;
}

Collider* PhysicsEngine::AddCollider(SDL_Rect rect, ColliderType type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			LOG("new collider rect");
			break;
		}
	}

	return ret;
}

Collider* PhysicsEngine::AddColliderCircle(float x, float y, float radius, ColliderType type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(x, y, radius, type, callback);
			LOG("new collider circle");
			break;
		}
	}

	return ret;
}

void PhysicsEngine::DebugDraw()
{
	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER:
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha); //blue
			break;

		case COLLIDER_PLAYER:
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha); //green
			break;

		case COLLIDER_TORPEDO:
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha); //white
			break;

		case COLLIDER_ASTEROID:
			app->render->DrawCircle(colliders[i]->x,
				colliders[i]->y,
				colliders[i]->radius, 255, 255, 0, alpha);	//yellow		
			break;

		/*case COLLIDER_PLANET:
			app->render->DrawCircle(colliders[i]->x,
				colliders[i]->y,
				colliders[i]->radius, 255, 0, 0, alpha); //red
			break;*/

		case COLLIDER_EARTH:
			app->render->DrawCircle(colliders[i]->x,
				colliders[i]->y,
				colliders[i]->radius, 255, 0, 0, alpha); //red
			break;

		case COLLIDER_MOON:
			app->render->DrawCircle(colliders[i]->x,
				colliders[i]->y,
				colliders[i]->radius, 255, 0, 0, alpha); //red
			break;

		}

	}
}

void PhysicsEngine::doCollisions(Collider* col1, Collider* col2)
{
	if (col1->type == ColliderType::COLLIDER || col2->type == ColliderType::COLLIDER || 
		col1->type == ColliderType::COLLIDER_EARTH || col2->type == ColliderType::COLLIDER_EARTH || 
		col1->type == ColliderType::COLLIDER_MOON || col2->type == ColliderType::COLLIDER_MOON)
	{
		//vertical physics
		if (app->player->colliderPlayer->rect.x < col1->rect.x + col1->rect.w && app->player->colliderPlayer->rect.x + app->player->colliderPlayer->rect.w > col1->rect.x ||
			app->player->colliderPlayer->rect.x < col2->rect.x + col2->rect.w && app->player->colliderPlayer->rect.x + app->player->colliderPlayer->rect.w > col2->rect.x)
		{
			if (app->player->colliderPlayer->rect.y + app->player->colliderPlayer->rect.h > col1->rect.y && app->player->colliderPlayer->rect.y < col1->rect.y ||
				app->player->colliderPlayer->rect.y + app->player->colliderPlayer->rect.h > col2->rect.y && app->player->colliderPlayer->rect.y < col2->rect.y)
			{
				app->player->state = IDLE;
				app->player->speed.y = 0;
				if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) app->player->speed.y = -app->player->moveSpeed;
			}

			else if (app->player->colliderPlayer->rect.y < col1->rect.y + col1->rect.h && app->player->colliderPlayer->rect.y + app->player->colliderPlayer->rect.h > col1->rect.y + col1->rect.h ||
				app->player->colliderPlayer->rect.y < col2->rect.y + col2->rect.h && app->player->colliderPlayer->rect.y + app->player->colliderPlayer->rect.h > col2->rect.y + col2->rect.h)
			{
				app->player->state = FALLING;
				app->player->speed.y = 0;
				if (app->player->speed.y == 0)app->player->speed.y = 90;

			}
		}

		//horitzontal physics
		if (app->player->colliderPlayer->rect.y < col1->rect.y + col1->rect.h -5 && app->player->colliderPlayer->rect.y + app->player->colliderPlayer->rect.h > col1->rect.y +5 ||
			app->player->colliderPlayer->rect.y < col2->rect.y + col2->rect.h -5 && app->player->colliderPlayer->rect.y + app->player->colliderPlayer->rect.h > col2->rect.y +5)
		{

			//LEFT
			if (app->player->colliderPlayer->rect.x < col1->rect.x + col1->rect.w && app->player->colliderPlayer->rect.x + app->player->colliderPlayer->rect.w > col1->rect.x + col1->rect.w ||
				app->player->colliderPlayer->rect.x < col2->rect.x + col2->rect.w && app->player->colliderPlayer->rect.x + app->player->colliderPlayer->rect.w > col2->rect.x + col2->rect.w)
			{
				app->player->speed.x = app->player->moveSpeed;
			}

			//RIGHT
			else if (app->player->colliderPlayer->rect.x + app->player->colliderPlayer->rect.w > col1->rect.x && app->player->colliderPlayer->rect.x < col1->rect.x ||
				app->player->colliderPlayer->rect.x + app->player->colliderPlayer->rect.w > col2->rect.x && app->player->colliderPlayer->rect.x < col2->rect.x)
			{
				app->player->speed.x = -app->player->moveSpeed;
			}
		}

	}

	if (col1->type == ColliderType::COLLIDER_ASTEROID || col2->type == ColliderType::COLLIDER_ASTEROID) { app->player->hp - 1; LOG("hp : %i", app->player->hp); }
	if (col1->type == ColliderType::COLLIDER_MOON || col2->type == ColliderType::COLLIDER_MOON) { app->player->moonLanding = true; }
	if (col1->type == ColliderType::COLLIDER_EARTH || col2->type == ColliderType::COLLIDER_EARTH && app->player->moonLanding == true) { app->player->safeReturn = true; LOG("you win"); }
}

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}