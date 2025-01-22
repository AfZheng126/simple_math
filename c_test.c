#include <stdio.h>

// Declare the function from the shared object library
extern double add_numbers(double a, double b);
extern double multiply_numbers(double a, double b);

int main() {
	double result = add_numbers(3.0, 4.0);
	double result2 = multiply_numbers(3.0, 4.0);
	printf("Sum: %f\n", result);
	printf("Product: %f\n", result2);
	return 0;
}
