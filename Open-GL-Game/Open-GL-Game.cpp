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

    // While the User doesn't want to Quit (X Button, Alt+F4)
    while (!window.shouldClose()) // window -> window.window
    {
        window.processInput();

        window.clear();

        cube.rotation.x = glfwGetTime();
        cube.rotation.y = glfwGetTime() * 0.8f;
        cube.rotation.z = glfwGetTime() * 0.6f;
        cube.render();

        window.present();
    }
    // Cleans up all the GLFW stuff
    glfwTerminate();
    return 0;
}