
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"

using namespace std;

void processInput(GLFWwindow*);



int main() {

    Window window{ 800,600 };

    // ==================================================================
    // The Real Program starts here
    float red{};

    // ----- Create Vertex Array Object, which makes changing between VBOs easier -----
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // ----- Create Array Buffer on the GPU and copy our vertices to GPU -------
    float vertices[]{
       -1.0f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
       -0.5f,  0.5f, 0.0f
    };
    unsigned int VBO; // variable to store buffer id
    glGenBuffers(1, &VBO); // ask open gl to create a buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // tell gl to use this buffer
    glBufferData(GL_ARRAY_BUFFER, // copy our vertices to the buffer
        sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ------ configure vertex attribute(s) (currently it's just one, the position) -----
    // so the vertex shader understands, where to find the input attributes, in this case position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // ----- Create Vertex Array Object, which makes changing between VBOs easier -----
    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    // ----- Create Array Buffer on the GPU and copy our vertices to GPU -------
    float vertices2[]{
        0.0f, -0.5f, 0.0f,
        1.0f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f
    };
    unsigned int VBO2; // variable to store buffer id
    glGenBuffers(1, &VBO2); // ask open gl to create a buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO2); // tell gl to use this buffer
    glBufferData(GL_ARRAY_BUFFER, // copy our vertices to the buffer
        sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    // ------ configure vertex attribute(s) (currently it's just one, the position) -----
    // so the vertex shader understands, where to find the input attributes, in this case position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ----- Compile the Vertex Shader on the GPU -------

    const char* vertexShaderSource{ "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0" };
    unsigned int vertexShader{ glCreateShader(GL_VERTEX_SHADER) };
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // ------ Compile the Orange Fragment Shader on the GPU --------
    const char* orangeFragmentShaderSource{ "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "} \0" };
    unsigned int orangeFragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
    glShaderSource(orangeFragmentShader, 1, &orangeFragmentShaderSource, nullptr);
    glCompileShader(orangeFragmentShader);

    // ------ Compile the Yellow Fragment Shader on the GPU --------
    const char* yellowFragmentShaderSource{ "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
        "} \0" };
    unsigned int yellowFragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
    glShaderSource(yellowFragmentShader, 1, &yellowFragmentShaderSource, nullptr);
    glCompileShader(yellowFragmentShader);

    // -------- Create Orange Shader Program (Render Pipeline) ---------
    unsigned int orangeShaderProgram;
    orangeShaderProgram = glCreateProgram();
    glAttachShader(orangeShaderProgram, vertexShader);
    glAttachShader(orangeShaderProgram, orangeFragmentShader);
    glLinkProgram(orangeShaderProgram);

    // -------- Create Yellow Shader Program (Render Pipeline) ---------
    unsigned int yellowShaderProgram;
    yellowShaderProgram = glCreateProgram();
    glAttachShader(yellowShaderProgram, vertexShader);
    glAttachShader(yellowShaderProgram, yellowFragmentShader);
    glLinkProgram(yellowShaderProgram);

    // clean up shaders after they've been linked into a program
    glDeleteShader(vertexShader);
    glDeleteShader(orangeFragmentShader);
    glDeleteShader(yellowFragmentShader);



    // While the User doesn't want to Quit (X Button, Alt+F4)
    while (!glfwWindowShouldClose(window.window))
    {
        // process input (e.g. close window on Esc)
        glfwPollEvents();
        processInput(window.window);
        red += 0.0001f;
        if (red > 1)
            red -= 1;

        // render (paint the current frame of the game)
        glClearColor(red, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(orangeShaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(yellowShaderProgram);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // present (send the current frame to the computer screen)
        glfwSwapBuffers(window.window); // ??
    }
    // Cleans up all the GLFW stuff
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}