//: leaqx8664/exceptions/IndexOutOfBoundsException.hpp 

#ifndef LIB_LEAQ_INDEX_BOUNDS_EXCEPTION_HPP
#define LIB_LEAQ_INDEX_BOUNDS_EXCEPTION_HPP

#include <exception>

class IndexOutOfBoundsException : std::exception {

    const char* what() const noexcept{
    
	return "Invalid index";
    }
};
#endif
