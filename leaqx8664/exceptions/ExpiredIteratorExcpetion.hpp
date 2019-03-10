//: leaqx8664/exceptions/ExpiredIteratorException.hpp 

#ifndef LIB_LEAQ_EXPIRED_ITERATOR_EXCEPTION_HPP
#define LIB_LEAQ_EXPIRED_ITERATOR_EXCEPTION_HPP

#include <exception>

class ExpiredIteratorException : std::Exception{

    virtual const char* what() const noexcept{
    
	return "Failed call to an expired iterator";
    }
}
#endif
