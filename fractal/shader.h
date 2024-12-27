//#pragma once
//
//vec3 calc(float x, float y) {
//    // Example: Radial gradient based on distance from center
//    float dist = length(vec2(x - 0.5, y - 0.5)) * 2.0;
//    return mix(vec3(1.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0), dist); // Red to Blue
//}
//
//
//const char* fragmentShaderSource = R"(
//    #version 330 core
//    in vec2 fragPos; // Received from vertex shader
//
//    out vec4 FragColor;
//
//    // Define the calc function
//    vec3 calc(float x, float y) {
//        // Example: Radial gradient based on distance from center
//        float dist = length(vec2(x - 0.5, y - 0.5)) * 2.0;
//        return mix(vec3(1.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0), dist); // Red to Blue
//    }
//
//    void main()
//    {
//        // Compute color using the calc function
//        vec3 color = calc(fragPos.x, fragPos.y);
//        FragColor = vec4(color, 1.0);
//    }
//)";