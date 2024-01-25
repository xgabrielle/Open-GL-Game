
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
using namespace std;

void processInput(GLFWwindow*);



int main() {

    Window window{ 800,600 };

    // ==================================================================
    // The Real Program starts here
    float red{};
    float vertices[]{
             -1.0f, -0.5f, 0.0f,
              0.0f, -0.5f, 0.0f,
             -0.5f,  0.5f, 0.0f,
             -1.0f, -0.5f, 0.0f,
             -0.5f,  0.5f, 0.0f,
             -1.0f, 0.5f, 0.0f
    };
    Mesh mesh1{vertices, size(vertices)};
   
    // ----- Create Array Buffer on the GPU and copy our vertices to GPU -------
    float vertices2[]{
        0.0f, -0.5f, 0.0f,
        1.0f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f
    };

    Mesh mesh2{ vertices2, size(vertices2) };

    // ----- Compile the Vertex Shader on the GPU -------

  
    Shader vertexShader{ { "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0" }, GL_VERTEX_SHADER };

    Shader orangeShader{ { "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "} \0" }, GL_FRAGMENT_SHADER };

    Shader yellowShader{ { "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
        "} \0" }, GL_FRAGMENT_SHADER };



    // -------- Create Orange Shader Program (Render Pipeline) ---------
    unsigned int orangeShaderProgram;
    orangeShaderProgram = glCreateProgram();
    glAttachShader(orangeShaderProgram, vertexShader.shaderId);
    glAttachShader(orangeShaderProgram, orangeShader.shaderId);
    glLinkProgram(orangeShaderProgram);

    // -------- Create Yellow Shader Program (Render Pipeline) ---------
    unsigned int yellowShaderProgram;
    yellowShaderProgram = glCreateProgram();
    glAttachShader(yellowShaderProgram, vertexShader.shaderId);
    glAttachShader(yellowShaderProgram, yellowShader.shaderId);
    glLinkProgram(yellowShaderProgram);

    // clean up shaders after they've been linked into a program
    




    // While the User doesn't want to Quit (X Button, Alt+F4)
    while (!window.shouldClose())
    {
        // process input (e.g. close window on Esc)
        
       
        window.processInput();
        window.present();

        red += 0.0001f;
        if (red > 1)
            red -= 1;

        // render (paint the current frame of the game)
        glClearColor(red, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(orangeShaderProgram);
        mesh1.render();
        

        glUseProgram(yellowShaderProgram);
        mesh2.render();
        glDrawArrays(GL_TRIANGLES, 0, 3);

       
    }
    // Cleans up all the GLFW stuff
    glfwTerminate();
    return 0;

    
}

