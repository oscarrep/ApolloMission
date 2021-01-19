#pragma once

#include "p2List.h"
#include "Globals.h"

class Module;
class Render;
class Window;
class Textures;
class Input;
class Audio;
class Player;
class Scene;
class Physics;

class Application
{
public:
	Render* renderer;
	Window* window;
	Textures* textures;
	Input* input;
	Audio* audio;
	Player* player;
	Scene* scene;
	Physics* physics;

private:

	p2List<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	float dt = 0.0f;

	void AddModule(Module* mod);
};