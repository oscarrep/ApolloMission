#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Player.h"
#include "Map.h"
#include "EntityManager.h"
//#include "Physics.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	app->audio->PlayMusic("Assets/Audio/space_riddle.ogg");
	app->map->Load("level2.tmx");

	/*ship = app->tex->Load("Assets/Textures/spaceship.png");
	moon = app->tex->Load("Assets/Textures/moon.png");
	earth = app->tex->Load("Assets/Textures/earth.png");
	asteroids = app->tex->Load("Assets/Textures/asteroid.png");*/

	app->render->camera.x = app->render->camera.y = 0;
	
	app->entityManager->player->Start();

	backgroundrect.x = 0;
	backgroundrect.y = 0;
	backgroundrect.w = 1920;
	backgroundrect.h = 1080;

	//moonColl = app->collisions->AddColliderCircle(0, 0, 50, COLLIDER_TYPE::COLLIDER_PLANET, this);

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	Mix_VolumeMusic(volume);

	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) { volume++; LOG("volume--"); }
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) { volume--; LOG("volume++"); }

	app->map->Draw();
	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
