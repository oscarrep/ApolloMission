#include "Globals.h"
#include "Application.h"
#include "Player.h"
#include "Physics.h"
#include "Input.h"
#include "Textures.h"
#include "Render.h"
#include "Scene.h"
#include "Audio.h"


Player::Player(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

Player::~Player()
{}

// Load assets
bool Player::Start()
{
	LOG("Loading player");

	fire = App->audio->LoadFx("Assets/fire.ogg");

	shipPos = { 100,500 };

	spaceship = App->physics->CreateChain(shipPos.x, shipPos.y, spaceshipChain, 34);

	return true;
}

// Unload assets
bool Player::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status Player::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_W)==KEY_REPEAT) shipPos.y + 30;

	
	return UPDATE_CONTINUE;
}



