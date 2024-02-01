#pragma once

#include "Mesh.h"
#include "Material.h"

class Triangle
{
    Mesh* mesh;
    Material* material;

public:
    float red;
    float horizontalOffset;
    Triangle(Material* _material, Mesh* _mesh) {
        mesh = _mesh;
        material = _material;
    }

    void render() {
        material->use();

        int tintLocation = glGetUniformLocation(
            material->shaderProgram, "tintColor");
        glUniform4f(tintLocation, red, 0, 0, 1);

        int offsetLocation = glGetUniformLocation(
            material->shaderProgram, "horizontalOffset");
        glUniform1f(offsetLocation, horizontalOffset);

        int diffuseLocation = glGetUniformLocation(
            material->shaderProgram, "diffuseTexture");
        glUniform1i(diffuseLocation, 0);

        int blendLocation = glGetUniformLocation(
            material->shaderProgram, "blendTexture");
        glUniform1i(blendLocation, 1);

        mesh->render();
    }
};

// extend the triangle to have data members (fields)
//    - red, green, blue CHECK
//    - pass those data members to your uniform
// in your main function:
//    - pass in red color (1,0,0) for the first CHECK
//    - and green color (0,1,0) for the second CHECK

// result: one red, one green triangle
//         both using the same shader (like in Unity)

// if done early: play around with meshes
// can you make any polygon?
// triangle, square, pentagon, hexagon, ...
