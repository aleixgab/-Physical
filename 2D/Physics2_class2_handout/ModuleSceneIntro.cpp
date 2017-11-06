#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePhysics.h"

#include <iostream>

#include "Box2D/Box2D/Box2D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// TODO 5: Move all creation of bodies on 1,2,3 key press here in the scene
	
	// On space bar press, create a circle on mouse position

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) //Dynamic Circle
	{
		shapes.add(App->physics->CreateDCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) //Static Circle
	{
		shapes.add(App->physics->CreateSCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) //Kinematic Circle
	{
		shapes.add(App->physics->CreateKCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
	}

	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) //Dynamic Rectangle
	{
		shapes.add(App->physics->CreateDRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 50, 25));
	}

	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) //Static Rectangle
	{
		shapes.add(App->physics->CreateSRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 50, 25));
	}

	if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) //Kinematic Rectangle
	{
		shapes.add(App->physics->CreateKRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 50, 25));
	}

	if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) //Dynamic Chain
	{
		shapes.add(App->physics->CreateDChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 66));
	}

	if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN) //Static Chain
	{
		shapes.add(App->physics->CreateSChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 66));
	}

	if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) //Kinematic Chain
	{
		shapes.add(App->physics->CreateKChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 66));
	}

	// TODO 7: Draw all the circles using "circle" texture

		p2List_item<BodyHolder*>* item;
		item = shapes.getFirst();

		while (item != NULL)
		{
			b2Vec2 position = item->data->Position();

			if (item->data->GetType() == b2Shape::e_circle)
				App->renderer->Blit(circle, position.x - METERS_TO_PIXELS(item->data->GetRadius()), position.y - METERS_TO_PIXELS(item->data->GetRadius()), NULL, item->data->GetRotation(), position.x, position.y);
			if (item->data->GetType() == b2Shape::e_polygon) 
				App->renderer->Blit(box, position.x - METERS_TO_PIXELS(item->data->Get_hx()), position.y - METERS_TO_PIXELS(item->data->Get_hy()), NULL, item->data->GetRotation(), position.x, position.y);
			if (item->data->GetType() == b2Shape::e_chain)
				App->renderer->Blit(rick, position.x - METERS_TO_PIXELS(item->data->GetRadius()), position.y - METERS_TO_PIXELS(item->data->GetRadius()));
			
			item = item->next;
		}

	return UPDATE_CONTINUE;
}
