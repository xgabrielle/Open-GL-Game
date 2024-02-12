#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "../Maths/Matrix4x4.h"

class Triangle
{
    Mesh* mesh;
    Material* material;
    Texture* texture;

public:
    float red;
    Vector3 position = Vector3(0, 0, 0);
    Vector3 rotation = Vector3(0, 0, 0);
    Triangle(Material* _material, Mesh* _mesh, Texture* _texture = nullptr) {
        mesh = _mesh;
        material = _material;
        texture = _texture;
    }

    void render() {

        material->use();

        int tintLocation = glGetUniformLocation(
            material->shaderProgram, "tintColor");
        glUniform4f(tintLocation, red, 0, 0, 1);

        Matrix4x4 matTranslation = Matrix4x4::Translation(position);
        Matrix4x4 matRotation = Matrix4x4::Rotation(rotation);

        Matrix4x4 transform = matTranslation * matRotation;

        int transformLocation = glGetUniformLocation(
            material->shaderProgram, "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_TRUE, &transform.m11);

        int diffuseLocation = glGetUniformLocation(
            material->shaderProgram, "diffuseTexture");
        glUniform1i(diffuseLocation, 0);

        glActiveTexture(GL_TEXTURE0);

        if (texture != nullptr) {
            glBindTexture(GL_TEXTURE_2D, texture->textureId);
        }
        else {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        int blendLocation = glGetUniformLocation(
            material->shaderProgram, "blendTexture");
        glUniform1i(blendLocation, 1);

        mesh->render();
    }
};
