#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	// TODO 2: Place the camera one unit up in Y and one unit to the right
	// experiment with different camera placements, then use LookAt()
	// to make it look at the center

	App->camera->Position.y += 1;
	App->camera->Position.x += 1;

	App->camera->LookAt({0,0,0});

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
	// TODO 1: Create a Plane primitive. This uses the plane formula
	// so you have to express the normal of the plane to create 
	// a plane centered around 0,0. Make that it draw the axis for reference
	Plane p;
	p.axis = true;
	p.Render();

	// TODO 6: Draw a sphere of 0.5f radius around the center
	// Draw somewhere else a cube and a cylinder in wireframe

	Sphere s;
	s.axis = true;
	s.radius = 0.5f;
	s.InnerRender();

	Cube cb;
	cb.axis = true;
	cb.wire = true;
	cb.size = {2,2,2};
	cb.SetPos(1,1,-5);
	cb.Render();

	Cylinder cy;
	cy.axis = true;
	cy.wire = true;
	cy.SetPos(-2, 1, -2);
	cy.SetRotation(90, { 0,1,0 });
	cy.Render();

	return UPDATE_CONTINUE;
}

