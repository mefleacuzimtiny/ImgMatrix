#ifndef MATRIX_CPP
#define MATRIX_CPP

#include <iostream>
#include <stdexcept>
#include "../include/matrix.h"


//========================================================== CONSTRUCTORS ==========================================================


// Default
template <typename T>
Matrix<T>::Matrix() : rows(1), cols(1) {
	contents = new T*[1];	// creating an array of pointers of size 1
	/* Below:
	setting the first pointer element to an arry of size 1 
	and initializing it to zero using round brackets i.e.
	the default constructor is called.
	*/
	contents[0] = new T[1]();
	
}

// Constructor
template <typename T>
Matrix<T>::Matrix(int r, int c) : rows(r), cols(c) {
	if (rows <= 0 || cols <= 0)
		throw std::invalid_argument("Matrix dimensions must be non zero and positive");
//	contents = new T[rows * cols] { 0 };
	
	contents = new T*[rows];
	for (int i=0; i < rows; i++) {
		contents[i] = new T[cols]();
	}
}

// Copy
template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) : rows(other.rows), cols(other.cols) {
//	contents = new T[rows * cols];
//	for (int i = 0; i < rows * cols; ++i)
//		contents[i] = other.contents[i];
	
	contents = new T*[rows];
	for (int i=0; i < rows; i++) {
		contents[i] = new T[cols];
	}
	
	for (int i=0; i < rows; i++) {
		for (int j=0; j < cols; j++) {
			contents[i][j] = other.contents[i][j];
		}
	}
}


template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init_list) : rows(init_list.size()) {
	if (rows == 0) throw std::invalid_argument("Matrix cannot have zero rows.");
	
	cols = init_list.begin()->size();
	
	contents = new T*[rows];
	
	int i = 0;
	for (const auto& row : init_list) {
		if (row.size() != cols) throw std::invalid_argument("Inconsistent row widths.");
		
		contents[i] = new T[cols];
		
		int j = 0;
		for (const auto& val : row) {
			contents[i][j] = val;
			j++;
		}
		i++;
	}
}

// Destructor
template <typename T>
Matrix<T>::~Matrix() {
//	delete[] contents;
	
	for (int i=0; i < rows; i++) {
		delete[] contents[i];
	}
	delete[] contents;
}

////////////////////////////////////////////////////////// CONSTRUCTORS END //////////////////////////////////////////////////////////



//========================================================== OPERATOR OVERLOADS ==========================================================


template <typename T>
void operator >> (std::istream& in, Matrix<T> mat) {
	for (int i=0; i < mat.rows; i++) {
		for (int j=0; j < mat.cols; j++) {
			in >> mat(i, j);
		}
	}
}

//=========================== Element Access ===========================


template <typename T>
T& Matrix<T>::operator () (int i, int j) {
	if (i < 0 || i >= rows || j < 0 || j >= cols)
		throw std::out_of_range("Index out of range");
	
	return contents[i][j];
//	return contents[i * cols + j];
}

template <typename T>
const T& Matrix<T>::operator () (int i, int j) const {
	if (i < 0 || i >= rows || j < 0 || j >= cols)
		throw std::out_of_range("Index out of range");
	
	return contents[i][j];
//	return contents[i * cols + j];
}

////////////////////////// Element Access END //////////////////////////




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
T dotProd(int m, Matrix<T>& mat1, int row, Matrix<T>& mat2, int col) {
	T sum = 0;
	for (int k = 0; k < m; ++k)
		sum += mat1(row, k) * mat2(k, col);
	return sum;
}



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



template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
	if (cols != other.rows)
		throw std::invalid_argument("Matrix dimensions incompatible for multiplication");
	
	Matrix<T> B(other.transpose());			// turns the second operand's columns into rows to be multiplied in place
	
	Matrix<T> result(rows, other.cols);
	for (int i = 0; i < result.rows; ++i) {			// for each row
		for (int j = 0; j < result.cols; ++j) {		// for each column
			result(i, j) = dotProd(cols, contents[i], B.contents[j]);	 // dot product of rows into columns
		}
	}
	return result;
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


////////////////////////////////////////////////////////// OPERATOR OVERLOADS END //////////////////////////////////////////////////////////


//========================================================== MISC FUNCTIONS ==========================================================


// Transpose
template <typename T>
Matrix<T> Matrix<T>::transpose() const {
	Matrix<T> result(cols, rows);
	
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			result(j, i) = (*this)(i, j);
	
	return result;
}

template <typename T>
int Matrix<T>::getRowCount() const {
	return rows;
}

template <typename T>
int Matrix<T>::getColCount() const {
	return cols;
}


// Print utility
template <typename T>
void Matrix<T>::print() const {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j)
			std::cout << std::setw(5) << (*this)(i, j) << " ";
		std::cout << "\n";
	}
}

////////////////////////////////////////////////////////// MISC FUNCTIONS END //////////////////////////////////////////////////////////

#endif
