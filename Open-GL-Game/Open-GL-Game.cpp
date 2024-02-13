#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "GameObject.h"
#include "stb_image.h"
#include "Texture.h"
#include <vector>

using namespace std;

void processInput(GLFWwindow*);

int main() {

    Window window{ 800,600 }; // GLFW, GLAD, glViewport

    Texture container{ "container.jpg", GL_TEXTURE0 };
    Texture wall{ "wall.jpg", GL_TEXTURE1 };
    Texture face{ "awesomeface.png", GL_TEXTURE0 };

    Shader vertexShader{ "vertexShader.glsl", GL_VERTEX_SHADER };
    Shader orangeShader{ "orangeFragmentShader.glsl", GL_FRAGMENT_SHADER };
    Shader textureShader{ "textureFragmentShader.glsl", GL_FRAGMENT_SHADER };

    // -------- Create Orange Shader Program (Render Pipeline) ---------
    Material orange{ vertexShader, orangeShader };
    Material textured{ vertexShader, textureShader };

    GameObject cube{ &textured, Mesh::createCube(), &wall };

    Vector3 cubePositions[] =
    {
        Vector3(0.0f,0.0f,0.0f),
        Vector3(2.0f,5.0f,-15.0f),
        Vector3(-1.5f,-2.2f,-2.5f),
        Vector3(-3.8f,-2.0f,-12.3f),
        Vector3(2.4f,-0.4f,-3.5f),
        Vector3(-1.7f,3.0f,-7.5f),
        Vector3(1.3f,-2.0f,-2.5f),
        Vector3(1.5f,2.0f,-2.5f),
        Vector3(1.5f,0.2f,-1.5f),
        Vector3(-1.3f,1.0f,-1.5f)
    };
    vector<GameObject*> gameObject{};
    for (size_t i = 0; i < size(cubePositions); i++)
    {
        GameObject*newCube(new GameObject{ &textured, Mesh::createCube(),&wall });
        newCube->rotation.z = i * 0.1f;
        newCube->rotation.x = i * 0.1 + 0.5f;
        newCube->position = cubePositions[i], gameObject.push_back(newCube);
    }

    // While the User doesn't want to Quit (X Button, Alt+F4)
    while (!window.shouldClose()) // window -> window.window
    {
        window.processInput();

        window.clear();

        for ( GameObject* gameObject : gameObject)
        {
            gameObject->render(glfwGetTime());
        }
        /*cube.rotation.x = glfwGetTime();
        cube.rotation.y = glfwGetTime() * 0.8f;
        cube.rotation.z = glfwGetTime() * 0.6f;
        cube.render();*/

        window.present();
    }
    // Cleans up all the GLFW stuff
    glfwTerminate();
    return 0;
}