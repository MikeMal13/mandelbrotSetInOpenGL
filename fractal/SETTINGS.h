#pragma once

#define FORMULA FORMULA_EXP
#define SET_TYPE SET_JULIA
#define COLORING_SELECTED COLORING_STRIPS_AND_EDGES

// SELECT ONE (USE_FLOAT or USE_DOUBLE)
#define USE_FLOAT
//#define USE_DOUBLE

#define MAX_ITER R"(1000)"
#define MAX_DIST R"(10.0)"

#define WINDOW_SHIFT_SPEED 1.0
#define WINDOW_ZOOM_SPEED 4.0

#define SCREEN_DEFAULT_WIDTH 800
#define SCREEN_DEFAULT_HEIGHT 600
#define WINDOW_STARTING_CORDS { -2.0, 2.0, -2.0, 2.0 }
#define MOUSE_STARTING_CORDS { -1.0, 1.0, -1.0, 1.0 }


#define SET_MANDELBROT R"(c = complex(x, y); z = complex(0, 0);)"
#define SET_JULIA R"(c = complex((mouseX-0.5)*2, (mouseY-0.5)*2); z = complex(x, y);)"


#define FORMULA_REGULAR R"(    
complex next(complex c, complex z){
	return _add(_mul(z, z), c);
})"

#define FORMULA_EXP R"(    
complex next(complex c, complex z){
	return _add(_exp(z), c);
})"

#define FORMULA_EXP_DIV R"(    
complex next(complex c, complex z){
	return _div(_exp(z), c);
})"

#define FORMULA_SIN R"(
complex next(complex c, complex z){
	return _add(_sin(z), c);
})"

#define FORMULA_SIN_DIV R"(
complex next(complex c, complex z){
	return _div(_sin(z), c);
})"

#define FORMULA_EXP_SIN_DIV R"(
complex next(complex c, complex z){
	return _add(_sin(_exp(z)), c);
})"

// DO NOT REMOVE 0*mandelbrot(c, z, MAX_ITER);
// it effects static variables (like steps)
#define COLORING_EDGES	R"(
float value = 0*mandelbrot(c, z, MAX_ITER);			
float red = float(steps) / 100;					
float green = 0;										
float blue = value;)"

#define COLORING_STRIPS	R"(
float value = mandelbrot(c, z, MAX_ITER);			
float red = gra1(value);								
float green = 0;										
float blue = value;)"

#define COLORING_STRIPS_AND_EDGES R"(
float value = mandelbrot(c, z, MAX_ITER);			
float red = float(steps) / 100;								
float green = 10;										
float blue = value;)"