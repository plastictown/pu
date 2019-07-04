#include <iostream>




#include "lab5.h"

int main() {
	calc C;
	double a = C.action_with_output(3, '+', 5);
	double b = C.action_with_output(4, '-', 1.33);
	double c = C.action_with_output(7, '*', 2);
	double d = C.action_with_output(10, '/', 3);
	double e = C.action_with_output(2, '^', 10);
	double f = C.action_with_output(3.14, '?', 42);
	double g = C.action_with_output(7.15, '%', 3.01);

	std::cin.get();
	return 0;
}