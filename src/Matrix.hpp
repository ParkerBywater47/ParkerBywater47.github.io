#include <iostream>
using namespace std;

class Matrix {
    private:
        int num_rows_;
        int num_cols_;
        double ** data;
        void initialize_data(double * ptr_to_first); 

    public:
        Matrix(int num_rows, int num_cols);
        Matrix(int num_rows, int num_cols, double * ptr_to_first);
	Matrix(const Matrix& mat); 
        ~Matrix(); 

        const int get_num_rows();
        const int get_num_cols(); 
        void swap_rows(int, int); 

        void print();
        double * operator[](int i);
};
