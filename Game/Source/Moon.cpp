#include "Defs.h"
#include "Moon.h"
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Scene.h"
#include "Animation.h"
#include "Window.h"
#include "SString.h"

Moon::Moon() : Module()
{
	LoadAnim();
}

bool Moon::Awake()
{

	return true;
}


bool Moon::Start()
{
	moonTex = app->tex->Load("Assets/textures/moon.png");

	rect.x = 900;
	rect.y = 1000;
	rect.w = 200;
	rect.h = 200;

	colliderMoon = app->physicsEngine->AddCollider(rect, ColliderType::COLLIDER_MOON, this);
	//colliderMoon = app->physicsEngine->AddColliderCircle(900, 5600, 300, ColliderType::COLLIDER_MOON, this);

	return true;
}

bool Moon::PreUpdate()
{


	currentAnim = &moonAnim;


	return true;
}

bool Moon::Update(float dt)
{

	return true;
}

bool Moon::PostUpdate()
{
	app->render->DrawTexture(moonTex, (int)spawnPos.x, (int)spawnPos.y, &currentAnim->GetCurrentFrame(), 1.0f);
	//colliderMoon->SetPos(rect.x, rect.y);
	return true;
}

bool Moon::CleanUp()
{
	app->tex->UnLoad(moonTex);
	/*if (colliderPlayer != nullptr)
		colliderPlayer->toDelete = true;*/

	return true;
}

iPoint Moon::GetPos() const
{
	return spawnPos;
}

void Moon::OnCollision(Collider* col1, Collider* col2) { app->physicsEngine->doCollisions(col1, col2); }


void Moon::LoadAnim()
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


