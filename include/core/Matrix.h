#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <stdexcept> 


class Matrix {
    /*
    Define Matrix in continuous array 
    */

    private: 
        std::size_t n_cols; 
        std::size_t n_rows; 
        double* data; 
    
    public: 
        // Matrix(); 
        Matrix(std::size_t n_rows, std::size_t n_cols); 
        Matrix(std::size_t n_rows, std::size_t n_cols, double fill); 
        Matrix(const Matrix& other); 
        ~Matrix(); 

        // Getters/setters
        std::size_t get_rows() const {return this->n_rows;} 
        std::size_t get_cols() const {return this->n_cols;}
        double& operator()(std::size_t i, std::size_t j) {
            // Non const version for value modification
            return data[i * this->n_cols + j];
        }
        const double& operator()(std::size_t i, std::size_t j) const {
            // Const version just for getting value
            return data[i * this->n_cols + j];
        }

        // Matrix operations 
        Matrix* operator+(const Matrix& other); 
        bool operator!=(const Matrix& other); 
        Matrix* hadamard(const Matrix& other); 

        // Friend functions 
        friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
}; 


#endif 