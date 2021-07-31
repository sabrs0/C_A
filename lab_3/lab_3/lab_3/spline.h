#pragma once
#define TAB_LEN 11
#define ERROR 1
#define OK 0
#include <iostream>
using namespace std;
class spline
{
public:
	int n;
	double arg;
	double ans;
	double* h_coef = nullptr;
	double* x_arr = nullptr;
	double* y_arr = nullptr;
	double* a_coef = nullptr;
	double* b_coef = nullptr;
	double* c_coef = nullptr;
	double* d_coef = nullptr;
	int count_spline();
	void get_a_c();
	void get_b_c();
	void get_c_c();
	void get_d_c();
	spline() {};
	spline(spline &spline) {};
	spline(spline&& spline) {};
};