#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "../Maths/Matrix4x4.h"


class GameObject
{
    const Mesh* mesh{};
    Material* material{};
    Texture* texture{};
    

public:
    float red;
    Vector3 position = Vector3(0, 0, 0);
    Vector3 rotation = Vector3(0, 0, 0);
    GameObject(Material* _material, const Mesh* _mesh, Texture* _texture = nullptr) {
        mesh = _mesh;
        material = _material;
        texture = _texture;
    }

    void render(float time) {

        material->use();

        int tintLocation = glGetUniformLocation(
            material->shaderProgram, "tintColor");
        glUniform4f(tintLocation, red, 0, 0, 1);

        Matrix4x4 model = Matrix4x4::Translation(position) * Matrix4x4::Rotation(rotation);
        unsigned int transformLocation = glGetUniformLocation(
            material->shaderProgram, "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_TRUE, &model.m11);
        Matrix4x4 view = Matrix4x4::Translation(Vector3{ 0,0,(sin(time)+2)* - 3});
        unsigned int viewLoc = glGetUniformLocation(material->shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_TRUE, &view.m11);

        float fov = 46.0f / 360 * 2 * 3.14;
        float aspectRatio = 800.0f / 600;
        Matrix4x4 projection = Matrix4x4::Perspective(fov, aspectRatio, 0.1f, 100.0f);
        unsigned int projectionLoc = glGetUniformLocation(material->shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, &projection.m11);

        /*projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1F, 100.0F);
        view = glm::translation(view, glm::vec3(0.0f, 0.0f, -3.0f));*/

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

        int textureLocation = glGetUniformLocation(
            material->shaderProgram, "textureShader");
        glUniform1i(textureLocation, 1);

        mesh->render();
    }
};
