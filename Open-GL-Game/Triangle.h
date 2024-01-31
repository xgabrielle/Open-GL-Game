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
	float offsetX;
	float offsetY;
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

		int offsetLocation = glGetUniformLocation(material->shaderProgram, "offset");
		glUniform2f(offsetLocation,offsetX,offsetY);

		mesh->render();
	}
};

