#pragma once

#include <vector>
#include <glew.h>
#include <glm\glm.hpp>

class Model
{
public:
	Model( std::vector<glm::vec3> vertices, std::vector<GLushort> faces );
	virtual ~Model();

	void draw();

private:
	GLuint _vboIndex;
	GLuint _vaoIndex;

	std::vector<glm::vec3> _vertices;
	std::vector<GLushort> _faces;
};

