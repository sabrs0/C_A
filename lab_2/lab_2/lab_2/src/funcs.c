#include "../inc/funcs.h"
int find_ind(double *x, double arg, int degree, int len)
{
	int from,  to;
	for (int i = 0; i < len - 1; i ++)
	{
		if (arg < x[i])
		{	
			from = i - 1;
			break;
		}
	}
	if (degree == 1)
	{
		to = from + 1;
	}
	else
	{
		to = from + degree / 2;
	}
	while(to >= len)
	{
		from = from - 1;
		if (degree == 1)
		{
			to = from + 1;
		}
		else
		{
			to = from + degree / 2;
		} 
	}
	return from;
}
double count_Y(double y0, double y1, double x0, double x1)
{
	return ((y0 - y1) / (x0 - x1));
}
void free_matr(double **matr, int n)
{
	for (int i = 0; i < n; i ++)
	{
		free(matr[i]);
	}
	free(matr);
}
int create_matr(double ***matr, int n, int m)
{
	*matr = calloc(n, sizeof(double *));
	if (!(*matr))
	{	
		printf("#1\n");
		return ERROR;
	}
	for (int i = 0; i < n; i ++)
	{
		*(*matr + i) = calloc(m, sizeof(double));
		if (*(*matr + i) == NULL)
		{
			free_matr(*matr, ROWS);
			printf("#2\n");
			return ERROR;
		}
	}
	return OK;
}
int read_x_vals(char filename[], data_t *data)
{
	FILE *f;
	int check;
	f = fopen(filename, "r");
	if (f == NULL)
	{
		printf("#3\n");
		return ERROR;
	}
	data->x = malloc(sizeof(double) * COLS);
	if (!data->x)
	{
		printf("#4\n");
		fclose(f);
		return ERROR;
	}
	for (int i = 0; i < COLS; i ++)
	{
		check = fscanf(f, "%lf", &(data->x[i]));
		if (check != 1)
		{
			printf("#5\n");
			free(data->x);
			fclose(f);
			return ERROR;
		}
	}
	fclose(f);
	return OK;
	
}
int read_y_vals(char filename[], data_t *data)
{
	FILE *f;
	int check;
	f = fopen(filename, "r");
	if (f == NULL)
	{
		printf("#6\n");
		return ERROR;
	}
	data->y = malloc(sizeof(double) * ROWS);
	if (!data->y)
	{
		fclose(f);
		printf("#7\n");
		return ERROR;
	}
	double tmp;
	for (int i = 0; i < COLS; i ++)
	{
		check = fscanf(f, "%lf", &tmp);
	}
	for (int i = 0; i < ROWS; i ++)
	{	
		for (int j = 0; j < COLS + 1; j ++)
		{
			check = fscanf(f, "%lf", &tmp);
			if (j == 0)
			{
				if (check != 1)
				{
					free(data->y);
					fclose(f);
					printf("#8\n");						
					return ERROR;
				}
				data->y[i] = tmp;
			}
		}
	}
	fclose(f);
	return OK;
	
}
int read_dots(char filename[], data_t *data)
{
	FILE *f;
	int check;
	f = fopen(filename, "r");
	if (f == NULL)
	{
		printf("#9\n");
		return ERROR;
	}
	if (create_matr(&(data->dots), ROWS, COLS) == ERROR)
	{
		fclose(f);
		printf("#10\n");
		return ERROR;
	}
	double tmp;
	for (int i = 0; i < COLS; i ++)
	{
		check = fscanf(f, "%lf", &tmp);
	}
	for (int i = 0; i < ROWS; i ++)
	{	
		for (int j = 0; j < COLS + 1; j ++)
		{
			check = fscanf(f, "%lf", &tmp);
			if (j >= 1)
			{
				if (check != 1)
				{
					free_matr(data->dots, ROWS);
					fclose(f);
					printf("#11\n");
					return ERROR;
				}
				data->dots[i][j - 1] = tmp;
			}
		}
	}
	fclose(f);
	return OK;
	
}
int read_data(char filename[], data_t *d1)
{
	int rc = OK;
	rc = read_x_vals(filename, d1);
	if (!rc)
	{
		rc = read_y_vals(filename, d1);
	}
	if (!rc)
	{
		rc = read_dots(filename, d1);
	}
	return rc;
	
}
void print_data(data_t *data)
{
	printf("   ");
	for (int i = 0; i < COLS; i ++)
	{
		printf("%2.0lf ", data->x[i]);
	}
	printf("\n");
	for (int i = 0; i < ROWS; i ++)
	{
		for (int j = 0; j < COLS + 1; j ++)
		{
			if (j == 0)
			{
				printf("%2.0lf ", data->y[i]);
			}
			else
			{
				printf("%2.0lf ", data->dots[i][j - 1]);
			}
		}
		printf("\n");
	}
	printf("\n");
}
int build_sp_div_tab(double *arg, double *func, sp_div_tab *tab, int degree)
{
	if (degree >= ROWS)
	{
		return ERROR;
	}
	tab->vals[0][0] = func[0];
	for (int i = 0; i < degree; i ++)
	{
		tab->vals[1][i] = (func[i] - func[i + 1]) / (arg[i] - arg[i + 1]);
	}
	int len = degree;
	int iterator = 2;
	for (int i = 2; i < degree + 1; i ++)
	{
		for (int j = 0 ; j < len - 1; j ++)
		{
			tab->vals[i][j] = (tab->vals[i - 1][j] - tab->vals[i - 1][j + 1]) / (arg[j] - arg[j + iterator]);
			if (fabs(tab->vals[i][j]) <= EPS)
				tab->vals[i][j] = 0.0;
		}
		len --;
		iterator ++;
	}
	return OK;
}
int create_tab(sp_div_tab *tab, double *arg, double *func, int degree)
{
	if (create_matr(&(tab->vals), ROWS, COLS) == ERROR)
	{
		printf("#12\n");
		return ERROR;
	}
	printf("WTF\n");
	build_sp_div_tab(arg, func, tab, degree);
	return OK;
}
double Polynom_Newtone(double argument,double *args, double **polynome, int degree)
{
	double ans = 0.0;
	double mnoj = 1.0;
	ans += polynome[0][0];
	for (int i = 1; i < degree + 1; i ++)
	{
		mnoj = 1.0;
		for (int j = 0; j < i; j ++)
		{
			mnoj = mnoj * (argument - args[j]);
		}
		mnoj = mnoj * polynome[i][0];
		ans += mnoj;
	}
	return ans;
}
void process(data_t *data, interp_arr_t *arr, double x_arg, double y_arg, int x_deg, int y_deg)
{
	arr->arr = malloc(sizeof(double) * ROWS);
	if (!arr->arr)
		printf("ERROR\n");
	sp_div_tab tab;
	for (int i = 0; i < ROWS; i ++)
	{
		printf("SMTH DO\n");
		create_tab(&tab, data->x, data->dots[i], x_deg);
		arr->arr[i] = Polynom_Newtone(x_arg, data->x, tab.vals, x_deg);
		printf("%lf ", arr->arr[i]);
		free_matr(tab.vals, ROWS);
	}
	double answer;
	create_tab(&tab, data->y, arr->arr, x_deg);
	answer = Polynom_Newtone(y_arg, data->y, tab.vals, y_deg);
	printf("ANSWER = %lf\n", answer);
}

