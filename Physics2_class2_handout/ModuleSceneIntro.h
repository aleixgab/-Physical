#pragma once
#include "Module.h"
#include "p2List.h"
#include "Globals.h"

class PhysBody;
class b2Vec2;
class BodyHolder;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;

	int rick_head[66] = {
		41, 0,
		76, 33,
		87, 5,
		95, 40,
		112, 36,
		104, 59,
		106, 63,
		117, 67,
		109, 74,
		110, 87,
		106, 93,
		110, 100,
		103, 106,
		100, 116,
		106, 121,
		104, 126,
		99, 127,
		95, 139,
		87, 146,
		75, 149,
		59, 145,
		47, 133,
		35, 137,
		40, 126,
		25, 125,
		32, 116,
		11, 103,
		29, 91,
		0, 76,
		30, 63,
		14, 36,
		43, 39,
		41, 0
	};

	p2List<BodyHolder*> shapes;
};
