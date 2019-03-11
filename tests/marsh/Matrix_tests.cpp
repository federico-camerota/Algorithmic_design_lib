//: tests/marsh/Matrix_tests.cpp

#include "leaqx8664.hpp"
#include <iostream>

bool test_constructor();
bool test_copy_constructor();
bool test_move_constructor();

int main(){

    size_t passed = 0;
    size_t total = 0;

    ++total;
    passed += test_constructor();
   // ++total;
   // passed += test_copy_constructor();
   // ++total;
   // passed += test_move_constructor();
}


bool test_constructor(){

    leaqx8664::marsh::Matrix<double> mat{2,2};
    double num = 2.2;
    for (auto& x : mat)
	x = ++num;
    std::cout << mat << std::endl;
    return true;
}
