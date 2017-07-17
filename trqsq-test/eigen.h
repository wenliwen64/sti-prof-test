#include "Eigen/Dense"
#include "constants.h"
namespace eigen{
    using namespace Eigen;

    double *trqsq_eigen(const double *q_full, const double *s_full, double *r_full, int dim){
        const int dim_ = dim;
        //Map< const Matrix<double, 10, 10, RowMajor> > q_m(q_full);
        Map< const MatrixXd > q_m(q_full, dim, dim);
	//Map< const Matrix<double, 10, 10, RowMajor> > s_m(s_full);
	Map< const MatrixXd > s_m(s_full, dim, dim);
	//Map< Matrix<double, 10, 10, RowMajor> > r_m(r_full);
        MatrixXd r_m(dim, dim);

        r_m = q_m * s_m * q_m;	
        r_full = r_m.array().data();
        //map_from_full_to_sym(r_full, r_sym, dim);
        return 0;
    }
}
