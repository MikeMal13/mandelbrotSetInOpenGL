#pragma once

// Vertex Shader source code
const char* vertexShaderSource = R"(
    #version 450 core
    layout (location = 0) in vec3 aPos;    // Vertex position

    out vec2 fragPos; // Pass normalized coordinates to fragment shader

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
        // Convert from range [-1, 1] to [0, 1] for normalized coordinates
        fragPos = aPos.xy * 0.5 + 0.5;
    }
)";