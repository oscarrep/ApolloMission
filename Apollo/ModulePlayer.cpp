#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleAudio.h"


ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	fire = App->audio->LoadFx("Assets/fire.ogg");

	shipPos = { 100,500 };

	spaceship = App->physics->CreateChain(shipPos.x, shipPos.y, spaceshipChain, 34);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_W)==KEY_REPEAT) shipPos.y + 30;

	
	return UPDATE_CONTINUE;
}



