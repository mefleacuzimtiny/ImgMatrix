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
	Matrix(std::initializer_list<std::initializer_list<T>> init_list);
	
	~Matrix();
	
	friend std::istream& operator >> (std::istream& in, Matrix<T>& mat);
	
	T& operator()(int i, int j);

	const T& operator()(int i, int j) const;
	Matrix operator+(const Matrix<T>& other) const;
	Matrix operator-(const Matrix<T>& other) const;
	Matrix operator-() const;
	Matrix operator*(const Matrix<T>& other) const;
	Matrix operator*(float s) const;
	
	friend Matrix<T> operator*(float s, const Matrix<T>& mat) {
		return mat * s;
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
