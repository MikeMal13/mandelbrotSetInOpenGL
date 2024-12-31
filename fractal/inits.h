#pragma once
#include "vertexShader.h"
#include "SETTINGS.h"
#include "fragmentShader.h";


#ifdef USE_FLOAT
typedef float big_float;
#elif defined USE_DOUBLE
typedef double big_float;
#endif

struct cord {
    big_float x;
    big_float y;
};

big_float windowSize[4] = WINDOW_STARTING_CORDS;
big_float mouseWindow[4] = MOUSE_STARTING_CORDS;
big_float currentTime;
big_float deltaTime;
cord mouseCordIncludingLock;
bool mousePosLocked = false;





void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


GLFWwindow* window;

unsigned int vertexShader;
unsigned int fragmentShader;

int success;
char infoLog[512];

unsigned int shaderProgram;
unsigned int VBO, VAO;

auto startTime = std::chrono::high_resolution_clock::now();

void doStaff() {

    // 1. Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        exit(-1);
    }

    // 2. Configure GLFW: OpenGL version 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Uncomment the following line for MacOS compatibility
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // 3. Create a GLFW window
    window = glfwCreateWindow(SCREEN_DEFAULT_WIDTH, SCREEN_DEFAULT_HEIGHT, "OpenGL Dynamic Gradient", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    // 4. Initialize GLAD before calling any OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        exit(-1);
    }

    // 5. Set the viewport and register the resize callback
    glViewport(0, 0, SCREEN_DEFAULT_WIDTH, SCREEN_DEFAULT_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 6. Build and compile the shader program

    // a. Vertex Shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for vertex shader compile errors
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
    }

    // b. Fragment Shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(fragmentShader);

    // Check for fragment shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << "\n";
    }

    // c. Shader Program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
    }

    // d. Delete the shader objects once we've linked them into the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 7. Set up vertex data and buffers and configure vertex attributes

    // Rectangle covering the entire screen using two triangles
    float vertices[] = {
        // Positions          
        // First triangle
        -1.0f,  1.0f, 0.0f, // Top-left
        -1.0f, -1.0f, 0.0f, // Bottom-left
         1.0f, -1.0f, 0.0f, // Bottom-right

         // Second triangle
         -1.0f,  1.0f, 0.0f, // Top-left
          1.0f, -1.0f, 0.0f, // Bottom-right
          1.0f,  1.0f, 0.0f  // Top-right
    };


    glGenVertexArrays(1, &VAO); // Generate a VAO
    glGenBuffers(1, &VBO);      // Generate a VBO

    // Bind the Vertex Array Object first, then bind and set vertex buffers, and then configure vertex attributes.
    glBindVertexArray(VAO);

    // Bind the VBO buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Copy the vertices data into the buffer's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // No color attributes needed as colors are computed in the fragment shader

    // You can unbind the VAO and VBO to prevent accidental modification
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 8. Time Tracking Setup
    // Use high-resolution clock to measure elapsed time
    startTime = std::chrono::high_resolution_clock::now();
    
    // Use the shader program once to set initial uniforms
    glUseProgram(shaderProgram);
}