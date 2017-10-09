#pragma once
#include "Module.h"
#include "Globals.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

class b2World;
class b2Body;
class b2Vec2;

// TODO 6: Create a small class that keeps a pointer to tghe b2Body
// and has a method to request the position
// then write the implementation in the .cpp
// Then make your circle creation function to return a pointer to that class

class BodyHolder {
private:
	b2Body* body;
public:
	BodyHolder(b2Body* body) :body(body) {}

	uint GetType() const;
	b2Vec2 Position();

	float GetRadius() const; //in pixels. ONLY for Circles
	float Get_hx() const; //in pixels. ONLY for Boxes (half width of the box)
	float Get_hy() const; //in pixels. ONLY for Boxes (half height of the box)

	float GetRotation() const; //in degrees
	float GetAngularVelocity() const;
};

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	// TODO 4: Move body creation to 3 functions to create circles, rectangles and chains

	BodyHolder* CreateDCircle(int mouse_x, int mouse_y, int rad);
	BodyHolder* CreateSCircle(int mouse_x, int mouse_y, int rad);
	BodyHolder* CreateKCircle(int mouse_x, int mouse_y, int rad);

	BodyHolder* CreateDRectangle(int mouse_x, int mouse_y, int hx, int hy);
	BodyHolder* CreateSRectangle(int mouse_x, int mouse_y, int hx, int hy);
	BodyHolder* CreateKRectangle(int mouse_x, int mouse_y, int hx, int hy);

	BodyHolder* CreateDChain(int mouse_x, int mouse_y, int points[], int index);
	BodyHolder* CreateSChain(int mouse_x, int mouse_y, int points[], int index);
	BodyHolder* CreateKChain(int mouse_x, int mouse_y, int points[], int index);

private:

	bool debug;
	b2World* world;
};