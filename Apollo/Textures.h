#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2List.h"
#include "SDL\include\SDL.h"

class Textures : public Module
{
public:
	Textures(Application* app, bool start_enabled = true);
	~Textures();

	bool Init();
	bool CleanUp();

	SDL_Texture* const Load(const char* path);
	void Unload(SDL_Texture* texture);

public:
	p2List<SDL_Texture*> textures;
};