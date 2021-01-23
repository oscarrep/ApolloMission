#include "App.h"
#include "Input.h"
#include "Render.h"
#include "Collisions.h"
#include "Player.h"

#include "Log.h"

Collisions::Collisions()
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


	matrix[COLLIDER_ASTEROID][COLLIDER] = false;
	matrix[COLLIDER_ASTEROID][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ASTEROID][COLLIDER_ASTEROID] = true;
	matrix[COLLIDER_ASTEROID][COLLIDER_PLANET] = true;
	matrix[COLLIDER_ASTEROID][COLLIDER_TORPEDO] = true;

}


Collisions::~Collisions()
{}

bool Collisions::PreUpdate()
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


bool Collisions::Update(float dt)
{

	// To be implemented debug capabilities for painting colliders and godmode
	DebugDraw();
	//GodMode();

	return true;

}

void Collisions::DebugDraw()
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

		case COLLIDER_PLANET:
			app->render->DrawCircle(colliders[i]->x,
				colliders[i]->y, 
				colliders[i]->radius, 255, 0, 0, alpha); //red
			break;
		}
	}
}

bool Collisions::CleanUp()
{
	//LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
	*colliders = nullptr;

	return true;

}

Collider* Collisions::AddCollider(SDL_Rect rect, ColliderType type, Module* callback)
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

Collider* Collisions::AddColliderCircle(int x, int y, int radius, ColliderType type, Module* callback)
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

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}