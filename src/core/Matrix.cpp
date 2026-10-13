#include "core/Matrix.h"

Matrix::Matrix(std::size_t n_rows, std::size_t n_cols) {
    // Instanciate empty matrix with given dimensions. 
    this->n_cols = n_cols; 
    this->n_rows = n_rows; 
    this->data = new double[n_cols * n_rows]; 
}

Matrix::Matrix(std::size_t n_rows, std::size_t n_cols, double fill) {
    // Instanciate empty matrix with given dimensions and value
    this->n_cols = n_cols; 
    this->n_rows = n_rows; 
    this->data = new double[n_cols * n_rows]; 
    // Init values 
    for (std::size_t i = 0; i < this->n_cols * this->n_rows; i++) {
        this->data[i] = fill; 
    }
}

Matrix::Matrix(const Matrix& other) {
    // Copy constructor
    this->n_cols = other.n_cols; 
    this->n_rows = other.n_rows; 
    this->data = new double[n_cols * n_rows]; 
    // Deep-copy 
    for (std::size_t i = 0; i < this->n_cols * this->n_rows; i++) {
        this->data[i] = other.data[i]; 
    }
}

Matrix::~Matrix() {
    // Destructor 
    delete[] this->data; 
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    // Save local state
    std::ios_base::fmtflags original_flags = os.flags();
    
    // Set a fix width
    const std::size_t col_width = 10;
    os << std::fixed << std::setprecision(2);

    for (std::size_t i = 0; i < mat.get_rows(); ++i) {
        os << "[ ";
        for (std::size_t j = 0; j < mat.get_cols(); ++j) {
            os << std::setw(col_width) << mat(i, j) << " ";
        }
        os << "]\n";
    }

    os.flags(original_flags);
    return os;
}

Matrix* Matrix::operator+(const Matrix& other) {
    // Add two matrix 
    // Check matrix dimensions first 
    if (this->n_cols != other.get_cols() || this->n_rows != other.n_rows) {
        throw std::invalid_argument("Unable to add two matrix with different shapes."); 
    }
    // Create the new matrix with same shape 
    Matrix* m = new Matrix(this->n_rows, this->n_cols); 
    // Fill-in the matrix 
    for (std::size_t i = 0; i < this->n_rows; i++) {
        for (std::size_t j = 0; j < this->n_cols; j++) {
            (*m)(i,j) = this->data[i * this->n_cols + j] + other(i,j); 
        }
        
    }
    return m; 
}

bool Matrix::operator!=(const Matrix& other) {
    // Compare the two matrix 
    if (this->n_cols != other.get_cols() || this->n_rows != other.n_rows) {
        return true; 
    }
    for (std::size_t i = 0; i < this->n_rows; i++) {
        for (std::size_t j = 0; j < this->n_cols; j++) {
            if ((*this)(i,j) != other(i,j)) {
                return true; 
            }
        }
    }
    return false; 
}

Matrix* Matrix::hadamard(const Matrix& other) {
    // Check matrix dimensions first 
    if (this->n_cols != other.get_cols() || this->n_rows != other.n_rows) {
        throw std::invalid_argument("Unable to multiply with Hadamard two matrix with different shapes."); 
    }
    // Create the new matrix with same shape 
    Matrix* m = new Matrix(this->n_rows, this->n_cols); 
    // Fill-in the matrix 
    for (std::size_t i = 0; i < this->n_rows; i++) {
        for (std::size_t j = 0; j < this->n_cols; j++) {
            (*m)(i,j) = this->data[i * this->n_cols + j] * other(i,j); 
        }
        
    }
    return m; 
}

