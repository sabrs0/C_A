#include <iostream>
#include <fstream>
#include "io.h"

using namespace std;

int main()
{
	file_io f1;
	spline s1;
	f1.fill_file(f1.filename);
	f1.print_file(f1.filename);
	f1.get_values(f1.filename, s1);
	cout<<s1.count_spline()<<'\n';
	cout << "Spline (" << s1.arg << ")" << '=' << s1.ans << '\n';
	return 0;


}