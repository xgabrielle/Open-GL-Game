#pragma once
#include "glad/glad.h"
class Shader
{

public:
    unsigned int shaderId;
	Shader(const char* source, int shaderType) 
	{   
        shaderId = { glCreateShader(shaderType) };
        glShaderSource(shaderId, 1, &source, nullptr);
        glCompileShader(shaderId);
	}

    Shader (const Shader&) = delete; 
    ~Shader() 
    {
        glDeleteShader(shaderId);
    }
    
};

