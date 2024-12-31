#pragma once

#define FORMULA FORMULA_BURNING_SHIP
#define SET_TYPE SET_MANDELBROT
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

// for burning ship
#define FLIP_Y


#define SET_MANDELBROT R"(c = complex(x, y); z = complex(0, 0);)"
#define SET_JULIA R"(c = complex((mouseX-0.5)*2, (mouseY-0.5)*2); z = complex(x, y);)"


#define FORMULA_TEST R"(
	complex next(complex c, complex z){
		return _add(c, z);
	}
)"

#define FORMULA_REGULAR R"(    
complex next(complex c, complex z){
	return _add(_mul(z, z), c);
})"

#define FORMULA_BURNING_SHIP R"(
complex next(complex c, complex z){
	return _add(c, _pow(complex(abs(z.real), abs(z.imag)), 2));
})"

#define FORMULA_WATER_DROP R"(    
complex next(complex c, complex z){
	return _div(_exp(z), c);
})"


// DO NOT REMOVE 0*mandelbrot(c, z, MAX_ITER);
// it effects static variables (like steps)
#define COLORING_EDGES	R"(
float value = 0*mandelbrot(c, z, MAX_ITER);	
vec3 ret = vec3(
	float(steps)/100, 
	0, 
	0
);)"

#define COLORING_STRIPS	R"(
float value = mandelbrot(c, z, MAX_ITER);	
vec3 ret = vec3(
	gra1(value), 
	0, 
	value
); )"

#define COLORING_STRIPS_AND_EDGES R"(
float value = mandelbrot(c, z, MAX_ITER);
vec3 ret = vec3(
	float(steps) / 100, 
	0, 
	value
);)"

#define COLORING_TEST R"(
float value = mandelbrot(c, z, MAX_ITER);
vec3 ret;
if(steps == -1)
	ret = vec3(1, 1, 1);
else
	ret = vec3(0, 0, 0);
)"
