//: marsh/Matrix.hpp
/**
 * @file marsh/Matrix.hpp
 */

#ifndef MARSH_MATRIX_HPP
#define MARSH_MATRIX_HPP

/*
 * Include headers
 */
#include <memory>
#include <utility>
#include <iterator>

#include "../leaq_exceptions.hpp"

namespace leaqx8664{

    namespace marsh{
	/**
	 * @class Matrix
	 *
	 * @brief Class representing a matrix of scalars
	 *
	 * A matrix is a 2 dimensional arrya with scalar elements for which common mathematical operations
	 * such as summation and multiplication are defined through the overloading of operators.
	 */
	template <typename T>
	class Matrix<T>{

	    //! Pointer to array of elements in the matrix
	    std::uniq_ptr<T> elements; 
	    //! Pair of the number of rows and columns in the matrix
	    std::pair<size_t, size_t> dims; 
	    //! Maximum valid index in this matrix
	    const size_t max_index;

	    /**
	     * @class Matrix_iterator
	     *
	     * @brief Iterator for the matrix class
	     *
	     * This class allows iteration through a Matrix object by rows.
	     */
	    class Matrix_iterator : std::iterator<std::forward_iterator_tag, T>;
	    /**
	     * @class Matrix_const_iterator
	     *
	     * @brief Const iterator for the matrix class
	     *
	     * This class allows iteration through a const Matrix object by rows.
	     */
	    class Matrix_const_iterator : Matrix_iterator;

	    public:

		/**
		 * @class Matrix_block
		 *
		 * @brief A Matrix_block represents a block in a Matrix object
		 * 
		 * The Matrix_block class provides an easy way to work on sublocks of the matrix.
		 */
		class Matrix_block;

		//! Alias for the scalar type
		using scalar_type = T;
		//! Alias for the dimensions of the matrix
		using dimension = std::pair<size_t, size_t>;
		//! Alias for matrix iterators
		using iterator = Matrix_iterator;
		//! Alias for matrix const iterators
		using const_iterator = Matrix_const_iterator;
		//! Alias for matrix blocks
		using block = Matrix_block;



		/*
		 *  CONSTRUCTORS
		 */

		/**
		 * Create a matrix of uninitialized values with dimension
		 * (n_rows, n_columns)
		 *
		 * @param n_rows Number of rows in the matrix
		 * @param n_columns Number of columns in the matrix
		 */
		Matrix (const size_t n_rows, const size_t n_columns) :
		    dims{n_rows, n_columns}, max_index{n_rows*n_columns - 1}, elements{new T[max_index + 1]}
		{}
		/**
		 * Copy constructor for Matrix objects
		 *
		 * @param other Matrix object to copy from
		 */
		Matrix (const Matrix<T>& other) :
		    dims{other.dims}, max_index{other.max_index}, elements{new T[max_index + 1]}
		{
		    //copy elements of the given matrix in the new one
		    for (size_t i = 0U; i <= max_index; ++i)
			elements[i] = other.elements[i];
		}
		/**
		 * Move constructor for Matrix objects
		 *
		 * @param other Matrix object to move from
		 */
		Matrix (Matrix<T>&& other) :
		    dims{std::move(other.dims)}, max_index{other.max_index}, elements{std::move(other.elements)}
		{}
		/**
		 * ADD CONSTRUCTORS USING MATRIX SUBLOCKS
		*/

	    private:
		
		/*
		 * Matrix_iterator definition
		 */
		class Matrix_iterator : std::iterator<std::forward_iterator_tag, T>{

		    //! Pointer to the current element pointed by the iterator
		    scalar_type* current_position;
		    //! Number of elements left to visit
		    size_t remaining;

		    public:
			
			/**
			 * @brief Constructor for a Matrix_iterator
			 *
			 * Create a Matrix_iterator that points to the given matrix element.
			 *
			 * @param target First element in the iteration through the matrix
			 * @param max Maximum offset from the starting element
			 */
			Matrix_iterator (scalar_type* target, size_t max) :
			    current_position{target}, remaining{max + 1}
			{}
			/**
			 * @brief Operator++ for the Matrix_iterator class
			 *
			 * Update the iterator to point to the following element in the matrix.
			 * When all elements have been consumed, a call to this method will throw
			 * an ExpiredIteratorException.
			 */
			iterator& operator++(){
			
			    if (remaining > 0){
			    
				//decrement remaining, when different from zero increment 
				//the current_position while when reaches zero set to
				//nullptr
				(--remaining && ++current_position) || current_position = nullptr;
				return this;
			    }

			    throw ExpiredIteratorException{};
			}
			/**
			 * @brief Operator* for the Matrix_iterator class
			 *
			 * Returns a reference to the current element pointed by the iterator.
			 * If all elements have already been consumed, a call to this method will
			 * throw an ExpiredIteratorException
			 */
			scalar_type& operator*(){
			
			    if (current_position)
				return *current_position;
			    else
				throw ExpiredIteratorException{};
			}
			/**
			 * @brief Operator== for the Matrix_iterator class
			 *
			 * Checks if this and the given Matrix_iterator are pointint to the same
			 * element in the matrix.
			 *
			 * @param other Iterator to compare with
			 */
			bool operator==(const iterator& other){
			
			    return current_position == other.current_position;
			}
			/**
			 * @brief Operator!= for the Matrix_iterator class
			 *
			 * Check if this and the given Matrix_iterator are different
			 *
			 * @param other Iterator to check against
			 */
			bool operator!=(const iterator& other){
			
			    return !(*this == other);
			}

		};
		/*
		 * Matrix_const_iterator definition
		 */
		class Matrix_const_iterator : Matrix_iterator{}
	}
	
	
	}
}

#endif
