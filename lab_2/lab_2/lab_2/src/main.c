#include "../inc/funcs.h"
int main()
{
	char filename[256] = "test.txt";
	data_t data;
	sp_div_tab sp_table;
	interp_arr_t arr;
	if (read_data(filename, &data))
	{
		printf("ERROR in read_data\n");
		return 1;
	}
	//create_tab(&sp_table, &data);
	print_data(&data);
	printf("SMTH MAIN\n");
	process(&data, &arr, 1.5, 1.5, 0, 0);
	return 0;
}
