// main.cpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <math.h>

#include "inits.h"
#include "vertexShader.h"
#include "fragmentShader.h"
#include "SETTINGS.h"
#include "windowScaling.h";

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)

void printDataToUpload();
void inputUploadData();

big_float power2(big_float x) {
	return x * x;
}

big_float dist(cord a, cord b) {
    return sqrt(power2(a.x - b.x) + power2(a.y - b.y));
}


void handleKeyPresses() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        shiftWindowY(-WINDOW_SHIFT_SPEED);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        shiftWindowY(WINDOW_SHIFT_SPEED);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        shiftWindowX(-WINDOW_SHIFT_SPEED);
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        shiftWindowX(WINDOW_SHIFT_SPEED);
    }
       
    // zoom in
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        zoomWindow(1/WINDOW_ZOOM_SPEED);
    }

    // zoom out
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        zoomWindow(WINDOW_ZOOM_SPEED);
    }

    // zoom mouse window in
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        zoomMouseWindow(0.2);
    }
    
    // zoom mouse window out
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        zoomMouseWindow(5);
    }
    
    //lock mouse position
    if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		mousePosLocked = true;
	}
        
	//unlock mouse position
	if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		mousePosLocked = false;
	}

    // reset window size
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		windowSize[0] = -2.0f;
		windowSize[1] = 2.0f;
		windowSize[2] = -2.0f;
		windowSize[3] = 2.0f;
        fitWindow();
	}


    // SAVE window size and mouse location
    if (glfwGetKey(window, GLFW_KEY_S)&&
        (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)) {
        std::cout << "\n\nCOPY the following data and paste it after pressing CTRL+U on the next run\n";
        std::cout << "keep in mind when switching from double to float the accuracy is much lower.\n";
        printDataToUpload();
        std::cout << "\n";
    }


    // UPLOAD window size and mouse location
    if (glfwGetKey(window, GLFW_KEY_U) &&
        (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)) {
        std::cout << "\n\nPASTE coped data (after CTRL+S)\n";
        inputUploadData();
        std::cout << "\n";
    }
}

void printDataToUpload() {
    #define big_float_size char
#ifdef USE_FLOAT
    #define big_float_size unsigned int 
    std::cout << "F ";
#elif defined USE_DOUBLE
    #define big_float_size unsigned long long 
    std::cout << "D ";
#endif
    std::cout << *((big_float_size*) &windowSize[0]) << " ";
    std::cout << *((big_float_size*) &windowSize[1]) << " ";
    std::cout << *((big_float_size*) &windowSize[2]) << " ";
    std::cout << *((big_float_size*) &windowSize[3]) << " ";
    std::cout << *((big_float_size*) &mouseCordIncludingLock.x) << " ";
    std::cout << *((big_float_size*) &mouseCordIncludingLock.y) << " ";
}

void inputUploadData() {
    mousePosLocked = true;

    char oldType;
    std::cin >> oldType;
    if(oldType == 'F') {
        unsigned int temp_arr[4], temp_mouse_x, temp_mouse_y;
        float temp_arr2[4], temp_mouse_x2, temp_mouse_y2;
        std::cin >> temp_arr[0] >> temp_arr[1] >> temp_arr[2] >> temp_arr[3] >> temp_mouse_x >> temp_mouse_y;
        
        temp_arr2[0] = *((big_float*)&temp_arr[0]);
        temp_arr2[1] = *((big_float*)&temp_arr[1]);
        temp_arr2[2] = *((big_float*)&temp_arr[2]);
        temp_arr2[3] = *((big_float*)&temp_arr[3]);
        temp_mouse_x2 = *((big_float*)&temp_mouse_x);
        temp_mouse_y2 = *((big_float*)&temp_mouse_y);
        
        windowSize[0] = temp_arr2[0];
        windowSize[1] = temp_arr2[1];
        windowSize[2] = temp_arr2[2];
		windowSize[3] = temp_arr2[3];
		mouseCordIncludingLock.x = temp_mouse_x2;
		mouseCordIncludingLock.y = temp_mouse_y2;
    } else if (oldType == 'D') {
        unsigned long long temp_arr[4], temp_mouse_x, temp_mouse_y;
        double temp_arr2[4], temp_mouse_x2, temp_mouse_y2;
        std::cin >> temp_arr[0] >> temp_arr[1] >> temp_arr[2] >> temp_arr[3] >> temp_mouse_x >> temp_mouse_y;
        
        temp_arr2[0] = *((big_float*)&temp_arr[0]);
        temp_arr2[1] = *((big_float*)&temp_arr[1]);
        temp_arr2[2] = *((big_float*)&temp_arr[2]);
        temp_arr2[3] = *((big_float*)&temp_arr[3]);
        temp_mouse_x2 = *((big_float*)&temp_mouse_x);
        temp_mouse_y2 = *((big_float*)&temp_mouse_y);

        windowSize[0] = temp_arr2[0];
		windowSize[1] = temp_arr2[1];
		windowSize[2] = temp_arr2[2];
        windowSize[3] = temp_arr2[3];
		mouseCordIncludingLock.x = temp_mouse_x2;
        mouseCordIncludingLock.y = temp_mouse_y2;
    }                              
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

        fitWindow();
        currentTime = getElapsedTime();
        deltaTime = currentTime - lastTime;
        
        // print fps every second
        static double ___timeAtLastCall = -1;
        if (currentTime - ___timeAtLastCall > 1) {
            printf("fps: %f\n", 1 / deltaTime);
            ___timeAtLastCall = currentTime;
        }


        handleKeyPresses();
        cord fitMouseCord = fitCordToMouseWindow(getMousePosWithLock());
        

        glUseProgram(shaderProgram);
        #ifdef USE_FLOAT
            glUniform2f(mouseLocation, fitMouseCord.x, fitMouseCord.y);
            glUniform4fv(windowSizeLocation, 1, windowSize);
        #elif defined USE_DOUBLE
			glUniform2d(mouseLocation, fitMouseCord.x, fitMouseCord.y);
			glUniform4dv(windowSizeLocation, 1, windowSize);
        #endif
        glUniform1f(timeLocation, currentTime);

        
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
