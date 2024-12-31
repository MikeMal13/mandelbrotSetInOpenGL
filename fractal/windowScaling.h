#pragma once

#include "inits.h"
#include "SETTINGS.h"


void shiftWindowX(big_float mul);
void shiftWindowY(big_float mul);
void scaleX(big_float mul);
void scaleY(big_float mul);
void zoomWindow(big_float mul);
void zoomMouseWindow(big_float mul);
cord fitCordToMouseWindow(cord c);
void fitWindow();
cord convertToWindowCord(cord mouseCord);
cord getMousePos();
cord getMousePosWithLock();





// mul is portsion of the window size moved every second
void shiftWindowX(big_float mul) {
    big_float range_x = windowSize[3] - windowSize[2];
    mul *= range_x * deltaTime;
    windowSize[0] += mul;
    windowSize[1] += mul;
}

// mul is portsion of the window size moved every second
void shiftWindowY(big_float mul) {
#ifdef FLIP_Y
    mul *= -1;
#endif


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
    big_float dy = (range_y - newRange) / 2;
    windowSize[1] -= dy;
    windowSize[0] += dy;
}



// mul is multiplier of the window size every second
void zoomWindow(big_float mul) {
    // power of deltaTime to make zooming smooth
    scaleX(pow(mul, deltaTime));
    scaleY(pow(mul, deltaTime));
}

void zoomMouseWindow(big_float mul) {
    cord mousePos = getMousePos();
    mul = pow(mul, deltaTime);

    cord finalPos = fitCordToMouseWindow(mousePos);

    big_float range_x = mouseWindow[1] - mouseWindow[0];
    big_float range_y = mouseWindow[3] - mouseWindow[2];
    big_float newRange_x = range_x * mul;
    big_float newRange_y = range_y * mul;

    big_float sx = range_x - newRange_x;
    big_float sy = range_y - newRange_y;

    mouseWindow[0] += sx * mousePos.x;
    mouseWindow[1] -= sx * (1 - mousePos.x);
    mouseWindow[2] += sy * mousePos.y;
    mouseWindow[3] -= sy * (1 - mousePos.y);

    //std::cout << "mul: " << mul << ", range_x: " << range_x << ", range_y: " << range_y << "\n";
    printf("mouseWindow: %f, %f, %f, %f\n", mouseWindow[0], mouseWindow[1], mouseWindow[2], mouseWindow[3]);
}


cord fitCordToMouseWindow(cord c) {
    return {
         mouseWindow[0] + (c.x * (mouseWindow[1] - mouseWindow[0])),
         mouseWindow[2] + (c.y * (mouseWindow[3] - mouseWindow[2]))
    };
}

void fitWindow() {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    std::swap(width, height);

    big_float range_x = windowSize[3] - windowSize[2];
    big_float range_y = windowSize[1] - windowSize[0];

    scaleY((height * range_x) / (width * range_y));
}



cord convertToWindowCord(cord mouseCord) {
    big_float range_x = windowSize[3] - windowSize[2];
    big_float range_y = windowSize[1] - windowSize[0];

    big_float x = windowSize[2] + range_x * mouseCord.x;
    big_float y = windowSize[0] + range_y * mouseCord.y;

    return { x, y };
}



double xpos, ypos;
cord getMousePos() {
    glfwGetCursorPos(window, &xpos, &ypos);

    // Get window size
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // Normalize cursor position
    big_float normalizedX = xpos / width;
    big_float normalizedY = 1.0f - (ypos / height); // Flip Y-axis

    return { normalizedX, normalizedY };
}

cord lastCord;
cord getMousePosWithLock() {
    if (!mousePosLocked)
        lastCord = getMousePos();

    return lastCord;
}