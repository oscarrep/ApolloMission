#include "Defs.h"
#include "Log.h"
#include "Player.h"
#include "Input.h"
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Scene.h"
#include "Animation.h"
#include "Window.h"
#include "SString.h"

Player::Player() : Module()
{
	fireAnim.PushBack({ 0,	  0,  22, 22 });
	fireAnim.PushBack({ 22,  0,  22, 22 });
	fireAnim.PushBack({ 44,  0,  22, 22 });
	fireAnim.PushBack({ 66,  0,  22, 22 });
	fireAnim.speed = 0.2f;
}

bool Player::Awake()
{

	return true;
}


bool Player::Start()
{
	characterTex = app->tex->Load("Assets/textures/spaceship.png");
	propulsion = app->tex->Load("Assets/textures/fire.png");

	idleAnim.PushBack({ 0, 0, 26, 53 });

	position.x = spawnPos.x;
	position.y = spawnPos.y;

	shipRect.x = 0;
	shipRect.y = 0;
	shipRect.w = 26;
	shipRect.h = 53;

	propellerRect.x = 0;
	propellerRect.y = 0;
	propellerRect.w = 26;
	propellerRect.h = 53;

	colliderPlayer = app->physicsEngine->AddCollider(shipRect, ColliderType::COLLIDER_PLAYER, this);

	return true;
}

bool Player::PreUpdate()
{
	speed.y = gravity;

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
	if (fuel > 0)
	{
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			
			state = FLYING;
		}
	}
	else if (app->input->GetKey(SDL_SCANCODE_W) == KEY_UP)
	{
		speed.y = 0;
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		//launchTorpedo();
		LOG("pew pew uwu");
	}

	if (app->input->GetKey(SDL_SCANCODE_W) != KEY_REPEAT && fuel<1000) fuel+=5;

	LOG("fuel = %d", fuel);

	return true;
}

bool Player::Update(float dt)
{

	deltaTime = SDL_GetTicks() - lastTime;
	deltaTime /= 200;
	lastTime = SDL_GetTicks();


	//app->physicsEngine->updatePlayerStates();

	switch (state)
	{
	case IDLE:
		app->player->acceleration.y = 0;
		break;

	case FIRING:

		break;

	case FALLING:

		break;

	case FLYING:
		speed.y = -moveSpeed;
		fuel--;
		app->render->DrawTexture(propulsion, position.x+2, position.y+50, &(fireAnim.GetCurrentFrame()));
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

	colliderPlayer->SetPos(position.x, position.y);

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
		colliderPlayer->toDelete = true;*/

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

void Player::OnCollision(Collider* col1, Collider* col2) { app->physicsEngine->doCollisions(col1, col2); }