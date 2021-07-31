#include "io.h"
void file_io::fill_file(const char* filename)
{
	ofstream f_init;
	int n = 10;
	f_init.open(filename);
	for (int i = 0; i < TAB_LEN; i++)
	{
		f_init << double(i) << ' ' << double(i * i) << '\n';
	}
	f_init.close();

}
void file_io::print_file(const char* filename)
{
	ifstream f_init;
	int n = 20;
	f_init.open(filename);
	double val_x, val_y;
	for (int i = 0; i < TAB_LEN; i++)
	{
		f_init >> val_x;
		f_init >> val_y;
		cout << val_x << ' ' << val_y << '\n';
	}
	f_init.close();

}

int file_io::get_values(const char* filename, spline &S1)
{
	ifstream f;
	f.open(filename);
	S1.x_arr = new double[TAB_LEN];
	S1.y_arr = new double[TAB_LEN];
	for (int i = 0; i < TAB_LEN; i ++)
	{
		f >> S1.x_arr[i];
		f >> S1.y_arr[i];
	}
	f.close();
	return 0;

}