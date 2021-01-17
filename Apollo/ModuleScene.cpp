#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
	background = NULL;
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;
	App->audio->PlayMusic("Assets/space_riddle.ogg");

	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	background = App->textures->Load("Assets/purple_nebula2.png");
	asteroid = App->textures->Load("Assets/asteroid.png");
	ship = App->textures->Load("Assets/spaceship.png");
	moon = App->textures->Load("Assets/moon.png");
	earth = App->textures->Load("Assets/earth.png");

	backgroundrect.x = 0;
	backgroundrect.y = 0;
	backgroundrect.w = 1920;
	backgroundrect.h = 1080;
	
	asteroidAnim.PushBack({ 0,	  0,  100, 100 });
	asteroidAnim.PushBack({ 100,  0,  100, 100 });
	asteroidAnim.PushBack({ 200,  0,  100, 100 });
	asteroidAnim.PushBack({ 300,  0,  100, 100 });
	asteroidAnim.PushBack({ 400,  0,  100, 100 });
	asteroidAnim.PushBack({ 500,  0,  100, 100 });
	asteroidAnim.PushBack({ 600,  0,  100, 100 });
	asteroidAnim.PushBack({ 700,  0,  100, 100 });
	asteroidAnim.PushBack({ 800,  0,  100, 100 });
	asteroidAnim.PushBack({ 900,  0,  100, 100 });
	asteroidAnim.PushBack({ 1000, 0,  100, 100 });
	asteroidAnim.PushBack({ 1100, 0,  100, 100 });
	asteroidAnim.PushBack({ 1200, 0,  100, 100 });
	asteroidAnim.PushBack({ 1300, 0,  100, 100 });
	asteroidAnim.PushBack({ 1400, 0,  100, 100 });
	asteroidAnim.PushBack({ 1500, 0,  100, 100 });
	asteroidAnim.PushBack({ 1600, 0,  100, 100 });
	asteroidAnim.PushBack({ 1800, 0,  100, 100 });
	asteroidAnim.PushBack({ 1900, 0,  100, 100 });
	asteroidAnim.PushBack({ 2000, 0,  100, 100 });
	asteroidAnim.PushBack({ 2100, 0,  100, 100 });
	asteroidAnim.PushBack({ 2200, 0,  100, 100 });
	asteroidAnim.PushBack({ 2300, 0,  100, 100 });
	asteroidAnim.PushBack({ 2400, 0,  100, 100 });
	asteroidAnim.PushBack({ 2500, 0,  100, 100 });
	asteroidAnim.PushBack({ 2600, 0,  100, 100 });
	asteroidAnim.PushBack({ 2800, 0,  100, 100 });
	asteroidAnim.PushBack({ 2900, 0,  100, 100 });
	asteroidAnim.PushBack({ 3000, 0,  100, 100 });
	asteroidAnim.PushBack({ 3100, 0,  100, 100 });
	asteroidAnim.PushBack({ 3200, 0,  100, 100 });
	asteroidAnim.PushBack({ 3300, 0,  100, 100 });
	asteroidAnim.PushBack({ 3400, 0,  100, 100 });
	asteroidAnim.PushBack({ 3500, 0,  100, 100 });
	asteroidAnim.PushBack({ 3600, 0,  100, 100 });
	asteroidAnim.PushBack({ 3800, 0,  100, 100 });
	asteroidAnim.PushBack({ 3900, 0,  100, 100 });
	asteroidAnim.PushBack({ 4000, 0,  100, 100 });
	asteroidAnim.PushBack({ 4100, 0,  100, 100 });
	asteroidAnim.PushBack({ 4200, 0,  100, 100 });
	asteroidAnim.PushBack({ 4300, 0,  100, 100 });
	asteroidAnim.PushBack({ 4400, 0,  100, 100 });
	asteroidAnim.PushBack({ 4500, 0,  100, 100 });
	asteroidAnim.PushBack({ 4600, 0,  100, 100 });
	asteroidAnim.PushBack({ 4800, 0,  100, 100 });
	asteroidAnim.PushBack({ 4900, 0,  100, 100 });
	asteroidAnim.speed = 0.2f;

	earthAnim.PushBack({ 0,	  0,  100, 100 });
	earthAnim.PushBack({ 100,  0,  100, 100 });
	earthAnim.PushBack({ 200,  0,  100, 100 });
	earthAnim.PushBack({ 300,  0,  100, 100 });
	earthAnim.PushBack({ 400,  0,  100, 100 });
	earthAnim.PushBack({ 500,  0,  100, 100 });
	earthAnim.PushBack({ 600,  0,  100, 100 });
	earthAnim.PushBack({ 700,  0,  100, 100 });
	earthAnim.PushBack({ 800,  0,  100, 100 });
	earthAnim.PushBack({ 900,  0,  100, 100 });
	earthAnim.PushBack({ 1000, 0,  100, 100 });
	earthAnim.PushBack({ 1100, 0,  100, 100 });
	earthAnim.PushBack({ 1200, 0,  100, 100 });
	earthAnim.PushBack({ 1300, 0,  100, 100 });
	earthAnim.PushBack({ 1400, 0,  100, 100 });
	earthAnim.PushBack({ 1500, 0,  100, 100 });
	earthAnim.PushBack({ 1600, 0,  100, 100 });
	earthAnim.PushBack({ 1800, 0,  100, 100 });
	earthAnim.PushBack({ 1900, 0,  100, 100 });
	earthAnim.PushBack({ 2000, 0,  100, 100 });
	earthAnim.PushBack({ 2100, 0,  100, 100 });
	earthAnim.PushBack({ 2200, 0,  100, 100 });
	earthAnim.PushBack({ 2300, 0,  100, 100 });
	earthAnim.PushBack({ 2400, 0,  100, 100 });
	earthAnim.PushBack({ 2500, 0,  100, 100 });
	earthAnim.PushBack({ 2600, 0,  100, 100 });
	earthAnim.PushBack({ 2800, 0,  100, 100 });
	earthAnim.PushBack({ 2900, 0,  100, 100 });
	earthAnim.PushBack({ 3000, 0,  100, 100 });
	earthAnim.PushBack({ 3100, 0,  100, 100 });
	earthAnim.PushBack({ 3200, 0,  100, 100 });
	earthAnim.PushBack({ 3300, 0,  100, 100 });
	earthAnim.PushBack({ 3400, 0,  100, 100 });
	earthAnim.PushBack({ 3500, 0,  100, 100 });
	earthAnim.PushBack({ 3600, 0,  100, 100 });
	earthAnim.PushBack({ 3800, 0,  100, 100 });
	earthAnim.PushBack({ 3900, 0,  100, 100 });
	earthAnim.PushBack({ 4000, 0,  100, 100 });
	earthAnim.PushBack({ 4100, 0,  100, 100 });
	earthAnim.PushBack({ 4200, 0,  100, 100 });
	earthAnim.PushBack({ 4300, 0,  100, 100 });
	earthAnim.PushBack({ 4400, 0,  100, 100 });
	earthAnim.PushBack({ 4500, 0,  100, 100 });
	earthAnim.PushBack({ 4600, 0,  100, 100 });
	earthAnim.PushBack({ 4800, 0,  100, 100 });
	earthAnim.PushBack({ 4900, 0,  100, 100 });
	earthAnim.speed = 0.2f;

	moonAnim.PushBack({ 0,	  0,  100, 100 });
	moonAnim.PushBack({ 100,  0,  100, 100 });
	moonAnim.PushBack({ 200,  0,  100, 100 });
	moonAnim.PushBack({ 300,  0,  100, 100 });
	moonAnim.PushBack({ 400,  0,  100, 100 });
	moonAnim.PushBack({ 500,  0,  100, 100 });
	moonAnim.PushBack({ 600,  0,  100, 100 });
	moonAnim.PushBack({ 700,  0,  100, 100 });
	moonAnim.PushBack({ 800,  0,  100, 100 });
	moonAnim.PushBack({ 900,  0,  100, 100 });
	moonAnim.PushBack({ 1000, 0,  100, 100 });
	moonAnim.PushBack({ 1100, 0,  100, 100 });
	moonAnim.PushBack({ 1200, 0,  100, 100 });
	moonAnim.PushBack({ 1300, 0,  100, 100 });
	moonAnim.PushBack({ 1400, 0,  100, 100 });
	moonAnim.PushBack({ 1500, 0,  100, 100 });
	moonAnim.PushBack({ 1600, 0,  100, 100 });
	moonAnim.PushBack({ 1800, 0,  100, 100 });
	moonAnim.PushBack({ 1900, 0,  100, 100 });
	moonAnim.PushBack({ 2000, 0,  100, 100 });
	moonAnim.PushBack({ 2100, 0,  100, 100 });
	moonAnim.PushBack({ 2200, 0,  100, 100 });
	moonAnim.PushBack({ 2300, 0,  100, 100 });
	moonAnim.PushBack({ 2400, 0,  100, 100 });
	moonAnim.PushBack({ 2500, 0,  100, 100 });
	moonAnim.PushBack({ 2600, 0,  100, 100 });
	moonAnim.PushBack({ 2800, 0,  100, 100 });
	moonAnim.PushBack({ 2900, 0,  100, 100 });
	moonAnim.PushBack({ 3000, 0,  100, 100 });
	moonAnim.PushBack({ 3100, 0,  100, 100 });
	moonAnim.PushBack({ 3200, 0,  100, 100 });
	moonAnim.PushBack({ 3300, 0,  100, 100 });
	moonAnim.PushBack({ 3400, 0,  100, 100 });
	moonAnim.PushBack({ 3500, 0,  100, 100 });
	moonAnim.PushBack({ 3600, 0,  100, 100 });
	moonAnim.PushBack({ 3800, 0,  100, 100 });
	moonAnim.PushBack({ 3900, 0,  100, 100 });
	moonAnim.PushBack({ 4000, 0,  100, 100 });
	moonAnim.PushBack({ 4100, 0,  100, 100 });
	moonAnim.PushBack({ 4200, 0,  100, 100 });
	moonAnim.PushBack({ 4300, 0,  100, 100 });
	moonAnim.PushBack({ 4400, 0,  100, 100 });
	moonAnim.PushBack({ 4500, 0,  100, 100 });
	moonAnim.PushBack({ 4600, 0,  100, 100 });
	moonAnim.PushBack({ 4800, 0,  100, 100 });
	moonAnim.PushBack({ 4900, 0,  100, 100 });
	moonAnim.speed = 0.2f;

	
	return ret;
}

// Load assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleScene::Update()
{
	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
		circles.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = 
		{
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		//ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));
	}

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	//c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	App->renderer->Blit(background, 0, 0, &backgroundrect);
	App->renderer->Blit(asteroid, 0, 0, &(asteroidAnim.GetCurrentFrame()));
	App->renderer->Blit(earth, 1000, 1000, &(asteroidAnim.GetCurrentFrame()));
	App->renderer->Blit(moon, 500, 0, &(asteroidAnim.GetCurrentFrame()));


	return UPDATE_CONTINUE;
}

void ModuleScene::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	/*App->audio->PlayFx(bonus_fx);*/
}
