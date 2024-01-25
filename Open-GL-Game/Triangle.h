#pragma once
#include "Mesh.h"
#include "Material.h"
#include "glad/glad.h"

class Triangle
{
	Mesh* mesh;
	Material* material;

public:
	Triangle(Material* _material, Mesh* _mesh )
	{
		mesh = _mesh;
		material = _material;
	}

	void render()
	{
		material->use();
		mesh->render();
	}
};

