//#pragma once

#include "spline.h"
#include <iostream>
#include <fstream>

using namespace std;

class file_io
{
public:
	const char* filename = "table.txt";
	void fill_file(const char* filename);
	void print_file(const char* filename);
	int get_values(const char* filename, spline& S1);
};