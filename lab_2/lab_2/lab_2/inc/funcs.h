#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define ROWS 5
#define COLS 5
#define ERROR 1
#define OK 0
#define EPS 1e-9
typedef struct
{
	double *x;
	double *y;
	double **dots;
	int y_degree;
	int x_degree;
	double x_val;
	double y_val;
} data_t;
typedef struct
{
	double **vals;
} sp_div_tab;
typedef struct
{
	double *arr;
}interp_arr_t;
int find_ind(double *x, double arg, int degree, int len);
double count_Y(double y0, double y1, double x0, double x1);
int build_sp_div_tab(double *arg, double *func, sp_div_tab *tab, int degree);
double Polynom_Newtone(double argument,double *args, double **polynome, int degree);
void free_matr(double **matr, int n);
int create_matr(double ***matr, int n, int ms);
int read_x_vals(char filename[], data_t *data);
int read_y_vals(char filename[], data_t *data);
int read_dots(char filename[], data_t *data);
int read_data(char filename[], data_t *d1);
void print_data(data_t *data);
int create_tab(sp_div_tab *tab, double *arg, double *func, int degree);
void process(data_t *data, interp_arr_t *arr, double x_arg, double y_arg, int x_deg, int y_deg);
