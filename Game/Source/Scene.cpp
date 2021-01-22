#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Player.h"
#include "Map.h"
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
	background = app->tex->Load("Assets/Textures/purple_nebula2.png");
	ship = app->tex->Load("Assets/Textures/spaceship.png");
	moon = app->tex->Load("Assets/Textures/moon.png");
	earth = app->tex->Load("Assets/Textures/earth.png");
	asteroids = app->tex->Load("Assets/Textures/asteroid.png");

	app->render->camera.x = app->render->camera.y = 0;
	app->player->Start();

	backgroundrect.x = 0;
	backgroundrect.y = 0;
	backgroundrect.w = 1920;
	backgroundrect.h = 1080;

	LoadAsteroid();
	LoadEarth();
	LoadMoon();

	moonColl = app->collisions->AddColliderCircle(0, 0, 50, COLLIDER_TYPE::COLLIDER_PLANET, this);

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

	app->render->DrawTexture(background, 0, 0, &backgroundrect);
	app->render->DrawTexture(asteroids, 0, 0, &(asteroidAnim.GetCurrentFrame()));
	app->render->DrawTexture(earth, 100, 500, &(earthAnim.GetCurrentFrame()));
	app->render->DrawTexture(moon, 900, -5000, &(moonAnim.GetCurrentFrame()));

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

	app->tex->UnLoad(background);
	app->tex->UnLoad(asteroids);
	app->tex->UnLoad(ship);
	app->tex->UnLoad(moon);
	app->tex->UnLoad(earth);

	return true;
}

void Scene::LoadEarth()
{
	earthAnim.PushBack({ 0,	    0,  300, 300 });
	earthAnim.PushBack({ 300,   0,  300, 300 });
	earthAnim.PushBack({ 600,   0,  300, 300 });
	earthAnim.PushBack({ 900,   0,  300, 300 });
	earthAnim.PushBack({ 1200,  0,  300, 300 });
	earthAnim.PushBack({ 1500,  0,  300, 300 });
	earthAnim.PushBack({ 1800,  0,  300, 300 });
	earthAnim.PushBack({ 2100,  0,  300, 300 });
	earthAnim.PushBack({ 2400,  0,  300, 300 });
	earthAnim.PushBack({ 2700,  0,  300, 300 });
	earthAnim.PushBack({ 3000,  0,  300, 300 });
	earthAnim.PushBack({ 3300,  0,  300, 300 });
	earthAnim.PushBack({ 3600,  0,  300, 300 });
	earthAnim.PushBack({ 3900,  0,  300, 300 });
	earthAnim.PushBack({ 4200,  0,  300, 300 });
	earthAnim.PushBack({ 4500,  0,  300, 300 });
	earthAnim.PushBack({ 4800,  0,  300, 300 });
	earthAnim.PushBack({ 5100,  0,  300, 300 });
	earthAnim.PushBack({ 5400,  0,  300, 300 });
	earthAnim.PushBack({ 5700,  0,  300, 300 });
	earthAnim.PushBack({ 6000,  0,  300, 300 });
	earthAnim.PushBack({ 6300,  0,  300, 300 });
	earthAnim.PushBack({ 6600,  0,  300, 300 });
	earthAnim.PushBack({ 6900,  0,  300, 300 });
	earthAnim.PushBack({ 7200,  0,  300, 300 });
	earthAnim.PushBack({ 7500,  0,  300, 300 });
	earthAnim.PushBack({ 7800,  0,  300, 300 });
	earthAnim.PushBack({ 8100,  0,  300, 300 });
	earthAnim.PushBack({ 8400,  0,  300, 300 });
	earthAnim.PushBack({ 8700,  0,  300, 300 });
	earthAnim.PushBack({ 9000,  0,  300, 300 });
	earthAnim.PushBack({ 9300,  0,  300, 300 });
	earthAnim.PushBack({ 9600,  0,  300, 300 });
	earthAnim.PushBack({ 9900,  0,  300, 300 });
	earthAnim.PushBack({ 10200, 0,  300, 300 });
	earthAnim.PushBack({ 10500, 0,  300, 300 });
	earthAnim.PushBack({ 10800, 0,  300, 300 });
	earthAnim.PushBack({ 11100, 0,  300, 300 });
	earthAnim.PushBack({ 11400, 0,  300, 300 });
	earthAnim.PushBack({ 11700, 0,  300, 300 });
	earthAnim.PushBack({ 12000, 0,  300, 300 });
	earthAnim.PushBack({ 12300, 0,  300, 300 });
	earthAnim.PushBack({ 12600, 0,  300, 300 });
	earthAnim.PushBack({ 12900, 0,  300, 300 });
	earthAnim.PushBack({ 13200, 0,  300, 300 });
	earthAnim.PushBack({ 13500, 0,  300, 300 });
	earthAnim.PushBack({ 13800, 0,  300, 300 });
	earthAnim.PushBack({ 14100, 0,  300, 300 });
	earthAnim.PushBack({ 14400, 0,  300, 300 });
	earthAnim.PushBack({ 14700, 0,  300, 300 });
	earthAnim.speed = 0.05f;

}

void Scene::LoadMoon()
{
	moonAnim.PushBack({ 0,	  0,  200, 200 });
	moonAnim.PushBack({ 200,  0,  200, 200 });
	moonAnim.PushBack({ 400,  0,  200, 200 });
	moonAnim.PushBack({ 600,  0,  200, 200 });
	moonAnim.PushBack({ 800,  0,  200, 200 });
	moonAnim.PushBack({ 1000, 0,  200, 200 });
	moonAnim.PushBack({ 1200, 0,  200, 200 });
	moonAnim.PushBack({ 1400, 0,  200, 200 });
	moonAnim.PushBack({ 1600, 0,  200, 200 });
	moonAnim.PushBack({ 1800, 0,  200, 200 });
	moonAnim.PushBack({ 2000, 0,  200, 200 });
	moonAnim.PushBack({ 2200, 0,  200, 200 });
	moonAnim.PushBack({ 2400, 0,  200, 200 });
	moonAnim.PushBack({ 2600, 0,  200, 200 });
	moonAnim.PushBack({ 2800, 0,  200, 200 });
	moonAnim.PushBack({ 3000, 0,  200, 200 });
	moonAnim.PushBack({ 3200, 0,  200, 200 });
	moonAnim.PushBack({ 3400, 0,  200, 200 });
	moonAnim.PushBack({ 3600, 0,  200, 200 });
	moonAnim.PushBack({ 3800, 0,  200, 200 });
	moonAnim.PushBack({ 4000, 0,  200, 200 });
	moonAnim.PushBack({ 4200, 0,  200, 200 });
	moonAnim.PushBack({ 4400, 0,  200, 200 });
	moonAnim.PushBack({ 4600, 0,  200, 200 });
	moonAnim.PushBack({ 4800, 0,  200, 200 });
	moonAnim.PushBack({ 5000, 0,  200, 200 });
	moonAnim.PushBack({ 5200, 0,  200, 200 });
	moonAnim.PushBack({ 5400, 0,  200, 200 });
	moonAnim.PushBack({ 5600, 0,  200, 200 });
	moonAnim.PushBack({ 5800, 0,  200, 200 });
	moonAnim.PushBack({ 6000, 0,  200, 200 });
	moonAnim.PushBack({ 6200, 0,  200, 200 });
	moonAnim.PushBack({ 6400, 0,  200, 200 });
	moonAnim.PushBack({ 6600, 0,  200, 200 });
	moonAnim.PushBack({ 6800, 0,  200, 200 });
	moonAnim.PushBack({ 7000, 0,  200, 200 });
	moonAnim.PushBack({ 7200, 0,  200, 200 });
	moonAnim.PushBack({ 7400, 0,  200, 200 });
	moonAnim.PushBack({ 7600, 0,  200, 200 });
	moonAnim.PushBack({ 7800, 0,  200, 200 });
	moonAnim.PushBack({ 8000, 0,  200, 200 });
	moonAnim.PushBack({ 8200, 0,  200, 200 });
	moonAnim.PushBack({ 8400, 0,  200, 200 });
	moonAnim.PushBack({ 8600, 0,  200, 200 });
	moonAnim.PushBack({ 8800, 0,  200, 200 });
	moonAnim.PushBack({ 9000, 0,  200, 200 });
	moonAnim.PushBack({ 9200, 0,  200, 200 });
	moonAnim.PushBack({ 9400, 0,  200, 200 });
	moonAnim.PushBack({ 9600, 0,  200, 200 });
	moonAnim.PushBack({ 9800, 0,  200, 200 });
	moonAnim.speed = 0.1f;
}

void Scene::LoadAsteroid()
{
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
	asteroidAnim.PushBack({ 1700, 0,  100, 100 });
	asteroidAnim.PushBack({ 1800, 0,  100, 100 });
	asteroidAnim.PushBack({ 1900, 0,  100, 100 });
	asteroidAnim.PushBack({ 2000, 0,  100, 100 });
	asteroidAnim.PushBack({ 2100, 0,  100, 100 });
	asteroidAnim.PushBack({ 2200, 0,  100, 100 });
	asteroidAnim.PushBack({ 2300, 0,  100, 100 });
	asteroidAnim.PushBack({ 2400, 0,  100, 100 });
	asteroidAnim.PushBack({ 2500, 0,  100, 100 });
	asteroidAnim.PushBack({ 2600, 0,  100, 100 });
	asteroidAnim.PushBack({ 2700, 0,  100, 100 });
	asteroidAnim.PushBack({ 2800, 0,  100, 100 });
	asteroidAnim.PushBack({ 2900, 0,  100, 100 });
	asteroidAnim.PushBack({ 3000, 0,  100, 100 });
	asteroidAnim.PushBack({ 3100, 0,  100, 100 });
	asteroidAnim.PushBack({ 3200, 0,  100, 100 });
	asteroidAnim.PushBack({ 3300, 0,  100, 100 });
	asteroidAnim.PushBack({ 3400, 0,  100, 100 });
	asteroidAnim.PushBack({ 3500, 0,  100, 100 });
	asteroidAnim.PushBack({ 3600, 0,  100, 100 });
	asteroidAnim.PushBack({ 3700, 0,  100, 100 });
	asteroidAnim.PushBack({ 3800, 0,  100, 100 });
	asteroidAnim.PushBack({ 3900, 0,  100, 100 });
	asteroidAnim.PushBack({ 4000, 0,  100, 100 });
	asteroidAnim.PushBack({ 4100, 0,  100, 100 });
	asteroidAnim.PushBack({ 4200, 0,  100, 100 });
	asteroidAnim.PushBack({ 4300, 0,  100, 100 });
	asteroidAnim.PushBack({ 4400, 0,  100, 100 });
	asteroidAnim.PushBack({ 4500, 0,  100, 100 });
	asteroidAnim.PushBack({ 4600, 0,  100, 100 });
	asteroidAnim.PushBack({ 4700, 0,  100, 100 });
	asteroidAnim.PushBack({ 4800, 0,  100, 100 });
	asteroidAnim.PushBack({ 4900, 0,  100, 100 });
	asteroidAnim.speed = 0.2f;
}
