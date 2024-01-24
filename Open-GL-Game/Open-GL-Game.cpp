
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


using namespace std;

void processInput(GLFWwindow*);

// put before int main(){
//}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void error_callback(int error, const char* msg) {
    cerr << " [" << error << "] " << msg << endl;
}

int main() 
{

    glfwSetErrorCallback(error_callback);

    // Initialize GLFW
    if (!glfwInit()) { // Exit, if it failed
        cout << "Failed to init GLFW" << endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Requesting Window from Operating System
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Initialize GLAD (connects OpenGL Functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        glfwTerminate(); // added
        return -1;
    }
    // add just before glViewport:
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // replace glViewport(0, 0, 800, 600); with this:
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // ==================================================================================
    
    float red = 0;

    // Create Vertex Array Object which makes changing between VBO easier
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // ------ Create Array Buffer on the GPU and copy our vertics on GPU
    float vertices[] = {
        -1.0f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };

    unsigned int VBO; // variable to store buffer id
    glGenBuffers(1, &VBO); // ask open gl to create a buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // tell gl to use this buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // copy our vertex to the buffer


    // configure the vertex attribute(s) (currently there's just one, position)
    // so the vertex shader understand where to find the input attributes, in this case, postion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Create Vertex Array Object which makes changing between VBO easier
    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    // ------ Create Array Buffer on the GPU and copy our vertics on GPU
    float vertices2[] = {
        0.0f, -0.5f, 0.0f,
        1.0f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
    };

    unsigned int VBO2; // variable to store buffer id
    glGenBuffers(1, &VBO2); // ask open gl to create a buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO2); // tell gl to use this buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW); // copy our vertex to the buffer


    // configure the vertex attribute(s) (currently there's just one, position)
    // so the vertex shader understand where to find the input attributes, in this case, postion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    const char* vertexShaderSource{ "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4 (aPos.x, aPos.y, aPos.x, 1.0f);\n"
        "}\0" };

    
    unsigned int vertexShader { glCreateShader(GL_VERTEX_SHADER) };
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    {
        int  success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    // Compile the Fragment Shader on the GPU
    const char* orangeFragmentShaderSource{ "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "} \0" };

    const char* newColorFragmentShaderSource{ "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(0.2f, 1.f, 0.2f, 1.0f);\n"
        "}\0" };

    unsigned int orangeFragmentShader;
    orangeFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(orangeFragmentShader, 1, &orangeFragmentShaderSource, NULL);
    glCompileShader(orangeFragmentShader);

    unsigned int newColorFragmentShader;
    newColorFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(newColorFragmentShader, 1, &newColorFragmentShaderSource, NULL);
    glCompileShader(newColorFragmentShader);

    {
        int  success;
        char infoLog[512];
        glGetShaderiv(orangeFragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(orangeFragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    // Create a Shader Program (Render Pipeline)
    unsigned int orangeShaderProgram { glCreateProgram() };
    glAttachShader(orangeShaderProgram, vertexShader);
    glAttachShader(orangeShaderProgram, orangeFragmentShader);
    glLinkProgram(orangeShaderProgram);

    {
        int  success;
        char infoLog[512];
        glGetProgramiv(orangeShaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(orangeShaderProgram, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }

    unsigned int newColorShaderProgram { glCreateProgram() };
    glAttachShader(newColorShaderProgram, vertexShader);
    glAttachShader(newColorShaderProgram, newColorFragmentShader);
    glLinkProgram(newColorShaderProgram);
    // Clean up shader after they've been linked into a program
    glDeleteShader(vertexShader);
    glDeleteShader(orangeFragmentShader);
    glDeleteShader(newColorFragmentShader);

    //While the User doesn't want to Quit (X Button,Alt+Fn)
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        processInput(window);
        red += 0.0001f;
        if (red > 1)
            red -= 1;
        // render (paint the current frame of the game)
        glClearColor(red, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(orangeShaderProgram);//extra
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(newColorShaderProgram);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // present, send the current frame the to the computer screen
        glfwSwapBuffers(window);
    }
    // Cleans up alla the GLFW stuff

    glfwTerminate();
    return 0;
}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}