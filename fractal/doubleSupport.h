#pragma once


#define DOUBLE_SUPPORT R"(
	double _pow(double a, int n) {
		double res = 1;
		for (int i = 0; i < n; i++) {
			res *= a;
		}
		return res;
	}

	int _fact(int n) {
		int res = 1;
		for (int i = 1; i <= n; i++) {
			res *= i;
		}
		return res;
	}
	
	double abs(double a) {
		return a < 0 ? -a : a;
	}
	
	double sin(double a) {
		double res = 0;
		for (int i = 0; i < 10; i++) {
			res += (i % 2 == 0 ? 1 : -1) * _pow(a, 2 * i + 1) / _fact(2 * i + 1);
		}
		return res;
	}
	
	double cos(double a) {
		double res = 0;
		for (int i = 0; i < 10; i++) {
			res += (i % 2 == 0 ? 1 : -1) * _pow(a, 2 * i) / _fact(2 * i);
		}
		return res;
	}

	double _exp(double a) {
		double res = 0;
		for (int i = 0; i < 10; i++) {
			res += _pow(a, i) / _fact(i);
		}
		return res;
	}
)"