#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>
#include <iomanip>

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
	~Matrix();
	
	T& operator()(int i, int j);
	const T& operator()(int i, int j) const;
	
	Matrix<T> operator+(const Matrix<T>& other) const;
	Matrix<T> operator-(const Matrix<T>& other) const;
	Matrix<T> operator-() const;
	Matrix<T> operator*(const Matrix<T>& other) const;
	Matrix<T> transpose() const;
	
	void print() const;
};

#endif
