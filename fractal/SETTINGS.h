#pragma once

#define SET_TYPE SET_JULIA
#define COLORING_SELECTED COLORING_STRIPS

//#define USE_DOUBLE
#define USE_FLOAT
#define MAX_ITER R"(10000)"
#define MAX_DIST R"(10.0)"



#define SET_MANDELBROT R"(c = complex(x, y); z = complex(0, 0);)"
#define SET_JULIA R"(c = complex((mouseX-0.5)*2, (mouseY-0.5)*2); z = complex(x, y);)"

// DO NOT REMOVE 0*mandelbrot(c, z, MAX_ITER);
// it effects static variables (like steps)
#define COLORING_EDGES							\
R"(float value = 0*mandelbrot(c, z, MAX_ITER);			\
float red = float(steps) / 100;					\
float green = 0;										\
float blue = value;)"

#define COLORING_STRIPS									\
R"(float value = mandelbrot(c, z, MAX_ITER);			\
float red = gra1(value);								\
float green = 0;										\
float blue = value;)"

#define COLORING_STRIPS_AND_EDGES						\
R"(float value = mandelbrot(c, z, MAX_ITER);			\
float red = float(steps) / MAX_ITER;								\
float green = 0;										\
float blue = value;)"