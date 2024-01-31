
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Triangle.h"
#include "stb_image.h"
using namespace std;

void processInput(GLFWwindow*);

int main() {

    Window window{ 800,600 };

    int width, height, nrChannels;
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
   

    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    Vertex vertices[]
    {
            Vertex{Vector3{-1.0f,-0.5f, 0.0f}},
            Vertex{Vector3{ 0.0f,-0.5f, 0.0f}},
            Vertex{Vector3{-0.5f, 0.5f, 0.0f}}

            
    };
    Mesh mesh1{vertices, size(vertices)};
   
    Vertex vertices2[]
    {
        Vertex{Vector3{0.0f,-0.5f, 0.0f}},
        Vertex{Vector3{1.0f,-0.5f, 0.0f}},
        Vertex{Vector3{0.5f, 0.5f, 0.0f}} 
    };

    Mesh mesh2{ vertices2, size(vertices2) };

    Vertex vertices3[]
    {
        Vertex{Vector3{ 0.5f, 0.5f, 0.0f},Color:: red},
        Vertex{Vector3{-0.5f, 0.5f, 0.0f},Color::blue},
        Vertex{Vector3{ 0.0f,-0.5f, 0.0f}, Color::green}
    };

    Mesh mesh3{ vertices3, size(vertices3) };

    Vertex vertices4[]
    {
        // positions          // colors           // texture coords
        Vertex{Vector3{ 0.5f,  0.5f, 0.0f}, Color :: red,    Vector2{  1.0f, 1.0f}},   // top right
        Vertex{Vector3{ 0.5f, -0.5f, 0.0f}, Color :: blue,   Vector2{  1.0f, 0.0f}},   // bottom right
        Vertex{Vector3{-0.5f, -0.5f, 0.0f}, Color :: green,  Vector2{  0.0f, 0.0f}},   // bottom left
        Vertex{Vector3{-0.5f,  0.5f, 0.0f}, Color :: yellow, Vector2{  0.0f, 1.0f}}    // top left 
    };
    Mesh mesh4{ vertices4, size(vertices4) };


    Shader vertexShader{ "vertexShader.glsl", GL_VERTEX_SHADER };

    Shader orangeShader{ "OrangeFragmentShader.glsl", GL_FRAGMENT_SHADER};

    Shader yellowShader{"OrangeFragmentShader.glsl", GL_FRAGMENT_SHADER };

    Shader blueShader{ "OrangeFragmentShader.glsl", GL_FRAGMENT_SHADER };

    Shader textureShader{ "TextureFragmentShader.glsl", GL_FRAGMENT_SHADER };
  
    Material orange{vertexShader, orangeShader};
    Material yellow{ vertexShader, yellowShader };
    Material blue{ vertexShader, blueShader };
    Material textured{ vertexShader, textureShader };

    Triangle a{ &orange, &mesh1 };
    a.red = 1;
    a.offsetX = 0.2;
    Triangle b{ &yellow, &mesh2 };
    b.green = 1;
    b.offsetX;
    Triangle c{ &blue, &mesh3 };
    c.blue = 1;
    Triangle d{ &textured, &mesh4 };

    while (!window.shouldClose())
    {
        
        window.processInput();
        window.clear();

        a.render();
        b.render();
        c.render();
        d.render();

        window.present();
    }

    glfwTerminate();
    return 0;

    
}

