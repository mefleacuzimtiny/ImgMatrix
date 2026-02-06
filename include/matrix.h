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
	
public:
	Matrix();
	Matrix(int rows, int cols);
	Matrix(const Matrix<T>& other);
	Matrix<T>(std::initializer_list<std::initializer_list<T>> init_list);
	
	~Matrix();
	
	friend void operator >> (std::istream& in, Matrix<T>& mat) {
		for (int i=0; i < mat.rows; i++) {
			for (int j=0; j < mat.cols; j++) {
				in >> mat(i, j);
			}
		}
	}
	
	
	T& operator()(int i, int j);

	const T& operator()(int i, int j) const;
	Matrix<T> operator+(const Matrix<T>& other) const;
	Matrix<T> operator-(const Matrix<T>& other) const;
	Matrix<T> operator-() const;
	Matrix<T> operator*(const Matrix<T>& other) const;
	Matrix<T> operator*(float s) const;
	
	friend Matrix<T> operator*(float s, Matrix<T>& mat) {
		return mat * s;
	}
	
	Matrix<T> transpose() const;
	int getRowCount() const;
	int getColCount() const;
	
	void print() const;
};


#include "../src/matrix.cpp"
#endif
