#pragma once
#include "Module.h"
#include "Globals.h"

#include "Box2D/Box2D/Box2D.h" //header

#define SCALE 0.01f //1 meter = 100 pixels

#define METERS_TO_PIXELS(x) x/SCALE //pixels
#define PIXELS_TO_METERS(x) x*SCALE //meters

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

private:

	bool debug;

	b2Vec2 gravity;
	b2World* world;

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 8;
	int32 positionIterations = 3;

	// Creating a Body

	b2BodyDef groundBodyDef;
	b2Body* groundBody;

	// Creating a Ground Circle

	b2CircleShape groundCircle;

	// Creating a Ground Box

	b2PolygonShape groundBox;

	// Creating a Dynamic Body

	b2BodyDef bodyDef;
	b2Body* body;
	b2CircleShape dynamicCircle;
	b2FixtureDef fixtureDef;

	int32 dynamicCircle_radius;
};