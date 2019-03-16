//: tests/marsh/Matrix_tests.cpp

#include "leaqx8664.hpp"
#include <iostream>
#include <array>

std::array<int,8> test_2by4_matrix{1,2,3,4,5,6,7,8};

/////////////////////
// Test the get_shape member of the matrix class
/////////////////////
bool test_get_shape();
/////////////////////
// Test the max member of the matrix class
/////////////////////
bool test_max_index();
/////////////////////
// Test the functionality of matrix iterators
/////////////////////
bool test_iterators();
/////////////////////
// Test the functionality of operator<< 
/////////////////////
bool test_operator_put_to();
////////////////////
// Test operator== by constructing two matrices and initializing them
// with the values in test_2by4_matrix
////////////////////
bool test_operator_equal();
////////////////////
// Test operator!= by constructing two matrices and initializing one
// with the values in test_2by4_matrix and the other with the same 
// values but in reverse order.
////////////////////
bool test_operator_not_equal();
////////////////////
// Test all versions of operator() for a matrix built from the values
// in test_2by4_matrix.
////////////////////
bool test_operator_call();

int main(){

    std::cout << "Get shape test : " <<  (test_get_shape() ? "passed" : "failed") << std::endl;
    std::cout << "Max_index test : " << (test_max_index() ? "passed" : "failed") << std::endl;
    std::cout << "Iterators test : " << (test_iterators() ? "passed" : "failed") << std::endl;
//    std::cout << "Operator put to test : " << (test_operator_put_to() ? "passed" : "failed") << std::endl;
    std::cout << "Operator equal test : " << (test_operator_equal() ? "passed" : "failed") << std::endl;
    std::cout << "Operator not equal test : " << (test_operator_not_equal() ? "passed" : "failed") << std::endl;
    std::cout << "Operator call test : " << (test_operator_call() ? "passed" : "failed") << std::endl;
}

bool test_get_shape(){

    leaqx8664::marsh::Matrix<int> mat{2,4};
    leaqx8664::marsh::Matrix<int>::shape mat_shape = mat.get_shape();
    return mat_shape.first == 2 && mat_shape.second == 4;
}
bool test_max_index(){

    leaqx8664::marsh::Matrix<int> mat{2,4};
    size_t max_index = mat.get_max_index();
    return max_index == 7;
}
bool test_iterators(){

    leaqx8664::marsh::Matrix<int> mat{2,4};
    size_t i = 0;
    for (auto& x : mat)
	x = test_2by4_matrix[i++];

    i = 0;
    for (const auto& x : mat)
	if (x != test_2by4_matrix[i++])
	    return false;
    return true;
}

bool test_operator_put_to(){

    leaqx8664::marsh::Matrix<int> mat{2,4};
    size_t i = 0;
    for (auto& x : mat)
	x = test_2by4_matrix[i++];

    std::cout << mat << std::endl;

    return true;
}

bool test_operator_equal(){

    leaqx8664::marsh::Matrix<int> mat{2,4};
    size_t i = 0;
    for (auto& x : mat)
	x = test_2by4_matrix[i++];

    leaqx8664::marsh::Matrix<int> mat2{2,4};
    i = 0;
    for (auto& x : mat2)
	x = test_2by4_matrix[i++];

    return mat == mat2;
}

bool test_operator_not_equal(){

    leaqx8664::marsh::Matrix<int> mat{2,4};
    size_t i = 0;
    for (auto& x : mat)
	x = test_2by4_matrix[i++];

    leaqx8664::marsh::Matrix<int> mat2{2,4};
    for (auto& x : mat2)
	x = test_2by4_matrix[--i];

    return mat != mat2;
}


bool test_operator_call(){

    bool result = true;
    leaqx8664::marsh::Matrix<int> mat{2,4};
    size_t i = 0;
    for (auto& x : mat)
	x = test_2by4_matrix[i++];
    leaqx8664::marsh::Matrix<int> mat2{2,4};
    for (size_t j = 0; j < 2; ++j)
	for (size_t k = 0; k < 4; ++k)
	    mat2(j,k) = test_2by4_matrix[j*4 + k];
    leaqx8664::marsh::Matrix<int> mat3{2,4};
    for (size_t j = 0; j <= mat3.get_max_index(); ++j)
	    mat3(j) = test_2by4_matrix[j];
    
    return (mat == mat2) && (mat == mat3);
}
