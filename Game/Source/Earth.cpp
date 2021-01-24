#include "Defs.h"
#include "Earth.h"
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Scene.h"
#include "Animation.h"
#include "Window.h"
#include "SString.h"

Earth::Earth() : Module()
{
	LoadAnim();
}

bool Earth::Awake()
{

	return true;
}


bool Earth::Start()
{
	earthTex = app->tex->Load("Assets/textures/earth.png");

	rect.x = 950;
	rect.y = 5600;
	rect.w = 300;
	rect.h = 300;

	//colliderEarth = app->physicsEngine->AddCollider(rect, ColliderType::COLLIDER_EARTH, this);
	colliderEarth = app->physicsEngine->AddColliderCircle(900, 5600, 300, ColliderType::COLLIDER_EARTH, this);

	return true;
}

bool Earth::PreUpdate()
{


	currentAnim = &earthAnim;


	return true;
}

bool Earth::Update(float dt)
{

	return true;
}

bool Earth::PostUpdate()
{
	app->render->DrawTexture(earthTex, (int)spawnPos.x, (int)spawnPos.y, &currentAnim->GetCurrentFrame(), 1.0f);
	//colliderEarth->SetPos(rect.x, rect.y);
	return true;
}

bool Earth::CleanUp()
{
	app->tex->UnLoad(earthTex);
	/*if (colliderPlayer != nullptr)
		colliderPlayer->toDelete = true;*/

	return true;
}

iPoint Earth::GetPos() const
{
	return spawnPos;
}

void Earth::OnCollision(Collider* col1, Collider* col2) { app->physicsEngine->doCollisions(col1, col2); }


void Earth::LoadAnim()
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


