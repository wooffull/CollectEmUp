#include "Triangle.h"

const float& Triangle::SIZE = 0.1f;

Triangle::Triangle() :
	GameObject()
{
	setFixed( false );
	setMass( 0.65f );
	
	// Add event listener to self for when the triangle has been added
	Callback cAdded = std::bind( &Triangle::onAdded, this, std::placeholders::_1 );
	addEventListener( Event::ADDED, cAdded );

	// Add event listener to self for when the triangle has been removed
	Callback cRemoved = std::bind( &Triangle::onRemoved, this, std::placeholders::_1 );
	addEventListener( Event::REMOVED, cRemoved );
}

Triangle::~Triangle()
{
	delete _shape;
}

void Triangle::onAdded( Event e )
{
	GLfloat* verts = new GLfloat[6];
	verts[0] = 0;
	verts[1] = SIZE * 0.5f;
	verts[2] = SIZE * 0.5f;
	verts[3] = -SIZE * 0.5f;
	verts[4] = -SIZE * 0.5f;
	verts[5] = -SIZE * 0.5f;

	Shape* shape = new Shape( verts, 3, _programIndex );
	setShape( shape );

	delete[] verts;
}

void Triangle::onRemoved( Event e )
{
}