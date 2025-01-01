#pragma once
#include "doubleSupport.h"


//sin(z) = (e^(iz) - e^(-iz))/2i

#define COMPLEX_MATH_FUNCTION_SIGNITRE R"(
	complex _add(complex a, complex b);
	complex _add(complex a, calc_type b);
	complex _sub(complex a, complex b);
	complex _sub(complex a, calc_type b);
	complex _sub(calc_type a, complex b);
	complex _mul(complex a, complex b);
    complex _mul(complex a, calc_type b);
	complex _muli(complex z);
	float _abs(complex a);
    complex _pow(complex a, int n);
	complex _pow(complex a, complex b);
	complex _pow(complex a, calc_type b);
	complex _exp(complex a);
	complex _imagExp(calc_type b);
	complex _div(complex x, complex y);
	complex _div(complex z, calc_type a);
	complex _sin(complex z);
	complex _cos(complex z);

	#define PI 3.14159265359
)"

#define COMPLEX_MATH_FUNCTION_ALL DOUBLE_SUPPORT R"(
	float _exp(float a){
		return exp(a);
	}

	complex _add(complex a, complex b) {
		return complex(a.real + b.real, a.imag + b.imag);
	}

	complex _add(complex a, calc_type b) {
		return complex(a.real + b, a.imag + b);
	}

	complex _sub(complex a, complex b) {
		return complex(a.real - b.real, a.imag - b.imag);
	}

	complex _sub(complex a, calc_type b) {
		return complex(a.real - b, a.imag - b);
	}

	complex _sub(calc_type a, complex b) {
		return complex(a - b.real, a - b.imag);
	}

	complex _mul(complex a, complex b) {
		return complex(a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real);
	}

    complex _mul(complex a, calc_type b) {
		return complex(a.real * b, a.imag * b);
	}
	
	// z*i
	complex _muli(complex z) {
		return complex(-z.imag, z.real);
	}

	complex _div(complex z, calc_type a){
		return complex(z.real/a, z.imag/a);
	}
	
	// -z
	complex _neg(complex z){
		return complex(-z.real, -z.imag);
	}

	// (a+bi)/(c+di) = ((ac+bd)+i(cb-ad))/(cc+dd)
	complex _div(complex x, complex y) {
		calc_type top1 = (x.real * y.real) + (x.imag * y.imag);
		calc_type top2 = (y.real * x.imag) - (x.real * y.imag);
		calc_type bot = (y.real * y.real) + (y.imag * y.imag);
		return _div(complex(top1, top2), bot);
	}

	float _abs(complex a) {
		return sqrt(float(a.real * a.real + a.imag * a.imag));
	}
	
	// a^n
	// can be optimized for larger n
    complex _pow(complex a, int n) {
		complex res = complex(1, 0);
		for (int i = 0; i < n; i++) {
			res = _mul(res, a);
		}
		return res;
	}

	
	// (a+bi)^(c+di)
	complex _pow(complex a, complex b) {
		if(a.real == 0 && a.imag == 0){
			return complex(0, 0);
		}

		// convert to polar form
		calc_type r = _abs(a);
		calc_type theta = atan(a.imag / a.real);
			
		complex left = _mul(b, log(r));
		complex right = complex(-b.imag*theta, b.real*theta); // b*i*theta
		return _exp(_add(left, right));
	}

	// (a+bi)^(c)
	// same as last but d is 0
	complex _pow(complex a, calc_type b) {
		if(a.real == 0 && a.imag == 0){
			return complex(0, 0);
		}
	
		// convert to polar form
		calc_type r = _abs(a);
		calc_type theta = atan(a.imag / a.real);
		return _exp(complex(b * log(r), b*theta));
	}

	
	
	// e^(a+bi) = e^a * e^bi 
	complex _exp(complex a){
		return _mul(_imagExp(a.imag), _exp(a.real));
	}
	
	// e^iz = cos(z) + i*sin(z)
	complex _imagExp(calc_type b){
		return complex(cos(b), sin(b));		
	}
	
	// sin(z) = (e^(iz) - e^(-iz))/2i
	complex _sin(complex z){
		complex top = _sub(_exp(_muli(z)), _exp(_muli(_neg(z))));
		// (a + bi)/2i = (b-ia)/2
		return _div(complex(top.imag, -top.real), 2);
	}

	// cos(z) != sin(z + pi/2)
	// cos(z) = (e^(iz) + e^(-iz))/2 
	complex _cos(complex z){
		complex top = _add(_exp(_muli(z)), _exp(_muli(_neg(z))));
		return _div(top, 2);
	}
)"




