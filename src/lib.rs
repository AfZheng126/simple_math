

#[no_mangle] // Prevent name mangling
pub extern "C" fn add_numbers(a: f64, b: f64) -> f64 {
  a + b
}

#[no_mangle] // Prevent name mangling
pub extern "C" fn multiply_numbers(a: f64, b: f64) -> f64 {
  a * b
}