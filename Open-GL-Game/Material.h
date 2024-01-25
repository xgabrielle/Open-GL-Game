#pragma once
#include "glad/glad.h"
#include "Shader.h"

class Material
{
	unsigned int shaderProgram;
public:
	
	Material(Shader& vertexShader, Shader& fragmentShader)
	{
		
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader.shaderId);
		glAttachShader(shaderProgram, fragmentShader.shaderId);
		glLinkProgram(shaderProgram);
	}

	void use()
	{
		glUseProgram(shaderProgram);
	}

};

