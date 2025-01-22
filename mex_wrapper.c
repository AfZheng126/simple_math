#include "mex.h"

// Declare the Rust function signature
extern double add_numbers(double a, double b);
extern double multiply_numbers(double a, double b);

// The MEX function interface
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs != 2) {
        mexErrMsgIdAndTxt("rust_mex:add_two_numbers", "Two input arguments required.");
    }

    // Extract inputs from MATLAB
    double a = mxGetScalar(prhs[0]);
    double b = mxGetScalar(prhs[1]);

    // Call the Rust function
    double result = add_numbers(a, b);
    double result2 = multiply_numbers(a, b);

    // Return the result to MATLAB
    plhs[0] = mxCreateDoubleScalar(result);
    plhs[1] = mxCreateDoubleScalar(result2);
}
