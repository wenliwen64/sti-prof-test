#include "../common/tools.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "tcl_trqsq.h"
#include "eigen.h"
using std::string;
using std::cout;
using std::endl;
using tested_function_t = double* (*)(const double*, const double*, double*, int);

// declarations...
tested_function_t get_test_func(const char* arg, string& test_func_name);
int init_inputs(const char*, double*&, double*&, double*&, int dim);
void fill_sym_m(const char*, double* m, int dim);
void map_from_sym_to_full(const double* m_sym, double* m_full, int dim);

int main(int argc, char** argv){
    int dim = atoi(argv[2]);
    int n_iterations = atoi(argv[3]);
    string test_func_name;

    timespec time_0, time_1;
    timespec time_accum{};
    srand(1);

    tested_function_t test_func = get_test_func(argv[1], test_func_name);
    double* q_input; 
    double* s_input; 
    double* r_input;

    // matrix initialization...
    int num_e = init_inputs(argv[1], q_input, s_input, r_input, dim);
    q_input[0] = 0;
    s_input[0] = 0;

    // run thru iterations...
    for(int i = 0; i != n_iterations; ++i){

	// fill symmetric matrices...
	fill_sym_m(argv[1], q_input, dim);
	fill_sym_m(argv[1], s_input, dim);

        // measurement starts...
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time_0);
	test_func(q_input, s_input, r_input, dim);
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

int init_inputs(const char* arg, double*& q, double*& s, double*& r, int dim){
    string arg1(arg);

    int num_e_sym = (dim * dim + dim) / 2;
    int num_e_full = dim * dim;

    if(string("trqsq").find(arg1) == 0){
	q = new double[num_e_sym];
	s = new double[num_e_sym];
	r = new double[num_e_sym];
        return num_e_sym;
    }
    else if(string("eigen").find(arg1) == 0){
	q = new double[num_e_full];
	s = new double[num_e_full];
	r = new double[num_e_full];
        return num_e_full;
    }
    else{
	q = new double[num_e_sym];
	s = new double[num_e_sym];
	r = new double[num_e_sym];
        return num_e_sym;
    }
}

void fill_sym_m(const char* arg, double* m, int dim){
    string arg1(arg);

    int num_e_sym = (dim * dim + dim) / 2;

    if(string("trqsq").find(arg1) == 0){
	for(int i = 0; i != num_e_sym; ++i)
	    m[i] = tools::my_rand(0.0, 1.0);
    }
    else if(string("eigen").find(arg1) == 0){
	for(int i = 0; i != dim; ++i){
            for(int j = 0; j != dim; ++j){
		if(i <= j)
                    m[i * dim + j] = tools::my_rand(0.0, 1.0);
		else
		    m[i * dim + j] = m[j * dim + i];
	    } 
	}
    }
    else
	return;
}

void map_from_sym_to_full(const double* m_sym, double* m_full, int dim){
    for(int i = 0; i != dim; ++i){
	for(int j = 0; j != dim; ++j){
	    if(i <= j)
		m_full[i * dim + j] = m_sym[j * (j + 1) / 2 + i]; 
	    else
		m_full[i * dim + j] = m_sym[i * (i + 1) / 2 + j];
	}
    }
}

void map_from_full_to_sym(const double* m_full, double* m_sym, int dim){
    for(int i = 0; i != dim; ++i){
	for(int j = 0; j != dim; ++j){
	    if(i <= j)
		m_sym[j * (j + 1) / 2 + i] = m_full[i * dim + j];
	}
    }
}


/*
void flatten(const double** om, double* rm, int row, int col){
    for(int i = 0; i != row; ++i)
	for(int j = 0; j != col; ++j)
	    rm[i * row + j] = om[i][j];
}
*/
