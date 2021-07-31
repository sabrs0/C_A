#include "spline.h"
void spline::get_a_c()
{
	a_coef = new double[TAB_LEN - 1];
	for (int i = 0; i < TAB_LEN - 1; i++)
	{
		a_coef[i] = y_arr[i];
	}
}
void spline::get_b_c()
{
	b_coef = new double[TAB_LEN - 1];
	for (int i = 1; i < TAB_LEN - 1; i++)
	{
		double h_coef = x_arr[i] - x_arr[i - 1];
		b_coef[i - 1] = (y_arr[i] - y_arr[i - 1] / h_coef) - (h_coef * (c_coef[i] + 2 * (c_coef[i - 1])) / 3);
	}
	double h_coef = x_arr[TAB_LEN - 1] - x_arr[TAB_LEN - 2];
	b_coef[TAB_LEN - 2] = y_arr[TAB_LEN - 1] - y_arr[TAB_LEN - 2] / h_coef - h_coef * 2 * c_coef[TAB_LEN - 2] / 3;
	
}
void spline::get_c_c()
{
	double h_coef1;
	double h_coef2;
	double f;
	double* ksi_arr = new double[TAB_LEN];
	double* tet_arr = new double[TAB_LEN];
	c_coef = new double[TAB_LEN - 1];

	ksi_arr[0] = ksi_arr[1] = 0;
	tet_arr[0] = tet_arr[1] = 0;

	for (int i = 2; i < TAB_LEN; i++)
	{
		h_coef1 = x_arr[i] - x_arr[i - 1];
		h_coef2 = x_arr[i - 1] - x_arr[i - 2];
		f = 3 * ((y_arr[i] - y_arr[i - 1] / h_coef1) - (y_arr[i - 1] - y_arr[i - 2] / h_coef2));
		ksi_arr[i] = -(h_coef1/ (h_coef2 * ksi_arr[i - 1] + 2 * (h_coef1 +  h_coef2)));	
		tet_arr[i] = (f - h_coef1 * tet_arr[i - 1]) / (h_coef1 * ksi_arr[i - 1] + 2 * (h_coef1 + h_coef2));
	}
	c_coef[TAB_LEN - 2] = tet_arr[TAB_LEN - 1];
	for (int i = TAB_LEN - 2; i >= 1; i--)
	{
		c_coef[i - 1] = ksi_arr[i] * c_coef[i] + tet_arr[i];
	}
}
void spline::get_d_c()
{
	d_coef = new double[TAB_LEN - 1];
	for (int i = 1; i < TAB_LEN - 1; i++)
	{
		double h_coef = x_arr[i] - x_arr[i - 1];
		d_coef[i - 1] = (c_coef[i] - c_coef[i - 1]) / (3 * h_coef);
	}
	double h_coef = x_arr[TAB_LEN - 1] - x_arr[TAB_LEN - 2];
	d_coef[TAB_LEN - 2] = -c_coef[TAB_LEN - 2] / (3 * h_coef);
}
int spline::count_spline()
{
	get_a_c();
	get_c_c();
	get_b_c();
	get_d_c();
	arg = 5.5;
	int ind = TAB_LEN - 1;
	for (int i = 0; i < TAB_LEN; i++)
	{
		if (x_arr[i] >= arg)
		{
			ind = i;
			break;
		}
	}
	ind -= 1;
	if (ind < 0)
		return ERROR;
	double h = arg - x_arr[ind];
	ans = a_coef[ind] + b_coef[ind] * h + c_coef[ind] * h * h + d_coef[ind] * h * h * h;
	cout << ans << '\n';
	return OK;
}