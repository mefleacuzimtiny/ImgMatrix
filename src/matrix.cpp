//todo: make the matrix be instantiable from a raw string

#ifndef MATRIX_CPP
#define MATRIX_CPP

#include <iostream>
#include <stdexcept>
#include "../include/matrix.h"


//========================================================== CONSTRUCTORS ==========================================================

// Default
template <typename T>
Matrix<T>::Matrix() : rows(1), cols(1) {
	// initializing the 2D array
	contents = new T*[1];	// creating an array of pointers of size 1
	/* Below:
	setting the first pointer element to an arry of size 1 
	and initializing it to zero using round brackets i.e.
	the element's type's default constructor is called.
	*/
	contents[0] = new T[1]();
	
	// initializing the vector
	data.resize(rows);
	for (auto& row : data) {
		row.resize(cols, 0);
	}
	
	// initializing the 1D array
	elements = new T[1] { 0 };
}

// Constructor
template <typename T>
Matrix<T>::Matrix(int r, int c) : rows(r), cols(c) {
	if (rows <= 0 || cols <= 0)
		throw std::invalid_argument("Matrix dimensions must be non zero and positive");
	
	// initializing the 2D array
	contents = new T*[rows];
	for (int i=0; i < rows; i++) {
		contents[i] = new T[cols]();
	}
	
	// initializing the vector
	data.resize(rows);
	for (auto& row : data) {
		row.resize(cols, 0);
	}
	
	//initializing the 1D array
	elements = new T[rows * cols] { 0 };
}

// Copy
template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) : rows(other.rows), cols(other.cols) {
	
	// initializing the 2D array:
	contents = new T*[rows];
	for (int i=0; i < rows; i++) {
		contents[i] = new T[cols];
	}
	for (int i=0; i < rows; i++) {
		for (int j=0; j < cols; j++) {
			contents[i][j] = other.contents[i][j];
		}
	}
	
	//initializing the vector:
//	data.resize(rows);
//	for (auto& row : data) {
//		row.resize(cols, 0);
//	}
	data = other.data;

	// initializing the 1D array:
	elements = new T[rows * cols];
	for (int i = 0; i < rows * cols; ++i)
		elements[i] = other.elements[i];
}


//template <typename T>
//Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init_list) : rows(init_list.size()) {
//	if (rows == 0) throw std::invalid_argument("Matrix cannot have zero rows.");
//	
//	cols = init_list.begin()->size();
//	
//	contents = new T*[rows];
//	
//	int i = 0;
//	for (const auto& row : init_list) {
//		if (row.size() != cols) throw std::invalid_argument("Inconsistent row widths.");
//		
//		contents[i] = new T[cols];
//		
//		int j = 0;
//		for (const auto& val : row) {
//			contents[i][j] = val;
//			j++;
//		}
//		i++;
//	}
//}


template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init_list) : rows(init_list.size()) {
	if (rows == 0) throw std::invalid_argument("Matrix cannot have zero rows.");
	
	// Set the number of columns (using the first row's size)
	cols = init_list.begin()->size();
	
	// 2D Array initialization (like your other constructors)
	contents = new T*[rows];
	for (int i = 0; i < rows; i++) {
		contents[i] = new T[cols]();  // Initialize each row with default values
	}
	
	// Vector initialization (like your other constructors)
	data.resize(rows);
	for (auto& row : data) {
		row.resize(cols, 0);  // Initialize each row with zero
	}
	
	// 1D Array initialization (like your other constructors)
	elements = new T[rows * cols]();  // Initialize all elements to zero
	
	// Copy the values from the initializer list into all three storage methods
	int i = 0;
	for (const auto& row : init_list) {
		if (row.size() != cols) throw std::invalid_argument("Inconsistent row widths.");
		
		// Fill the 2D array
		for (int j = 0; j < cols; j++) {
			contents[i][j] = row.begin()[j];  // Copy value into the 2D array
		}
		
		// Fill the vector
		for (int j = 0; j < cols; j++) {
			data[i][j] = row.begin()[j];  // Copy value into the vector
		}
		
		// Fill the 1D array
		for (int j = 0; j < cols; j++) {
			elements[i * cols + j] = row.begin()[j];  // Copy value into the 1D array
		}
		i++;
	}
}

// Destructor
template <typename T>
Matrix<T>::~Matrix() {
	
	// cleaning 2D array
	for (int i=0; i < rows; i++) {
		delete[] contents[i];
	}
	delete[] contents;
	
	// cleaning vector:
	// nothing needed here
	
	// cleaning 1D array;
	delete[] elements;
}

////////////////////////////////////////////////////////// CONSTRUCTORS END //////////////////////////////////////////////////////////



//========================================================== OPERATOR OVERLOADS ==========================================================


//=========================== Stream Operators ===========================
//template <typename T>
//void operator >> (std::istream& in, Matrix<T> mat) {
//	for (int i=0; i < mat.rows; i++) {
//		for (int j=0; j < mat.cols; j++) {
//			in >> mat(i, j);
//		}
//	}
//}
////////////////////////// Stream Operators END //////////////////////////

//=========================== Element Access ===========================


template <typename T>
T& Matrix<T>::operator () (int i, int j) {
	if (i < 0 || i >= rows || j < 0 || j >= cols)
		throw std::out_of_range("Index out of range");
	
	//	return contents[i][j];
	//	return data[i][j];
	return elements[i * cols + j];
}

template <typename T>
const T& Matrix<T>::operator () (int i, int j) const {
	if (i < 0 || i >= rows || j < 0 || j >= cols)
		throw std::out_of_range("Index out of range");
	
	//	return contents[i][j];
	//	return data[i][j];
	return elements[i * cols + j];
}

////////////////////////// Element Access END //////////////////////////


//=========================== Arithmetic Operators ===========================


// Addition
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
	if (rows != other.rows || cols != other.cols)
		throw std::invalid_argument("Matrix dimensions must match for addition");
	
	Matrix<T> result(rows, cols);
//	for (int i = 0; i < rows * cols; ++i)
//		result.contents[i] = contents[i] + other.contents[i];
	for (int i=0; i < rows; i++) {
		for (int j=0; j < cols; j++) {
			result(i, j) = (*this)(i, j) + other(i, j);
		}
	}
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const T scalar) const {
	Matrix<T> result(rows, cols);
	for (int i=0; i < rows; i++) {
		for (int j=0; j < cols; j++) {
			result(i, j) = (*this)(i, j) + scalar;
		}
	}
	return result;
}

// Subtraction
template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
	if (rows != other.rows || cols != other.cols)
		throw std::invalid_argument("Matrix dimensions must match for subtraction");
	
	Matrix<T> result(rows, cols);
	//for (int i = 0; i < rows * cols; ++i)
	//	result.contents[i] = contents[i] - other.contents[i];
	for (int i=0; i < rows; i++) {
		for (int j=0; j < cols; j++) {
			result(i, j) = (*this)(i, j) - other(i, j);
		}
	}
	
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const T scalar) const {
	Matrix<T> result(rows, cols);
	for (int i=0; i < rows; i++) {
		for (int j=0; j < cols; j++) {
			result(i, j) = (*this)(i, j) - scalar;
		}
	}
	return result;
}

// Negation
template <typename T>
Matrix<T> Matrix<T>::operator-() const {
	Matrix<T> result(rows, cols);
	//for (int i = 0; i < rows * cols; ++i)
	//	result.contents[i] = -contents[i];
	
	for (int i=0; i < rows; i++) {
		for (int j=0; j < cols; j++) {
		//	result.contents[i][j] = -contents[i][j];
			result(i, j) = -(*this)(i, j);
		}
	}
	
	return result;
}

// Multiplication


template <typename T>
T dotProd(int m, T* rowvect, T* colvect) {
	T sum = 0;
	for (int k = 0; k < m; ++k)
		sum += rowvect[k] * colvect[k];
	return sum;
}
template <typename T>
T dotProd(int m, const Matrix<T>& mat1, int row, const Matrix<T>& mat2, int col) {
	T sum = 0;
	for (int k = 0; k < m; ++k)
		sum += mat1(row, k) * mat2(k, col);
	return sum;
}




template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
	if (cols != other.rows)
		throw std::invalid_argument("Matrix dimensions incompatible for multiplication");
	
	Matrix<T> B(other.transpose());			// turns the second operand's columns into rows to be multiplied in place
	
	Matrix<T> result(rows, other.cols);
	for (int i = 0; i < result.rows; ++i) {			// for each row
		for (int j = 0; j < result.cols; ++j) {		// for each column
//			result(i, j) = dotProd(cols, contents[i], B.contents[j]);	 // dot product of rows into columns
			// when implementing via vectors or other technique, use this:
			result(i, j) = dotProd(cols, *this, i, other, j);	 // dot product alternative if performance was needed without the initial transpose
		}
	}
	return result;
}


void foldedComment() {/*  Just a large comment I wanted to put in a foldable block so it doesn't distract me
//template <typename T>
//Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
//	if (cols != other.rows)
//		throw std::invalid_argument("Matrix dimensions incompatible for multiplication");
//	
//	Matrix<T> B(other.transpose());			// turns the second operand's columns into rows to be multiplied in place
//	
//	Matrix<T> result(rows, other.cols);
//	for (int i = 0; i < result.rows; ++i) {			// for each row
//		for (int j = 0; j < result.cols; ++j) {		// for each column
//			T sum = 0;
//			for (int k = 0; k < cols; ++k)
//				sum += (*this)(i, k) * other(k, j);
//			result(i, j) = sum;
//			// result(i, j) = dotProd(cols, *this, i, other, j);	 // dot product alternative if performance was needed without the initial transpose
//		}
//	}
//	return result;
//}
*/
}


template <typename T>
Matrix<T> Matrix<T>::operator*(float s) const {
	
	Matrix<T> result(*this);
	for (int i=0; i < rows; i++) {
		for (int j=0; j < cols; j++) {
			result(i, j) = s * (*this)(i, j);
		}
	}
	return result;
}


template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
	if (this == &other) return *this; // Self-assignment check
	
	// 1. Clean up old memory (mirror your destructor)
	for (int i = 0; i < rows; i++) delete[] contents[i];
	delete[] contents;
	delete[] elements;
	
	// 2. Re-allocate and copy (mirror your copy constructor)
	rows = other.rows;
	cols = other.cols;
	
	
	// copying the 2D array:
	contents = new T*[rows];
	for (int i=0; i < rows; i++) {
		contents[i] = new T[cols];
	}
	for (int i=0; i < rows; i++) {
		for (int j=0; j < cols; j++) {
			contents[i][j] = other.contents[i][j];
		}
	}
	
	// copying the vector:
	data = other.data;
	
	// copying the 1D array:
	elements = new T[rows * cols];
	for (int i = 0; i < rows * cols; ++i)
		elements[i] = other.elements[i];
	
	return *this;
}
////////////////////////// Arithmetic Operators END //////////////////////////


////////////////////////////////////////////////////////// OPERATOR OVERLOADS END //////////////////////////////////////////////////////////


//========================================================== MISC FUNCTIONS ==========================================================

//=========================== Matrix Operations without Sybmols ===========================

// Transpose
template <typename T>
Matrix<T> Matrix<T>::transpose() const {
	Matrix<T> result(cols, rows);
	
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			result(j, i) = (*this)(i, j);
	
	return result;
}
////////////////////////// Matrix Operations without Sybmols END //////////////////////////

//=========================== Data Getters ===========================

template <typename T>
int Matrix<T>::getRowCount() const {
	return rows;
}

template <typename T>
int Matrix<T>::getColCount() const {
	return cols;
}
////////////////////////// Data Getters END //////////////////////////


//=========================== Logging Functions ===========================

// Print utility
template <typename T>
void Matrix<T>::print() const {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j)
//			std::cout << std::setw(5) << (*this)(i, j) << " ";
			std::cout << std::setw(5) << (*this)(i, j) << " ";
		std::cout << "\n";
	}
}

template <typename T>
template <typename U>
void Matrix<T>::printAs() const {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j)
			std::cout << std::setw(5) << static_cast<U>((*this)(i, j)) << " ";
		std::cout << "\n";
	}
}
////////////////////////// Logging Functions END //////////////////////////

////////////////////////////////////////////////////////// MISC FUNCTIONS END //////////////////////////////////////////////////////////

#endif
