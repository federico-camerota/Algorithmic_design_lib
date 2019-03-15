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
#include <iostream>

#include "../leaq_exceptions.hpp"

namespace leaqx8664{

    namespace marsh{
	
	/////////////////////
	// MATRIX CLASS
	/////////////////////
	
	/**
	 * @class Matrix
	 *
	 * @brief Class representing a matrix of scalars
	 *
	 * A matrix is a 2 dimensional array with scalar elements for which common mathematical operations
	 * such as summation and multiplication are defined through the overloading of operators.
	 */
	template <typename T>
	class Matrix{

	    public:

		/**
		 * @class Matrix_block
		 *
		 * @brief A Matrix_block represents a block in a Matrix object
		 * 
		 * The Matrix_block class provides an easy way to work on sublocks of the matrix.
		 */
		class Matrix_block;

		//! Alias for the dimensions of the matrix
		using dimension = std::pair<size_t, size_t>;
		//! Alias for matrix blocks
		using block = Matrix_block;
		//! Alias for scalar_type used in the matrix
		using scalar_type = T;

	    private:
		//! Pointer to array of elements in the matrix
		std::unique_ptr<scalar_type[]> elements; 
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
		class Matrix_iterator; 
		/**
		 * @class Matrix_const_iterator
		 *
		 * @brief Const iterator for the matrix class
		 *
		 * This class allows iteration through a const Matrix object by rows.
		 */
		class Matrix_const_iterator; 

	    public:

		////////////////////
		// ALIASES FOR ITERATORS
		////////////////////

		//! Alias for matrix iterators
		using iterator = Matrix_iterator;
		//! Alias for matrix const iterators
		using const_iterator = Matrix_const_iterator;


		///////////////////
		// MATRIX CLASS CONSTRUCTORS 
		///////////////////

		/**
		 * Create a matrix of uninitialized values with dimension
		 * (n_rows, n_columns)
		 *
		 * @param n_rows Number of rows in the matrix
		 * @param n_columns Number of columns in the matrix
		 */
		Matrix (const size_t n_rows, const size_t n_columns) :
		    dims{n_rows, n_columns}, max_index{n_rows*n_columns - 1}, elements{new T[n_rows*n_columns + 1]}
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

		/**
		 * @brief Descturctor for the Matrix class
		 *
		 * The destructure is set to the default one.
		 */
		~Matrix() = default;
		

		///////////////////
		// OPERATORS OVERLOADING
		///////////////////
		/**
		 * @brief Overloading of operator() for the Matrix class
		 *
		 * Return a reference to the element in row n_row and column
		 * n_column. Indexing starts at 0. If one of the indices exceeds the
		 * corresponding dimension of the matrix a IndexOutOfBoundsException
		 * will be thrown.
		 *
		 * @param n_row Row of the desired element.
		 * @param n_column Column of the desired element.
		 * @returns A reference to the desired element in the matrix.
		 *
		 * @throws IndexOutOfBoundsException if one of the given indices is not valid.
		 */
		scalar_type& operator()(const size_t n_row, const size_t n_column){
		
		    if (n_row < dims.first && n_column < dims.second)
			return elements[dims.second*n_rows + n_column];
		    throw IndexOutOfBoundsException{};
		}
		/**
		 * @brief Overloading of operator() for the Matrix class
		 *
		 * Return a reference to the element in the given position. Element positions are
		 * counted by rows starting at 0. If the given index is greater or equal to the number
		 * of elements in the matrix an IndexOutOfBoundsException will be thrown.
		 *
		 * @param index The index of the desired element.
		 * @returns A reference to the element in position index inside the matrix.
		 *
		 * @throws IndexOutOfBoundsException if one of the given indices is not valid.
		 */
		scalar_type& operator()(const size_t index){
		
		    if (index <= max_index)
			return elements[index];
		    throw IndexOutOfBoundsException{};
		}


		///////////////////
		// BEGIN AND END FUNCTIONS                      
		///////////////////
		/**
		 * @brief Get an iterator to the beginning of the structure
		 *
		 * Return an iterator to the first element in the first row of the Matrix object.
		 * Iteratorion through Matrix objects is performed by rows.
		 *
		 * @returns An iterator to the first element in the matrix
		 */
		iterator begin() { return iterator{elements.get(), max_index};}
		/**
		 * @brief Get an iterator representing the terminal element in the structure.
		 *
		 * Returns an iterator pointing to the terminal element of the matrix.
		 *
		 */
		iterator end() { return iterator{nullptr, 0};}
		/**
		 * @brief Get a const iterator to the beginning of the structure
		 *
		 * Return a const iterator to the first element in the first row of the Matrix object.
		 * Iteratorion through Matrix objects is performed by rows.
		 *
		 * @returns A const iterator to the first element in the matrix
		 */
		const_iterator begin() const { return const_iterator{elements.get(), max_index};}
		/**
		 * @brief Get a const iterator representing the terminal element in the structure.
		 *
		 * Returns a const iterator pointing to the terminal element of the matrix.
		 *
		 */
		const_iterator end() const { return const_iterator{nullptr, 0};}
		/**
		 * @brief Get a const iterator to the beginning of the structure
		 *
		 * Return a const iterator to the first element in the first row of the Matrix object.
		 * Iteratorion through Matrix objects is performed by rows.
		 *
		 * @returns A const iterator to the first element in the matrix
		 */
		const_iterator cbegin() const { return const_iterator{elements.get(), max_index};}
		/**
		 * @brief Get a const iterator representing the terminal element in the structure.
		 *
		 * Returns a const iterator pointing to the terminal element of the matrix.
		 *
		 */
		const_iterator cend() const { return const_iterator{nullptr, 0};}

		
		///////////////////
		// GET DIMENSION MEMBER                      
		///////////////////
		/**
		 * @brief Get the dimensions of a Matrix 
		 *
		 * Returns an object of type Matrix<T>::dimension that represents
		 * the dimensions of the Matrix object.
		 *
		 * @returns The dimensions of the Matrix
		 */
		dimension get_dimensions() const noexcept {
		
		    return dims;
		}

	    private:

		//////////////////
		// MATRIX ITERATOR CLASS
		//////////////////
		class Matrix_iterator : std::iterator<std::forward_iterator_tag, T> {

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
			 *
			 * @returns A reference to this iterator.
			 */
			Matrix_iterator& operator++(){
			
			    if (remaining > 0){
			    
				//decrement remaining, when different from zero increment 
				//the current_position while when reaches zero set to
				//nullptr
				(--remaining && ++current_position) || (current_position = nullptr);
				return *this;
			    }

			    throw ExpiredIteratorException{};
			}
			/**
			 * @brief Operator* for the Matrix_iterator class
			 *
			 * Returns a reference to the current element pointed by the iterator.
			 * If all elements have already been consumed, a call to this method will
			 * throw an ExpiredIteratorException
			 *
			 * @returns A reference to the element pointed by the iterator
			 * @throws ExpiredIteratorException If the iterator is pointing to the terminal element of the Matrix.
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
			 * @returns True if the given iterator points to the same element as this one, false otherwise.
			 */
			bool operator==(const Matrix_iterator& other){
			
			    return current_position == other.current_position;
			}
			/**
			 * @brief Operator!= for the Matrix_iterator class
			 *
			 * Check if this and the given Matrix_iterator are different
			 *
			 * @param other Iterator to check against
			 * @returns True if the given iterator does not point to the same element as this one, false if it does.
			 */
			bool operator!=(const Matrix_iterator& other){
			
			    return !(*this == other);
			}

		};
		//////////////////
		// MATRIX CONST ITERATOR CLASS
		//////////////////
		class Matrix_const_iterator : public Matrix_iterator{
		
		    public:
			using Matrix_iterator::Matrix_iterator;

			/**
			 * @brief Operator* for the Matrix_const_iterator class
			 *
			 * Returns the element currently pointed by the iterator as a const
			 * reference. If all elements have already been consumed an 
			 * ExpiredIteratorException will be throwed.
			 *
			 * @returns A const reference to the element pointed by the iterator
			 * @throws ExpiredIteratorException If the iterator is pointing to the terminal element of the Matrix.
			 */
			const scalar_type& operator*(){
			
			    return Matrix_iterator::operator*();
			}
		};
	};
	
	////////////////
	// OPERATOR PUT TO FOR THE MATRIX CLASS      
	////////////////
	/**
	 * @brief Overloading of operator<< for Matrix class
	 *
	 * The given Matrix is redirected to the given std::ostream
	 * between square brackets and using a semicolon and a newline
	 * between each row of the matrix.
	 *
	 * @param os The target std::ostream
	 * @param matrix The Matrix object to redirect
	 */
	template <typename T>
	std::ostream& operator<< ( std::ostream& os, const Matrix<T>& matrix){
	
	    os << "[ ";
	    size_t i = 0;
	    typename Matrix<T>::dimension dims = matrix.get_dimensions();
	    for (auto& x : matrix){
		os << x;
		if (++i % dims.second == 0 && i/dims.second != dims.first)
		    os << ";\n";
		else
		 os << " ";
	    }
	    os << "]";
	    return os;
	}
		
    }
}

#endif
