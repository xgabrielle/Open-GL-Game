#pragma once
#include "glad/glad.h"
class Shader
{

public:
    unsigned int shaderId;
	Shader(const char* source, int shaderType) // when constructed: load shader on GPU
	{   
        shaderId = { glCreateShader(shaderType) };
        glShaderSource(shaderId, 1, &source, nullptr);
        glCompileShader(shaderId);
	}

    Shader (const Shader&) = delete; // avoid being cloned
    ~Shader() // when destructed: delete the shader from GPU
    {
        glDeleteShader(shaderId);
    }
    
};

