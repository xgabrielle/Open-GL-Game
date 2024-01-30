#pragma once
#include "Mesh.h"
#include "Material.h"
#include "glad/glad.h"

class Triangle
{
	Mesh* mesh;
	Material* material;

public:
	float red;
	float green;
	float blue;
	Triangle(Material* _material, Mesh* _mesh )
	{
		mesh = _mesh;
		material = _material;
	}

	void render()
	{
		
		material->use();
		int tintLocation = glGetUniformLocation(material ->shaderProgram, "tintColor");
		glUniform4f(tintLocation, red, green, blue, 1);

		mesh->render();
	}
};

