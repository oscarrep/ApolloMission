#include "Defs.h"
#include "Log.h"
#include "Player.h"
#include "Input.h"
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Scene.h"
#include "Animation.h"
#include "Collisions.h"
#include "Window.h"
#include "SString.h"

Player::Player() : Module()
{

}

bool Player::Awake()
{

	return true;
}


bool Player::Start()
{
	characterTex = app->tex->Load("Assets/textures/spaceship.png");
	propulsion = app->tex->Load("Assets/textures/fire.png");

	idleAnim.PushBack({ 0, 0, 52, 106 });

	position.x = spawnPos.x;
	position.y = spawnPos.y;

	shipRect.x = 0;
	shipRect.y = 0;
	shipRect.w = 52;
	shipRect.h = 106;

	//colliderPlayer = app->collisions->AddCollider({0,0,0,0}, COLLIDER_TYPE::COLLIDER_PLAYER, this);

	return true;
}

bool Player::PreUpdate()
{
	currentAnim = &idleAnim;
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) 
	{
		speed.x = -moveSpeed;
	}
	else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP) 
	{
		speed.x = 0;
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		speed.y = moveSpeed;
	}
	else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_UP)
	{
		speed.y = 0;
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) 
	{
		speed.x = moveSpeed;

	}
	else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP) 
	{
		speed.x = 0;
	}

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		speed.y = -moveSpeed;
	}
	else if (app->input->GetKey(SDL_SCANCODE_W) == KEY_UP)
	{
		speed.y = 0;
	}

	if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
	{

	}



	return true;
}

bool Player::Update(float dt)
{

	deltaTime = SDL_GetTicks() - lastTime;
	deltaTime /= 200;
	lastTime = SDL_GetTicks();


	switch (state)
	{
	case IDLE:
		acceleration.y = 0;
		speed.y = 0;
		break;

	case FIRING:

		break;

	case FALLING:

		break;

	case FLYING:

		break;

	case LEFT:

		break;

	case RIGHT:

		break;

	case HIT:

		break;

	case DEAD:

		break;

	}


	speed.y = speed.y + acceleration.y;

	if (speed.y >= 60) {
		speed.y = 60;
	}
	if (speed.y <= -50) {
		speed.y = -50;
	}

	position.x = position.x + speed.x * deltaTime;
	position.y = position.y + speed.y * deltaTime;

	//colliderPlayer->SetPos(position.x + 2, position.y);


	state = FALLING;

	speed.x = 0;

	return true;
}

bool Player::PostUpdate()
{
	app->render->DrawTexture(characterTex, (int)position.x, (int)position.y, &currentAnim->GetCurrentFrame(), 1.0f);

	return true;
}

bool Player::CleanUp()
{
	app->tex->UnLoad(characterTex);
	/*if (colliderPlayer != nullptr)
		colliderPlayer->to_delete = true;*/

	return true;
}

fPoint Player::GetPos() const
{
	return position;
}

fPoint Player::GetSpeed() const
{
	return speed;
}