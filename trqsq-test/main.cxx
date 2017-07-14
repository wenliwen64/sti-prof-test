#include "../common/tools.h"
#include <iostream>
#include <string>
#include "tcl_trqsq.h"
#include "eigen.h"
using std::string;
using std::cout;
using std::endl;
using tested_function_t = double* (*)(const double*, const double*, double*, int);

// declarations...
tested_function_t get_test_func(const char* arg, string& test_func_name);
void fill_sym_m(double* m, int dim);

int main(int argc, char** argv){
    int dim = 10;
    int n_iterations = 100000;
    string test_func_name;

    timespec time_0, time_1;
    timespec time_accum{};
    srand(1);

    tested_function_t test_func = get_test_func(argv[1], test_func_name);

    int num_e_sym = (dim * dim + dim) / 2;
    // matrix initialization...
    double* q_sym = new double[num_e_sym];
    double* s_sym = new double[num_e_sym];
    double* r_sym = new double[num_e_sym];

    // run thru iterations...
    for(int i = 0; i != n_iterations; ++i){
	// fill symmetric matrices...
	fill_sym_m(q_sym, num_e_sym);
	fill_sym_m(s_sym, num_e_sym);

        // measurement starts...
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time_0);
	test_func(q_sym, s_sym, r_sym, dim);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time_1);
        // measurement ends...

	tools::time_add(time_accum, tools::time_diff(time_0, time_1));
    }
    cout << "elapsed time: " << time_accum.tv_sec << "."  << time_accum.tv_nsec << endl;
    return 0;
}

tested_function_t get_test_func(const char* arg, string& test_func_name){
    string arg1(arg);

    if(string("trqsq").find(arg1) == 0){
	test_func_name = "tcl_trqsq";
	return trqsq::tcl_trqsq;
    }	
    else if(string("eigen").find(arg1) == 0){
	test_func_name = "eigen";
	return eigen::trqsq_eigen;
    }
    else{
        test_func_name = "tcl_trqsq";
	return trqsq::tcl_trqsq;
    }
	
}

void fill_sym_m(double* m, int dim){
    for(int i = 0; i != dim; ++i)
	m[i] = tools::my_rand(0.0, 1.0);
}

/*
void flatten(const double** om, double* rm, int row, int col){
    for(int i = 0; i != row; ++i)
	for(int j = 0; j != col; ++j)
	    rm[i * row + j] = om[i][j];
}
*/
