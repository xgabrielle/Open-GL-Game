
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Triangle.h"
#include "stb_image.h"
#include "Texture.h"

using namespace std;

void processInput(GLFWwindow*);

int main() {

    Window window{ 800,600 };

    Texture container{ "container.jpg", GL_TEXTURE0};

    //stbi_set_flip_vertically_on_load(true);
    Texture wall{ "wall.jpg", GL_TEXTURE1};


    Vertex vertices[]{
           Vertex{Vector3{-1.0f, -0.5f, 0.0f}},
           Vertex{Vector3{ 0.0f, -0.5f, 0.0f}},
           Vertex{Vector3{-0.5f,  0.5f, 0.0f}},
           Vertex{Vector3{-1.0f, -0.5f, 0.0f}},
           Vertex{Vector3{-0.5f,  0.5f, 0.0f}},
           Vertex{Vector3{-1.0f, 0.5f, 0.0f}}
    };


    Mesh mesh1{ vertices, size(vertices) };

    Vertex vertices2[]{
        Vertex{Vector3{0.0f, -0.5f, 0.0f},Color::red},
        Vertex{Vector3{1.0f, -0.5f, 0.0f},Color::green},
        Vertex{Vector3{0.5f,  0.5f, 0.0f},Color::blue}
    };

    Mesh mesh2{ vertices2, size(vertices2) };

    Vertex vertices3[]{
        // positions                           // colors        // texture coords
        Vertex{Vector3{ 0.5f,  0.5f, 0.0f},  Color::red,     Vector2{ 1.0f, 1.0f }},   // top right
        Vertex{Vector3{ 0.5f, -0.5f, 0.0f},  Color::green,   Vector2{ 1.0f, 0.0f }},   // bottom right
        Vertex{Vector3{-0.5f, -0.5f, 0.0f},  Color::blue,    Vector2{ 0.0f, 0.0f }},   // bottom left
        Vertex{Vector3{-0.5f,  0.5f, 0.0f},  Color::yellow,  Vector2{ 0.0f, 1.0f }},    // top left
        Vertex{Vector3{ 0.5f,  0.5f, 0.0f},  Color::red,     Vector2{ 1.0f, 1.0f }},   // top right
        Vertex{Vector3{-0.5f, -0.5f, 0.0f},  Color::blue,    Vector2{ 0.0f, 0.0f }},   // bottom left
    };

    Mesh mesh3{ vertices3, size(vertices3) };

    Shader vertexShader{ "vertexShader.glsl", GL_VERTEX_SHADER };

    Shader orangeShader{
        "orangeFragmentShader.glsl", GL_FRAGMENT_SHADER
    };

    Shader yellowShader{
        "orangeFragmentShader.glsl", GL_FRAGMENT_SHADER
    };

    Shader textureShader{
        "TextureFragmentShader.glsl", GL_FRAGMENT_SHADER
    };


    // -------- Create Orange Shader Program (Render Pipeline) ---------
    Material orange{ vertexShader, orangeShader };
    Material yellow{ vertexShader, yellowShader };
    Material textured{ vertexShader, textureShader };

    Triangle a{ &orange, &mesh1 };
    a.red = 1;
    Triangle b{ &orange, &mesh2 };
    b.red = 0.5f;

    Triangle c{ &textured, &mesh3, &container };

    c.offsetX =  0.5f;

    Triangle d{ &textured, &mesh3, &wall};

    d.offsetX = -0.5f;

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    // While the User doesn't want to Quit (X Button, Alt+F4)
    while (!window.shouldClose()) // window -> window.window
    {
        window.processInput();

        window.clear();

        a.render();
        b.render();

        //c.horizontalOffset = cos(glfwGetTime());

        c.render();

        d.render();

        window.present();
    }
    // Cleans up all the GLFW stuff
    glfwTerminate();
    return 0;
}

