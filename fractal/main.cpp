// main.cpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <math.h>

#include "inits.h"
#include "vertexShader.h"
#include "fragmentShader.h"

typedef double big_float;


big_float windowSize[] = { -2.0f, 2.0f, -2.0f, 2.0f };
big_float currentTime;
big_float deltaTime;

// mul is portsion of the window size moved every second
void shiftWindowX(big_float mul) {
    big_float range_x = windowSize[3] - windowSize[2];
    mul *= range_x * deltaTime;
    windowSize[0] += mul;
    windowSize[1] += mul;
}

// mul is portsion of the window size moved every second
void shiftWindowY(big_float mul) {
    big_float range_y = windowSize[1] - windowSize[0];
    mul *= range_y * deltaTime;
    windowSize[2] += mul;
    windowSize[3] += mul;
}

void scaleX(big_float mul) {
    big_float range_x = windowSize[3] - windowSize[2];
    big_float newRange = range_x * mul;
    big_float dx = (range_x - newRange) / 2;
    windowSize[3] -= dx;
    windowSize[2] += dx;
}

// mul is multiplier of the window size every second
void scaleY(big_float mul) {
	big_float range_y = windowSize[1] - windowSize[0];
    big_float newRange = range_y * mul;
	big_float dy = (range_y-newRange)/2;
	windowSize[1] -= dy;
	windowSize[0] += dy;
}

// mul is multiplier of the window size every second
void zoomWindow(big_float mul) {
    // power of deltaTime to make zooming smooth
    scaleX(pow(mul, deltaTime)); 
    scaleY(pow(mul, deltaTime));
}

void fitWindow() {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    std::swap(width, height);

    big_float range_x = windowSize[3] - windowSize[2];
    big_float range_y = windowSize[1] - windowSize[0];

    scaleY((height * range_x) / (width * range_y));
}

bool mousePosLocked = false;
void handleKeyPresses() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        shiftWindowY(-1.0); 
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        shiftWindowY(1.0);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        shiftWindowX(-1.0);
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        shiftWindowX(1.0);
    }
       
    // zoom in
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        zoomWindow(0.25);
    }

    // zoom out
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        zoomWindow(4);
    }

    //lock mouse position
    if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		mousePosLocked = true;
	}

	//unlock mouse position
	if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		mousePosLocked = false;
	}
}


struct cord {
    big_float x;
    big_float y;
};

big_float xpos, ypos;
cord getMousePos() {
    if(!mousePosLocked) 
        glfwGetCursorPos(window, &xpos, &ypos);

    // Get window size
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // Normalize cursor position
    big_float normalizedX = xpos / width;
    big_float normalizedY = 1.0f - (ypos / height); // Flip Y-axis

    return { normalizedX, normalizedY };
}

double getElapsedTime() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = currentTime - startTime;
    double t = elapsed.count();
    return t;
}

int main()
{
    doStaff();


    int timeLocation = glGetUniformLocation(shaderProgram, "u_time");
    int windowSizeLocation = glGetUniformLocation(shaderProgram, "u_windowSize");
    int mouseLocation = glGetUniformLocation(shaderProgram, "u_cursorPos");
    if (timeLocation == -1 || windowSizeLocation == -1 || mouseLocation == -1) {
        std::cout << "Error getting uniform locations\n";
        std::cout << "timeLocation: " << timeLocation 
                  << ", windowSizeLocation: " << windowSizeLocation
                  << ", mouseLocation: " << mouseLocation << "\n";
        exit(1);
    }

    double lastTime = getElapsedTime();
    while (!glfwWindowShouldClose(window)) {

        // print fps every second
        static double ___timeAtLastCall = -1;
        if (currentTime - ___timeAtLastCall > 1) {
            std::cout << "fps: "  << 1 / deltaTime << "\n";
            ___timeAtLastCall = currentTime;
        } 

        
        fitWindow();
        currentTime = getElapsedTime();
        deltaTime = currentTime - lastTime;

        handleKeyPresses();

        glUseProgram(shaderProgram);

        cord mouseCord = getMousePos();

        glUniform2d(mouseLocation, mouseCord.x, mouseCord.y);
        glUniform1f(timeLocation, currentTime);
        glUniform4dv(windowSizeLocation, 1, windowSize);

        // Rendering commands here
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Clear with dark gray color
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the rectangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6); // Draw 6 vertices forming 2 triangles


        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();

        lastTime = currentTime;
    }


    // 10. Clean up resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // 11. Terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
