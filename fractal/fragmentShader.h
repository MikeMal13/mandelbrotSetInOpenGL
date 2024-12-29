#pragma once
#include "SETTINGS.h"
#include "complexMathFunctions.h"

// Fragment Shader source code with calc function
const char* fragmentShaderSource = R"(
    #version 450 core
)"
#ifdef USE_FLOAT
R"( #define calc_type float
    #define calc_type_vec2 vec2
    #define calc_type_vec3 vec3
    #define calc_type_vec4 vec4  )"
#elif defined USE_DOUBLE 
R"( #define calc_type double
    #define calc_type_vec2 dvec2
    #define calc_type_vec3 dvec3
    #define calc_type_vec4 dvec4 )"
#endif
R"(
    struct complex {
		calc_type real;
		calc_type imag;
	};

    in vec2 fragPos; // Received from vertex shader

    out vec4 FragColor;

    uniform float u_time; // Elapsed time in seconds
    uniform calc_type_vec2 u_cursorPos;
    uniform calc_type_vec4 u_windowSize;
        
    uniform calc_type arr;
    
    )" COMPLEX_MATH_FUNCTION_SIGNITRE R"(


    complex c, z;
    calc_type minX, maxX, minY, maxY;
    calc_type mouseX, mouseY;



    // All of the math functions for complex numbers
    // (add, mul, pow, exp)
	)" COMPLEX_MATH_FUNCTION_ALL R"(

    // the pre defined function is: 
    // complex next(complex c, complex z);
    // it calculates the next number f(z) -> z
    )"  FORMULA  R"(
    
    #define MAX_DIST )" MAX_DIST R"(
    #define MAX_ITER )" MAX_ITER R"(

    int steps = -1;
    float mandelbrot(complex c, complex z, int maxIter) {
		int n = 0;
        complex boundery = complex(MAX_DIST, MAX_DIST);
		while (n < maxIter && _abs(z) < MAX_DIST) {
			z = next(c, z);
            n++;
		}
        steps = n;
        if(steps >= MAX_ITER)
           steps = 0;
        return _abs(z) / (MAX_DIST*MAX_DIST);

    }
    
    void set_c_and_z(calc_type x, calc_type y){ )" SET_TYPE R"(}

    float gra1(float val){
        return (exp(val)-1)/(exp(1));
    }
    
    vec3 calc(calc_type x, calc_type y, calc_type t) {
        
        mouseX = u_cursorPos.x;
        mouseY = u_cursorPos.y;

        minX = u_windowSize.x;
        maxX = u_windowSize.y;
        minY = u_windowSize.z;
        maxY = u_windowSize.w;

        x = minX + (x*(maxX - minX));
        y = minY + (y*(maxY - minY));        
        
        set_c_and_z(x, y);  
        )" COLORING_SELECTED R"( 
        
        return vec3(red, 0, blue);
    }

    void main()
    {
        // Compute color using the calc function
        vec3 color = calc(calc_type(fragPos.x), calc_type(fragPos.y), u_time);
        FragColor = vec4(color, 1.0);
    }
)";

