//: tests/marsh/Matrix_tests.cpp

#include "leaqx8664.hpp"
#include <iostream>
#include <array>

std::array<int> test_2by4_matrix{1,2,3,4,5,6,7,8};

/////////////////////
// Test the functionality of operator<< 
/////////////////////
bool test_operator<<();
////////////////////
// Test operator== by constructing two matrices and initializing them
// with the values in test_2by4_matrix
////////////////////
bool test_operator==();
////////////////////
// Test operator!= by constructing two matrices and initializing one
// with the values in test_2by4_matrix and the other with the same 
// values but in reverse order.
////////////////////
bool test_operator!=();
////////////////////
// Test all versions of operator() for a matrix built from the values
// in test_2by4_matrix.
////////////////////
bool test_operator()();

int main(){

    size_t passed = 0;
    size_t total = 0;

}



