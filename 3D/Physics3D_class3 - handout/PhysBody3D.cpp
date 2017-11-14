#include "PhysBody3D.h"
#include "glmath.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// TODO 4: Fill in PhysBody methods. Remember to use 
// get/setOpenGLMatrix methods

// ---------------------------------------------------------
PhysBody3D::PhysBody3D(btRigidBody* body)
{}

// ---------------------------------------------------------
PhysBody3D::~PhysBody3D()
{}

// ---------------------------------------------------------
void PhysBody3D::GetTransform(float* matrix) const
{
	btTransform transform;
	transform.getOpenGLMatrix(matrix);
}

// ---------------------------------------------------------
void PhysBody3D::SetTransform(const float* matrix) const
{
	btTransform transform;
	transform.setFromOpenGLMatrix(matrix);

	btTransform body_trans = this->body->getWorldTransform();

	btTransform ret = body_trans * transform;
	ret.getOpenGLMatrix((btScalar*) matrix);
}

// ---------------------------------------------------------
void PhysBody3D::SetPos(float x, float y, float z)
{
}
