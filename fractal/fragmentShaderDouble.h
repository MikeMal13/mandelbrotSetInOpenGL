#pragma once


// Fragment Shader source code with calc function
const char* fragmentShaderSourceDouble = R"(
    #version 450 core

    in vec2 fragPos; // Received from vertex shader

    out vec4 FragColor;

    uniform float u_time; // Elapsed time in seconds
    uniform dvec2 u_cursorPos;
    uniform dvec4 u_windowSize;
    
    uniform double arr;

    double minX, maxX, minY, maxY;
    double mouseX, mouseY;

    struct complex {
		double real;
		double imag;
	};
    complex c, z;

	complex _add(complex a, complex b) {
		return complex(a.real + b.real, a.imag + b.imag);
	}

	complex _mul(complex a, complex b) {
		return complex(a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real);
	}

    complex _mul(complex a, float b) {
		return complex(a.real * b, a.imag * b);
	}

	float abs(complex a) {
		return sqrt(float(a.real * a.real + a.imag * a.imag));
	}
    
    complex pow(complex a, int n) {
		complex res = complex(1, 0);
		for (int i = 0; i < n; i++) {
			res = _mul(res, a);
		}
		return res;
	}

    complex next(complex c, complex z){
		return _add(_mul(z, z), c);
	}
    
    #define MAX_DIST 10.0
    #define MAX_ITER 100
    int steps = -1;
    float mandelbrot(complex c, complex z, int maxIter) {
		int n = 0;
        complex boundery = complex(MAX_DIST, MAX_DIST);
		while (n < maxIter && abs(z) < MAX_DIST) { //!outOfBound(z, boundery)) {
			z = next(c, z);
            n++;
		}
        steps = n;
        return abs(z) / (MAX_DIST*MAX_DIST);
    }
    
    void set_c_and_z(double x, double y){
        //c = complex((mouseX-0.5)*2, (mouseY-0.5)*2);
		//z = complex(x, y);
        c = complex(x, y);
		z = complex(0, 0);
    }

    float avg(complex c, complex z, int maxIter){
        return 1;    
    }


    float gra1(float val){
        return (exp(val)-1)/(exp(1));
    }
    
    vec3 calc(double x, double y, float t) {
        
        mouseX = float(u_cursorPos.x);
        mouseY = float(u_cursorPos.y);

        minX = u_windowSize.x;
        maxX = u_windowSize.y;
        minY = u_windowSize.z;
        maxY = u_windowSize.w;

        x = minX + (x*(maxX - minX));
        y = minY + (y*(maxY - minY));        
        
        set_c_and_z(x, y);
        
        float value = mandelbrot(c, z, MAX_ITER);
        float red = gra1(value) + steps / MAX_ITER;
        float green = 0;
        float blue = value;
        
        if(steps >= MAX_ITER)
           red = 0;
        
        return vec3(red, 0, blue);
    }

    void main()
    {
        // Compute color using the calc function
        vec3 color = calc(double(fragPos.x), double(fragPos.y), u_time);
        FragColor = vec4(color, 1.0);
    }
)";

