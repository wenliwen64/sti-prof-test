#include "Eigen/Dense"
#include "constants.h"
namespace eigen{
    using namespace Eigen;

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

    double *trqsq_eigen(const double *q_sym, const double *s_sym, double *r_sym, int dim){
        double* q_full = new double[dim * dim];
        double* s_full = new double[dim * dim];
        double* r_full = new double[dim * dim];
        map_from_sym_to_full(q_sym, q_full, dim);
        map_from_sym_to_full(s_sym, s_full, dim);
	
        const int dim_ = dim;

        Map< MatrixXd > q_m(q_full, dim, dim);
	Map< MatrixXd > s_m(s_full, dim, dim);
        MatrixXd r_m(dim, dim);

        r_m = q_m * s_m * q_m;	
        r_full = r_m.array().data();
        map_from_full_to_sym(r_full, r_sym, dim);
        return 0;
    }
}
