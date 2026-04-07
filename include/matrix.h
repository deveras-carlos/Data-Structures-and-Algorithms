#ifndef _MATRIX_H_
#define _MATRIX_H_

#ifdef _MATRIX_C_
#include "vector.h"
#include <stdlib.h>

typedef struct _matrix_{
    Vector* *rows;
    size_t row_count;
    size_t column_count;
} Matrix;

// Function prototypes for Matrix operations
Matrix* create_matrix( size_t row_count, size_t column_count );
void free_matrix( Matrix* matrix );
int set_matrix_element( Matrix* matrix, size_t row, size_t column, void* element );
void* get_matrix_element( Matrix* matrix, size_t row, size_t column );
size_t get_matrix_row_count( Matrix* matrix );
size_t get_matrix_column_count( Matrix* matrix );

Vector* get_matrix_row( Matrix* matrix, size_t row );
Vector* get_matrix_column( Matrix* matrix, size_t column );
Vector* get_matrix_diagonal( Matrix* matrix, size_t offset );
Vector* get_matrix_antidiagonal( Matrix* matrix, size_t offset );

Matrix* transpose_matrix( Matrix* matrix );
Matrix* add_matrices(
    Matrix* matrix_a, Matrix* matrix_b,
    long long int ( *add_func)(void*, void*)
);
Matrix* multiply_matrices(
    Matrix* matrix_a, Matrix* matrix_b,
    long long int ( *add_func)(void*, void*),
    long long int ( *mul_func)(void*, void*)
);
Matrix* scalar_multiply_matrix(
    Matrix* matrix, void* scalar,
    long long int ( *mul_func)(void*, void*)
);
Matrix* apply_function_to_matrix( Matrix* matrix, void* (*func)(void*) );
Matrix* map_matrix( Matrix* matrix, void* (*func)(void*) );

long long int determinant( Matrix* matrix );
Matrix* inverse_matrix( Matrix* matrix );
Matrix* power_matrix( Matrix* matrix, int exponent );

#else

extern Matrix* create_matrix( size_t row_count, size_t column_count );
extern void free_matrix( Matrix* matrix );
extern int set_matrix_element( Matrix* matrix, size_t row, size_t column, void* element );
extern void* get_matrix_element( Matrix* matrix, size_t row, size_t column );
extern size_t get_matrix_row_count( Matrix* matrix );
extern size_t get_matrix_column_count( Matrix* matrix );

extern Vector* get_matrix_row( Matrix* matrix, size_t row );
extern Vector* get_matrix_column( Matrix* matrix, size_t column );
extern Vector* get_matrix_diagonal( Matrix* matrix, size_t offset );
extern Vector* get_matrix_antidiagonal( Matrix* matrix, size_t offset );

extern Matrix* transpose_matrix( Matrix* matrix );
extern Matrix* add_matrices(
        Matrix* matrix_a, Matrix* matrix_b,
        long long int (*add_func)(void*, void*)
    );
extern Matrix* multiply_matrices(
        Matrix* matrix_a, Matrix* matrix_b,
        long long int (*add_func)(void*, void*),
        long long int (*mul_func)(void*, void*)
    );
extern Matrix* scalar_multiply_matrix(
        Matrix* matrix, void* scalar,
        long long int (*mul_func)(void*, void*)
    );
extern Matrix* apply_function_to_matrix( Matrix* matrix, void* ( *func )( void* ) );
extern Matrix* map_matrix(Matrix* matrix, void* ( *func )( void* ) );

extern long long int determinant( Matrix* matrix );
extern Matrix* inverse_matrix( Matrix* matrix );
extern Matrix* power_matrix( Matrix* matrix, int exponent );

#endif // _MATRIX_C_

#endif // _MATRIX_H_