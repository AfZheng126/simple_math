# simple_math

## Steps to Create the Rust Function Callable from MATLAB

### 1. Set Up the Rust Project

All functions that are to be called must be written in `lib.rs` in the following format: 
```
#[no_mangle] // Prevent name mangling
pub extern "C" fn function_name(a: f64, b: f64) -> f64 {
  a + b
}
```
The `#[no_mangle]` attribute allows the function name to be called from C. The `extern "C"` specifies taht this function uses the C calling convention, making it compatible with C/C++.

## 2. Update Cargo.toml
Append the `Cargo.toml` file with
```
[lib]
crate-type = ["cdylib"]
```
This makes Rust build a dynamic library, which will be used by the C wrapper.

## 3. Build the shared library
Run
```
cargo build --release
```
and copy the `.so` file (or `.dll` for windows, `.dylib` for apple) into a path that can be found by C/C++.

## 4. Create the C Wrapper for MEX

Create a new file `mex_wrapper.c`:
```
#include "mex.h"

// Declare the Rust function signature
extern double add_numbers(double a, double b);

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

    // Return the result to MATLAB
    plhs[0] = mxCreateDoubleScalar(result);
}
```
This allows C to get functions from the `.so` file.

## 5. Compile the MEX Function
Open MATLAB and run the following command, specifying the paths to the Rust shared library and the C wrapper:
```
mex -L. path_to_so_file.so mex_wrapper.c
```
`-L.` specifies that the library (.so file) is in the current directory.
Sometimes, you may also want to include `-ldl -lpthread`, which are common system dependencies for shared libraries and dynamic loading. However, this simple example does not require it.


## 6. Conclusion
All functions written in the `lib.rs` can be called by MATLAB.

## 7. Calling the functions now in Rust main.rs
If you want to call the function in Rust, you need to link to the C dynamic library in `main.rs` file. To do this, first add `libloading` to your dependencies in `Cargo.toml`.
```
[dependencies]
libloading = "0.7"
```
Then in `main.rs`, load the shared library and call the function
```
use libloading::{Library, Symbol};

fn main() {

    unsafe {
        // Load the shared library
        let lib = Library::new("target/release/libmy_project.so").expect("Failed to load library");

        // Get the symbol (function) from the library
        let my_function: Symbol<unsafe extern "C" fn()> = lib.get(b"my_function").expect("Failed to load function");

        // Call the function
        my_function();
    }
}
```


# How to use Gmesh

First, use a .geo file to create a script defining the lines, curves, surfaces, and the mesh properties. Then load the .geo file into gmesh and click 2D under Mesh to generate the 2D mesh. Now click export with Version 2 ASCII and save as a .msh file without including the non-mesh elements. Finally read the data in Matlab using this [guide](https://victorsndvg.github.io/FEconv/formats/gmshmsh.xhtml). 
