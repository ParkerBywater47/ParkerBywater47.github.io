#ifndef MATRIX_H
#define MATRIX_H


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

        int get_num_rows() const;
        int get_num_cols() const; 
        void swap_rows(int, int); 

        void print();
        double * operator[](int i);
};


#endif
