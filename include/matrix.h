#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <vector>

//template <typename T>
//class Matrix {
//protected:
//	int rows;
//	int cols;
//	
//private:
//	T* contents;
//	
//public:
//	Matrix();
//	Matrix(int rows, int cols);
//	Matrix(const Matrix<T>& other);
//	~Matrix();
//	
//	T& operator()(int i, int j);
//	const T& operator()(int i, int j) const;
//	
//	Matrix<T> operator+(const Matrix<T>& other) const;
//	Matrix<T> operator-(const Matrix<T>& other) const;
//	Matrix<T> operator-() const;
//	Matrix<T> operator*(const Matrix<T>& other) const;
//	Matrix<T> transpose() const;
//	
//	void print() const;
//};


template <typename T>
class Matrix {
protected:
	int rows;
	int cols;
	
private:
	T** contents;
	std::vector<std::vector<T>> data;
	T* elements;
	
public:
	Matrix();
	Matrix(int rows, int cols);
	Matrix(const Matrix<T>& other);
	Matrix(std::initializer_list<std::initializer_list<T>> init_list);
	
	~Matrix();
	
	friend std::istream& operator >> (std::istream& in, Matrix<T>& mat);
	
	T& operator()(int i, int j);

	const T& operator()(int i, int j) const;
	Matrix operator+(const Matrix<T>& other) const;
	Matrix operator+(const T scalar) const;
	Matrix operator-(const Matrix<T>& other) const;
	Matrix operator-(const T scalar) const;
	Matrix operator-() const;
	Matrix operator*(const Matrix<T>& other) const;
	Matrix operator*(const float scalar) const;
	Matrix& operator=(const Matrix<T>& other);
	
	friend Matrix<T> operator*(const float scalar, const Matrix<T>& mat) {
		return mat * scalar;
	}
	friend Matrix<T> operator-(const T scalar, const Matrix<T>& mat) {		// ig not "mathematical", so to speak but for images, quite convenient
//		return -mat + scalar;
		Matrix<T> result(mat.rows, mat.cols);
		for (int i=0; i < mat.rows; i++) {
			for (int j=0; j < mat.cols; j++) {
				result(i, j) = scalar - mat(i, j);
			}
		}
		return result;
	}
	friend Matrix<T> operator+(const T scalar, const Matrix<T>& mat) {		// ig not "mathematical", so to speak but for images, quite convenient
		return mat + scalar;
	}
	
	Matrix transpose() const;
	int getRowCount() const;
	int getColCount() const;
	
	void print() const;
	
	template <typename U>
	void printAs() const;
};


#include "../src/matrix.cpp"
#endif
