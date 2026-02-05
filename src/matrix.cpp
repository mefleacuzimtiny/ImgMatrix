#ifndef MATRIX_CPP
#define MATRIX_CPP


#include <iostream>
#include <stdexcept>
#include "../include/matrix.h"

// Constructor
template <typename T>
Matrix<T>::Matrix(int r, int c) : rows(r), cols(c) {
	if (rows <= 0 || cols <= 0)
		throw std::invalid_argument("Matrix dimensions must be positive");
	contents = new T[rows * cols]{};
}

// Copy constructor
template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) : rows(other.rows), cols(other.cols) {
	contents = new T[rows * cols];
	for (int i = 0; i < rows * cols; ++i)
		contents[i] = other.contents[i];
}

// Destructor
template <typename T>
Matrix<T>::~Matrix() {
	delete[] contents;
}

// Element access
template <typename T>
T& Matrix<T>::operator()(int i, int j) {
	if (i < 0 || i >= rows || j < 0 || j >= cols)
		throw std::out_of_range("Index out of range");
	return contents[i * cols + j];
}

template <typename T>
const T& Matrix<T>::operator()(int i, int j) const {
	if (i < 0 || i >= rows || j < 0 || j >= cols)
		throw std::out_of_range("Index out of range");
	return contents[i * cols + j];
}

// Addition
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
	if (rows != other.rows || cols != other.cols)
		throw std::invalid_argument("Matrix dimensions must match for addition");
	
	Matrix<T> result(rows, cols);
	for (int i = 0; i < rows * cols; ++i)
		result.contents[i] = contents[i] + other.contents[i];
	return result;
}

// Subtraction
template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
	if (rows != other.rows || cols != other.cols)
		throw std::invalid_argument("Matrix dimensions must match for subtraction");
	
	Matrix<T> result(rows, cols);
	for (int i = 0; i < rows * cols; ++i)
		result.contents[i] = contents[i] - other.contents[i];
	return result;
}

// Multiplication
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
	if (cols != other.rows)
		throw std::invalid_argument("Matrix dimensions incompatible for multiplication");
	
	Matrix<T> result(rows, other.cols);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < other.cols; ++j) {
			T sum = 0;
			for (int k = 0; k < cols; ++k)
				sum += (*this)(i, k) * other(k, j);
			result(i, j) = sum;
		}
	}
	return result;
}

// Transpose
template <typename T>
Matrix<T> Matrix<T>::transpose() const {
	Matrix<T> result(cols, rows);
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			result(j, i) = (*this)(i, j);
	return result;
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

#endif
