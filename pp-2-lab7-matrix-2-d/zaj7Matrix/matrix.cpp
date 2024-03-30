#include <iostream>
#include <string>
#include <stdexcept> // std::out_of_range()
#include <iomanip>   // std::setw()

using namespace std;

#include "matrix.h"

#ifndef _MSC_FULL_VER // if not Visual Studio Compiler
    #warning "Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym"
#else
    #pragma message ("Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym")
#endif

TwoDimensionMatrix::TwoDimensionMatrix(){
    for (int i = 0; i<size_; i++){
        for (int j = 0; j<size_; j++){
            matrix_[i][j]=0;
        }
    }

};

TwoDimensionMatrix::TwoDimensionMatrix(const TwoDimensionMatrix &matrix){
    for (int i = 0; i<size_; i++){
        for (int j = 0; j<size_; j++){
            matrix_[i][j]=matrix.matrix_[i][j];
        }
    }
};

TwoDimensionMatrix::TwoDimensionMatrix(const MatrixElement matrix[size_][size_]){
    for (int i = 0; i<size_; i++) {
        for (int j = 0; j<size_; j++) {
            matrix_[i][j] = matrix[i][j];
        }
    }
};

int TwoDimensionMatrix::get(int row, int column) const{
    return matrix_[row][column];
}

const TwoDimensionMatrix& TwoDimensionMatrix::operator=(const TwoDimensionMatrix matrix){
    if (this != &matrix) {
        for (int i = 0; i < size_; i++) {
            for (int j = 0; j < size_; j++) {
                matrix_[i][j] = matrix.matrix_[i][j];
            }
        }
    }
    return *this;
}
MatrixElement* TwoDimensionMatrix::operator[](size_t i){
    return this->matrix_[i];
};

const MatrixElement* TwoDimensionMatrix::operator[](size_t i)const{
    return this->matrix_[i];
};

TwoDimensionMatrix operator+(const TwoDimensionMatrix& matrix1, const TwoDimensionMatrix& matrix2){
    TwoDimensionMatrix result;
    for (int i = 0; i < matrix1.size_ && i < matrix2.size_; i++) {
        for (int j = 0; j < matrix1.size_ && j < matrix2.size_; j++) {
            result.matrix_[i][j] = matrix1.matrix_[i][j]+matrix2.matrix_[i][j];
        }
    }
    return result;
};

TwoDimensionMatrix& TwoDimensionMatrix::operator*=(MatrixElement number){
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            matrix_[i][j] = matrix_[i][j] * number;
        }
    }
    return *this;
};

TwoDimensionMatrix TwoDimensionMatrix::operator&&(const TwoDimensionMatrix& matrix) const{
    TwoDimensionMatrix result;
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            if(matrix_[i][j] != 0 && matrix.matrix_[i][j] != 0){
                result.matrix_[i][j] = 1;
            }
            else{
                result.matrix_[i][j] = 0;
            }
        }
    }
    return result;
};

TwoDimensionMatrix::operator size_t()const{
    return size_;
};

ostream& operator<<(ostream& os, const TwoDimensionMatrix& matrix){
    for (int i = 0; i < matrix.size_; i++) {
        for (int j = 0; j < matrix.size_; j++){
        os << matrix.matrix_[i][j] << " ";
        }
    }
    return os;
};

istream& operator>>(istream& is, TwoDimensionMatrix& matrix){
    for (int i = 0; i < matrix.size_; i++) {
        for (int j = 0; j < matrix.size_; j++){
            is >> matrix.matrix_[i][j];
        }
    }
    return is;
};

