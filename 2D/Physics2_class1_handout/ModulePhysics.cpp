#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"

// TODO 1: Include Box 2 header and library

#include "Box2D/Box2D/Box2D.h" //header

#ifdef _DEBUG //if _DEBUG is defined...
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" ) //debug library
#else //if _DEBUG is not defined, then use Release
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" ) //release library
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	// TODO 2: Create a private variable for the world
	// - You need to send it a default gravity
	// - You need init the world in the constructor
	// - Remember to destroy the world after using it

	gravity = b2Vec2(0.0f, 9.81f);
	world = new b2World(gravity);

	// TODO 4: Create a a big static circle as "ground"

	groundBodyDef.position.Set(PIXELS_TO_METERS(SCREEN_WIDTH / 2), PIXELS_TO_METERS(SCREEN_HEIGHT / 2));
	groundBody = world->CreateBody(&groundBodyDef);
	
	groundCircle.m_radius = PIXELS_TO_METERS(250);
	
	groundBody->CreateFixture(&groundCircle, 0.0f);

	// HOMEWORK: Try creating a box under the big circle as bottom ground

/*	groundBodyDef.position.Set(PIXELS_TO_METERS(SCREEN_WIDTH / 2), PIXELS_TO_METERS(SCREEN_HEIGHT));
	groundBody = world->CreateBody(&groundBodyDef);

	groundBox.SetAsBox(PIXELS_TO_METERS(SCREEN_WIDTH), PIXELS_TO_METERS(100)); //SetAsBox(half_width, half_height);

	groundBody->CreateFixture(&groundBox, 0.0f);*/
	
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	// TODO 3: Update the simulation ("step" the world)

	world->Step(timeStep, velocityIterations, positionIterations);

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	// TODO 5: On space bar press, create a circle on mouse position
	// - You need to transform the position / radius

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		
		//Creating a Dynamic Body

		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(PIXELS_TO_METERS(App->input->GetMouseX()), PIXELS_TO_METERS(App->input->GetMouseY()));
		body = world->CreateBody(&bodyDef);

		dynamicCircle_radius = rand() % 80 + 20;
		dynamicCircle.m_radius = PIXELS_TO_METERS(dynamicCircle_radius);

		fixtureDef.shape = &dynamicCircle;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		body->CreateFixture(&fixtureDef);
	}

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
					
					break;
				}
				case b2Shape::e_polygon:
				{
					b2PolygonShape* shape = (b2PolygonShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();

					SDL_Rect rect;

					int a, b, c, d, e, f, g, h, i, j;

					rect.x = METERS_TO_PIXELS(pos.x) - METERS_TO_PIXELS(abs(shape->m_vertices[0].x));
					rect.y = METERS_TO_PIXELS(pos.y) - METERS_TO_PIXELS(abs(shape->m_vertices[0].y));

					rect.w = METERS_TO_PIXELS(abs(shape->m_vertices[0].x) * 2);
					rect.h = METERS_TO_PIXELS(abs(shape->m_vertices[0].y) * 2);

					//abs(m_vertices[0].x) = half_width;
					//abs(m_vertices[0].y) = half_height;

					//m_vertices[0] = (-, -); [1] = (+, -); [2] = (+, +); [3] = (-, +)

					App->renderer->DrawQuad(rect, 255, 255, 255);

					break;
				}

				break;

				// You will have to add more cases to draw boxes, edges, and polygons ...
			}
		}
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!

	if (world != nullptr)
		delete world;
	world = nullptr;

	return true;
}
