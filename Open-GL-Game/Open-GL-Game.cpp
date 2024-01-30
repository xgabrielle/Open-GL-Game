
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Triangle.h"
using namespace std;

void processInput(GLFWwindow*);

int main() {

    Window window{ 800,600 };
    
    Vertex vertices[]{
            Vertex{Vector3{-1.0f,-0.5f, 0.0f}},
            Vertex{Vector3{ 0.0f,-0.5f, 0.0f}},
            Vertex{Vector3{-0.5f, 0.5f, 0.0f}}

            
    };
    Mesh mesh1{vertices, size(vertices)};
   
    Vertex vertices2[]{
        Vertex{Vector3{0.0f,-0.5f, 0.0f},Color::red},
        Vertex{Vector3{1.0f,-0.5f, 0.0f},Color::blue},
        Vertex{Vector3{0.5f, 0.5f, 0.0f},Color::green} 
    };

    Mesh mesh2{ vertices2, size(vertices2) };

    Vertex vertices3[]{
        Vertex{Vector3{ 0.5f, 0.5f, 0.0f}},
        Vertex{Vector3{-0.5f, 0.5f, 0.0f}},
        Vertex{Vector3{ 0.0f,-0.5f, 0.0f}}
    };

    Mesh mesh3{ vertices3, size(vertices3) };

    Shader vertexShader{ "vertexShader.glsl", GL_VERTEX_SHADER };

    Shader orangeShader{ "OrangeFragmentShader.glsl", GL_FRAGMENT_SHADER};

    Shader yellowShader{"OrangeFragmentShader.glsl", GL_FRAGMENT_SHADER };

    Shader blueShader{ "OrangeFragmentShader.glsl", GL_FRAGMENT_SHADER };
  
    Material orange{vertexShader, orangeShader};
    Material yellow{ vertexShader, yellowShader };
    Material blue{ vertexShader, blueShader };

    Triangle a{ &orange, &mesh1 };
    a.red = 1;
    Triangle b{ &yellow, &mesh2 };
    b.green = 1;
    Triangle c{ &blue, &mesh3 };
    c.blue = 1;

    while (!window.shouldClose())
    {
        
        window.processInput();
        window.clear();

        a.render();
        b.render();
        c.render();

        window.present();
    }

    glfwTerminate();
    return 0;

    
}

