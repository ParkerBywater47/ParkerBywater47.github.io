#include "Matrix.hpp"
#include <omp.h>
#include <iostream>

// 
// Constructor for creating an "empty" matrix. Item assignment can then be used to 
// fill the matrix with the appropriate data
//
Matrix::Matrix(int num_rows, int num_cols): num_rows_(num_rows), num_cols_(num_cols)
{  
    this->data = new double*[num_rows_] ;
    for (int i = 0; i < num_rows_; i++)
    {
        this->data[i] = new double[num_cols_]; 
    } 
}

//
// Constructor for creating a matrix whose data is already stored in a contiguous block of memory 
// (an array) elsewhere. This block must be contiguous as the initialize_data method does the pointer 
// arithmetic under this assumption. 
//
Matrix::Matrix(int num_rows, int num_cols, double * ptr_to_first): num_rows_(num_rows), num_cols_(num_cols)
{
    initialize_data(ptr_to_first); 
}

// 
// Destructor. Just deallocates memory
//
Matrix::~Matrix() {
    for (int i = 0; i < num_rows_; i++)
    {
        delete[] data[i]; 
    }
    delete[] data; 
}

// 
// Copy constructor
//
Matrix::Matrix(const Matrix& mat) {
    num_rows_ = mat.num_rows_;
    num_cols_ = mat.num_cols_; 
    this->data = new double*[mat.num_rows_]; 
    #pragma omp parallel for
    for (int i = 0; i < num_rows_; i++)
    {
        this->data[i] = new double[mat.num_cols_];
        for (int j = 0; j < num_cols_; j++) {
            data[i][j] = mat.data[i][j];
        }
    }
}

int Matrix::get_num_rows() const {
    return num_rows_;
}

int Matrix::get_num_cols() const {
    return this->num_cols_; 
}

void Matrix::initialize_data(double * ptr_to_first) {

    this->data = new double*[num_rows_];
    for (int i = 0; i < num_rows_; i++)
    {
        this->data[i] = new double[num_cols_];
        for (int j = 0; j < num_cols_; j++)
        {
            data[i][j] = *(ptr_to_first + (i*num_rows_) + j);
        }
    }
}

void Matrix::swap_rows(const int i, const int j) {
    double * temp = data[j];
    data[j] = data[i];
    data[i] = temp;
}

double * Matrix::operator[](int i) {
    return data[i]; 
}

const double * Matrix::operator[](int i) const {
    return data[i]; 
}

void Matrix::print()
{
    for (int i = 0; i < this->num_rows_; i++)
    {
        for (int j = 0; j < this->num_cols_; j++)
            printf("%14.4f", data[i][j]);
        std::cout << std::endl;
    }
}

