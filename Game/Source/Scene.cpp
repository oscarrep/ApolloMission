#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
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

	background = app->tex->Load("Assets/Textures/purple_nebula2.png");
	asteroids = app->tex->Load("Assets/Textures/asteroid.png");
	ship = app->tex->Load("Assets/Textures/spaceship.png");
	moon = app->tex->Load("Assets/Textures/moon.png");
	earth = app->tex->Load("Assets/Textures/earth.png");

	app->render->camera.x = app->render->camera.y = 0;

	backgroundrect.x = 0;
	backgroundrect.y = 0;
	backgroundrect.w = 1920;
	backgroundrect.h = 1080;

	shipRect.x = 0;
	shipRect.y = 0;
	shipRect.w = 52;
	shipRect.h = 106;

	LoadAsteroid();
	LoadEarth();
	LoadMoon();

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
	if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) app->render->camera.y += 1;
	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) app->render->camera.y -= 1;
	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) app->render->camera.x -= 1;
	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) app->render->camera.x += 1;

	//app->render->DrawTexture(img, 380, 100);

	app->render->DrawTexture(background, 0, 0, &backgroundrect);
	app->render->DrawTexture(asteroids, 0, 0, &(asteroidAnim.GetCurrentFrame()));
	app->render->DrawTexture(earth, 900, 900, &(earthAnim.GetCurrentFrame()));
	app->render->DrawTexture(moon, 500, 0, &(moonAnim.GetCurrentFrame()));

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
	earthAnim.PushBack({ 0,	   0,  100, 100 });
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
	earthAnim.PushBack({ 1700, 0,  100, 100 });
	earthAnim.PushBack({ 1800, 0,  100, 100 });
	earthAnim.PushBack({ 1900, 0,  100, 100 });
	earthAnim.PushBack({ 2000, 0,  100, 100 });
	earthAnim.PushBack({ 2100, 0,  100, 100 });
	earthAnim.PushBack({ 2200, 0,  100, 100 });
	earthAnim.PushBack({ 2300, 0,  100, 100 });
	earthAnim.PushBack({ 2400, 0,  100, 100 });
	earthAnim.PushBack({ 2500, 0,  100, 100 });
	earthAnim.PushBack({ 2600, 0,  100, 100 });
	earthAnim.PushBack({ 2700, 0,  100, 100 });
	earthAnim.PushBack({ 2800, 0,  100, 100 });
	earthAnim.PushBack({ 2900, 0,  100, 100 });
	earthAnim.PushBack({ 3000, 0,  100, 100 });
	earthAnim.PushBack({ 3100, 0,  100, 100 });
	earthAnim.PushBack({ 3200, 0,  100, 100 });
	earthAnim.PushBack({ 3300, 0,  100, 100 });
	earthAnim.PushBack({ 3400, 0,  100, 100 });
	earthAnim.PushBack({ 3500, 0,  100, 100 });
	earthAnim.PushBack({ 3600, 0,  100, 100 });
	earthAnim.PushBack({ 3700, 0,  100, 100 });
	earthAnim.PushBack({ 3800, 0,  100, 100 });
	earthAnim.PushBack({ 3900, 0,  100, 100 });
	earthAnim.PushBack({ 4000, 0,  100, 100 });
	earthAnim.PushBack({ 4100, 0,  100, 100 });
	earthAnim.PushBack({ 4200, 0,  100, 100 });
	earthAnim.PushBack({ 4300, 0,  100, 100 });
	earthAnim.PushBack({ 4400, 0,  100, 100 });
	earthAnim.PushBack({ 4500, 0,  100, 100 });
	earthAnim.PushBack({ 4600, 0,  100, 100 });
	earthAnim.PushBack({ 4700, 0,  100, 100 });
	earthAnim.PushBack({ 4800, 0,  100, 100 });
	earthAnim.PushBack({ 4900, 0,  100, 100 });
	earthAnim.speed = 0.05f;

}

void Scene::LoadMoon()
{
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
	moonAnim.PushBack({ 1700, 0,  100, 100 });
	moonAnim.PushBack({ 1800, 0,  100, 100 });
	moonAnim.PushBack({ 1900, 0,  100, 100 });
	moonAnim.PushBack({ 2000, 0,  100, 100 });
	moonAnim.PushBack({ 2100, 0,  100, 100 });
	moonAnim.PushBack({ 2200, 0,  100, 100 });
	moonAnim.PushBack({ 2300, 0,  100, 100 });
	moonAnim.PushBack({ 2400, 0,  100, 100 });
	moonAnim.PushBack({ 2500, 0,  100, 100 });
	moonAnim.PushBack({ 2600, 0,  100, 100 });
	moonAnim.PushBack({ 2700, 0,  100, 100 });
	moonAnim.PushBack({ 2800, 0,  100, 100 });
	moonAnim.PushBack({ 2900, 0,  100, 100 });
	moonAnim.PushBack({ 3000, 0,  100, 100 });
	moonAnim.PushBack({ 3100, 0,  100, 100 });
	moonAnim.PushBack({ 3200, 0,  100, 100 });
	moonAnim.PushBack({ 3300, 0,  100, 100 });
	moonAnim.PushBack({ 3400, 0,  100, 100 });
	moonAnim.PushBack({ 3500, 0,  100, 100 });
	moonAnim.PushBack({ 3600, 0,  100, 100 });
	moonAnim.PushBack({ 3700, 0,  100, 100 });
	moonAnim.PushBack({ 3800, 0,  100, 100 });
	moonAnim.PushBack({ 3900, 0,  100, 100 });
	moonAnim.PushBack({ 4000, 0,  100, 100 });
	moonAnim.PushBack({ 4100, 0,  100, 100 });
	moonAnim.PushBack({ 4200, 0,  100, 100 });
	moonAnim.PushBack({ 4300, 0,  100, 100 });
	moonAnim.PushBack({ 4400, 0,  100, 100 });
	moonAnim.PushBack({ 4500, 0,  100, 100 });
	moonAnim.PushBack({ 4600, 0,  100, 100 });
	moonAnim.PushBack({ 4700, 0,  100, 100 });
	moonAnim.PushBack({ 4800, 0,  100, 100 });
	moonAnim.PushBack({ 4900, 0,  100, 100 });
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
