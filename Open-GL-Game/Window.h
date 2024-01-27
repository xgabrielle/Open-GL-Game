#pragma once

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"


using namespace std;

class Window
{
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    static void error_callback(int error, const char* msg) {
        cerr << " [" << error << "] " << msg << endl;
    }

public:
    
    GLFWwindow* window;
    bool success{};

    Window(int width, int height) {
        glfwSetErrorCallback(error_callback);

        
        if (!glfwInit()) 
        {
            cout << "Failed to init GLFW" << endl;
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(800, 600,
            "LearnOpenGL", nullptr, nullptr);

        if (window == nullptr)
        {
            cout << "Failed to create GLFW window" << endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            cout << "Failed to initialize GLAD" << endl;
            glfwTerminate();
            return;
        }
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        success = true;
    }
    bool shouldClose()
    {
        return glfwWindowShouldClose(this->window);
    }

    void  present()
    {
        glfwSwapBuffers(this->window);
    }
    void processInput()
    {
        glfwPollEvents();
        if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
    void clear()
    {
        glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
};

