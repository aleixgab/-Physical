#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "math.h"

#include "Box2D/Box2D/Box2D.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));

	// big static circle as "ground" in the middle of the screen
	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 1.5f;
	int diameter = SCREEN_WIDTH / 2;

	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(diameter) * 0.5f;

	b2FixtureDef fixture;
	fixture.shape = &shape;
	b->CreateFixture(&fixture);

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
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
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetVertexCount();
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
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
	delete world;

	return true;
}

//Creation of Circle
BodyHolder* ModulePhysics::CreateDCircle(int mouse_x, int mouse_y, int rad) {

	b2BodyDef body;
	body.type = b2_dynamicBody;
	float radius = PIXEL_TO_METERS(rad);
	body.position.Set(PIXEL_TO_METERS(mouse_x), PIXEL_TO_METERS(mouse_y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = radius;
	b2FixtureDef fixture;
	fixture.shape = &shape;

	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	BodyHolder* a = new BodyHolder(b);
	return a;
}
BodyHolder* ModulePhysics::CreateSCircle(int mouse_x, int mouse_y, int rad) {

	b2BodyDef body;
	body.type = b2_staticBody;
	float radius = PIXEL_TO_METERS(rad);
	body.position.Set(PIXEL_TO_METERS(mouse_x), PIXEL_TO_METERS(mouse_y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = radius;
	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	BodyHolder* a = new BodyHolder(b);
	return a;
}
BodyHolder* ModulePhysics::CreateKCircle(int mouse_x, int mouse_y, int rad) {

	b2BodyDef body;
	body.type = b2_kinematicBody;
	float radius = PIXEL_TO_METERS(rad);
	body.position.Set(PIXEL_TO_METERS(mouse_x), PIXEL_TO_METERS(mouse_y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = radius;
	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	BodyHolder* a = new BodyHolder(b);
	return a;
}

//Creation of Rectangle
BodyHolder* ModulePhysics::CreateDRectangle(int mouse_x, int mouse_y, int hx, int hy) {
	
	// TODO 1: When pressing 2, create a box on the mouse position

	b2BodyDef body;
	body.type = b2_dynamicBody;

	//float hx = rand() % 3 + 1;
	//float hy = rand() % 3 + 1;

	body.position.Set(PIXEL_TO_METERS(mouse_x), PIXEL_TO_METERS(mouse_y));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape shape;
	shape.SetAsBox(PIXEL_TO_METERS(hx), PIXEL_TO_METERS(hy));

	b2FixtureDef fixture;
	fixture.shape = &shape;

	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	// TODO 2: To have the box behave normally, set fixture's density to 1.0f

	BodyHolder* a = new BodyHolder(b);
	return a;
}
BodyHolder* ModulePhysics::CreateSRectangle(int mouse_x, int mouse_y, int hx, int hy) {

	// TODO 1: When pressing 2, create a box on the mouse position

	b2BodyDef body;
	body.type = b2_staticBody;

	//float hx = rand() % 3 + 1;
	//float hy = rand() % 3 + 1;

	body.position.Set(PIXEL_TO_METERS(mouse_x), PIXEL_TO_METERS(mouse_y));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape shape;
	shape.SetAsBox(PIXEL_TO_METERS(hx), PIXEL_TO_METERS(hy));

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	// TODO 2: To have the box behave normally, set fixture's density to 1.0f

	BodyHolder* a = new BodyHolder(b);
	return a;
}
BodyHolder* ModulePhysics::CreateKRectangle(int mouse_x, int mouse_y, int hx, int hy) {

	// TODO 1: When pressing 2, create a box on the mouse position

	b2BodyDef body;
	body.type = b2_kinematicBody;

	//float hx = rand() % 3 + 1;
	//float hy = rand() % 3 + 1;

	body.position.Set(PIXEL_TO_METERS(mouse_x), PIXEL_TO_METERS(mouse_y));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape shape;
	shape.SetAsBox(PIXEL_TO_METERS(hx), PIXEL_TO_METERS(hy));

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	// TODO 2: To have the box behave normally, set fixture's density to 1.0f

	BodyHolder* a = new BodyHolder(b);
	return a;
}

//Creation of Chain
BodyHolder* ModulePhysics::CreateDChain(int mouse_x, int mouse_y, int points[], int index) {
	
	// TODO 3: Create a chain shape using those vertices
	// remember to convert them from pixels to meters!

	b2BodyDef body;
	body.type = b2_dynamicBody;

	body.position.Set(PIXEL_TO_METERS(mouse_x), PIXEL_TO_METERS(mouse_y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;

	b2Vec2* vertices = new b2Vec2[index / 2];

	for (int i = 0; i < index / 2; i++) {
		vertices[i] = { PIXEL_TO_METERS(points[2 * i]), PIXEL_TO_METERS(points[2 * i + 1]) };
	}

	shape.CreateChain(vertices, index / 2); //Difference between CreateChain() and CreateLoop()???

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	if (vertices != nullptr) //¿Dónde se tendría que hacer este delete?
		delete[] vertices;
	vertices = nullptr;

	BodyHolder* a = new BodyHolder(b);
	return a;
}
BodyHolder* ModulePhysics::CreateSChain(int mouse_x, int mouse_y, int points[], int index) {

	// TODO 3: Create a chain shape using those vertices
	// remember to convert them from pixels to meters!

	b2BodyDef body;
	body.type = b2_staticBody;

	body.position.Set(PIXEL_TO_METERS(mouse_x), PIXEL_TO_METERS(mouse_y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;

	b2Vec2* vertices = new b2Vec2[index / 2];

	for (int i = 0; i < index / 2; i++) {
		vertices[i] = { PIXEL_TO_METERS(points[2 * i]), PIXEL_TO_METERS(points[2 * i + 1]) };
	}

	shape.CreateChain(vertices, index / 2); //Difference between CreateChain() and CreateLoop()???

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	if (vertices != nullptr) //¿Dónde se tendría que hacer este delete?
		delete[] vertices;
	vertices = nullptr;

	BodyHolder* a = new BodyHolder(b);
	return a;
}
BodyHolder* ModulePhysics::CreateKChain(int mouse_x, int mouse_y, int points[], int index) {

	// TODO 3: Create a chain shape using those vertices
	// remember to convert them from pixels to meters!

	b2BodyDef body;
	body.type = b2_kinematicBody;

	body.position.Set(PIXEL_TO_METERS(mouse_x), PIXEL_TO_METERS(mouse_y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;

	b2Vec2* vertices = new b2Vec2[index / 2];

	for (int i = 0; i < index / 2; i++) {
		vertices[i] = { PIXEL_TO_METERS(points[2 * i]), PIXEL_TO_METERS(points[2 * i + 1]) };
	}

	shape.CreateChain(vertices, index / 2); //Difference between CreateChain() and CreateLoop()???

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	if (vertices != nullptr) //¿Dónde se tendría que hacer este delete?
		delete[] vertices;
	vertices = nullptr;

	BodyHolder* a = new BodyHolder(b);
	return a;
}

//BodyHolder class methods implementation
b2Vec2 BodyHolder::Position() {
	
	b2Vec2 position = body->GetPosition();
	b2Vec2 to_return = position;

	to_return.x = METERS_TO_PIXELS(to_return.x);
	to_return.y = METERS_TO_PIXELS(to_return.y);
	
	return to_return;
}

uint BodyHolder::GetType() const {
	return body->GetFixtureList()->GetShape()->GetType();
}

float BodyHolder::GetRadius() const { //in pixels. ONLY for Circles
	b2PolygonShape* shape = (b2PolygonShape*)body->GetFixtureList()->GetShape();
	return shape->m_radius;
}

float BodyHolder::Get_hx() const { //in pixels. ONLY for Boxes (half width of the box)
	b2PolygonShape* shape = (b2PolygonShape*)body->GetFixtureList()->GetShape();
	return abs(shape->m_vertices[0].x);
} 

float BodyHolder::Get_hy() const { //in pixels. ONLY for Boxes (half height of the box)
	b2PolygonShape* shape = (b2PolygonShape*)body->GetFixtureList()->GetShape();
	return abs(shape->m_vertices[0].y);
}

float BodyHolder::GetRotation() const { //in degrees
	return RADTODEG * body->GetAngle();
}

float BodyHolder::GetAngularVelocity() const {
	return RADTODEG * body->GetAngularVelocity();
}