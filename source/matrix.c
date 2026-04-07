#ifndef _MATRIX_C_
#define _MATRIX_C_

#include "matrix.h"
#include <stdlib.h>

Matrix* create_matrix( size_t row_count, size_t column_count ){
    if ( row_count == 0 || column_count == 0 ) {
        return NULL; // Invalid matrix dimensions
    }
    Matrix* matrix = ( Matrix* )malloc( sizeof( Matrix ) );
    if ( !matrix ) {
        return NULL; // Memory allocation failed
    }
    matrix->row_count = row_count;
    matrix->column_count = column_count;
    matrix->rows = ( Vector* )malloc( row_count * size_of_vector(  ) );
    if ( !matrix->rows ) {
        free( matrix );
        return NULL; // Memory allocation failed
    }

    for ( size_t i = 0; i < row_count; i++ ) {
        matrix->rows[ i ] = create_vector( column_count );
        if ( !matrix->rows[ i ] ) {
            for ( size_t j = 0; j < i; j++ ) {
                free_vector( matrix->rows[ j ] );
            }
            free( matrix->rows );
            free( matrix );
            return NULL; // Memory allocation failed
        }
    }
    return matrix;

}

void free_matrix( Matrix* matrix ){
    if ( matrix ) {
        for ( size_t i = 0; i < matrix->row_count; i++ ) {
            free_vector( matrix->rows[ i ] );
        }
        free( matrix->rows );
        free( matrix );
    }
}

int set_matrix_element( Matrix* matrix, size_t row, size_t column, void* element ){
    if ( !matrix || row >= matrix->row_count || column >= matrix->column_count ) {
        return -1; // Invalid matrix or out of bounds
    }
    return vector_set_element( matrix->rows[ row ], column, element );
}

void* get_matrix_element( Matrix* matrix, size_t row, size_t column ){
    if ( !matrix || row >= matrix->row_count || column >= matrix->column_count ) {
        return NULL; // Invalid matrix or out of bounds
    }
    return get_vector_element( matrix->rows[ row ], column );
}

size_t get_matrix_row_count( Matrix* matrix ){
    if ( !matrix ) {
        return 0; // Invalid matrix
    }
    return matrix->row_count;
}

size_t get_matrix_column_count( Matrix* matrix ){
    if ( !matrix ) {
        return 0; // Invalid matrix
    }
    return matrix->column_count;
}


Vector* get_matrix_row( Matrix* matrix, size_t row ){
    if ( !matrix || row >= matrix->row_count ) {
        return NULL; // Invalid matrix or out of bounds
    }
    return matrix->rows[ row ];
}

Vector* get_matrix_column( Matrix* matrix, size_t column ){
    if ( !matrix || column >= matrix->column_count ) {
        return NULL; // Invalid matrix or out of bounds
    }

    Vector* column_vector = create_vector( matrix->row_count );
    if ( !column_vector ) {
        return NULL; // Memory allocation failed
    }
    for ( size_t i = 0; i < matrix->row_count; i++ ) {
        void* element = get_vector_element( matrix->rows[ i ], column );
        if ( vector_push_back( column_vector, element ) != 0 ) {
            free_vector( column_vector );
            return NULL; // Memory allocation failed
        }
    }
    return column_vector;
}

Vector* get_matrix_diagonal( Matrix* matrix, size_t offset ){
    if ( !matrix ) {
        return NULL; // Invalid matrix
    }
    
    size_t diagonal_length = 0;
    if ( offset >= 0 ) {
        diagonal_length = ( matrix->row_count < matrix->column_count - offset ) ? matrix->row_count : ( matrix->column_count - offset );
    } else {
        diagonal_length = ( matrix->row_count + offset < matrix->column_count ) ? ( matrix->row_count + offset ) : matrix->column_count;
    }
    Vector* diagonal_vector = create_vector( diagonal_length );
    if ( !diagonal_vector ) {
        return NULL; // Memory allocation failed
    }
    for ( size_t i = 0; i < diagonal_length; i++ ) {
        size_t row = ( offset >= 0 ) ? i : ( i - offset );
        size_t column = ( offset >= 0 ) ? ( i + offset ) : i;
        void* element = get_vector_element( matrix->rows[ row ], column );
        if (vector_push_back( diagonal_vector, element ) != 0 ) {
            free_vector( diagonal_vector );
            return NULL; // Memory allocation failed
        }
    }
    return diagonal_vector;
}
    
Vector* get_matrix_antidiagonal( Matrix* matrix, size_t offset ){
    if ( !matrix ) {
        return NULL; // Invalid matrix
    }
    // Implementation for getting an antidiagonal vector
    size_t antidiagonal_length = 0;
    if ( offset >= 0 ) {
        antidiagonal_length = ( matrix->row_count < matrix->column_count - offset ) ? matrix->row_count : ( matrix->column_count - offset );
    } else {
        antidiagonal_length = ( matrix->row_count + offset < matrix->column_count ) ? ( matrix->row_count + offset ) : matrix->column_count;
    }
    Vector* antidiagonal_vector = create_vector( antidiagonal_length );
    if ( !antidiagonal_vector ) {
        return NULL; // Memory allocation failed
    }
    for ( size_t i = 0; i < antidiagonal_length; i++ ) {
        size_t row = ( offset >= 0 ) ? i : ( i - offset );
        size_t column = ( offset >= 0 ) ? ( matrix->column_count - 1 - i - offset ) : ( matrix->column_count - 1 - i );
        void* element = get_vector_element( matrix->rows[ row ], column );
        if ( vector_push_back( antidiagonal_vector, element ) != 0 ) {
            free_vector( antidiagonal_vector );
            return NULL; // Memory allocation failed
        }
    }
    return antidiagonal_vector;
}


Matrix* transpose_matrix( Matrix* matrix ){
    if ( !matrix ) {
        return NULL; // Invalid matrix
    }
    Matrix* transposed = create_matrix( matrix->column_count, matrix->row_count );
    if ( !transposed ) {
        return NULL; // Memory allocation failed
    }
    for ( size_t i = 0; i < matrix->row_count; i++ ) {
        for ( size_t j = 0; j < matrix->column_count; j++ ) {
            void* element = get_vector_element( matrix->rows[ i ], j );
            if (set_matrix_element( transposed, j, i, element ) != 0 ) {
                free_matrix( transposed );
                return NULL; // Memory allocation failed
            }
        }
    }
    return transposed;
}

Matrix* add_matrices(
    Matrix* matrix_a, Matrix* matrix_b,
    long long int (*add_func)(void*, void*)
){
    if ( !matrix_a || !matrix_b || !add_func ) {
        return NULL; // Invalid input
    }
    if ( matrix_a->row_count != matrix_b->row_count || matrix_a->column_count != matrix_b->column_count ) {
        return NULL; // Incompatible matrix dimensions
    }
    Matrix* result = create_matrix( matrix_a->row_count, matrix_a->column_count );
    if ( !result ) {
        return NULL; // Memory allocation failed
    }
    for ( size_t i = 0; i < matrix_a->row_count; i++ ) {
        for ( size_t j = 0; j < matrix_a->column_count; j++ ) {
            void* element_a = get_vector_element( matrix_a->rows[ i ], j );
            void* element_b = get_vector_element( matrix_b->rows[ i ], j );
            long long int sum = add_func( element_a, element_b );
            if (set_matrix_element( result, i, j, (void*)sum ) != 0) {
                free_matrix(result);
                return NULL; // Memory allocation failed
            }
        }
    }
    return result;
}

Matrix* multiply_matrices(
    Matrix* matrix_a, Matrix* matrix_b,
    long long int (*add_func)(void*, void*),
    long long int (*mul_func)(void*, void*)
){
    if ( !matrix_a || !matrix_b || !add_func || !mul_func ) {
        return NULL; // Invalid input
    }
    if ( matrix_a->column_count != matrix_b->row_count ) {
        return NULL; // Incompatible matrix dimensions
    }
    Matrix* result = create_matrix( matrix_a->row_count, matrix_b->column_count );
    if ( !result ) {
        return NULL; // Memory allocation failed
    }
    for ( size_t i = 0; i < matrix_a->row_count; i++ ) {
        for ( size_t j = 0; j < matrix_b->column_count; j++ ) {
            long long int sum = 0;
            for ( size_t k = 0; k < matrix_a->column_count; k++ ) {
                void* element_a = get_vector_element( matrix_a->rows[ i ], k );
                void* element_b = get_vector_element( matrix_b->rows[ k ], j );
                sum = add_func( (void*)sum, (void*)mul_func( element_a, element_b ) );
            }
            if (set_matrix_element( result, i, j, (void*)sum ) != 0) {
                free_matrix( result );
                return NULL; // Memory allocation failed
            }
        }
    }
    return result;
}

Matrix* scalar_multiply_matrix(
    Matrix* matrix, void* scalar,
    long long int ( *mul_func )( void*, void* )
){
    if ( !matrix || !scalar || !mul_func ) {
        return NULL; // Invalid input
    }
    Matrix* result = create_matrix( matrix->row_count, matrix->column_count );
    if ( !result ) {
        return NULL; // Memory allocation failed
    }
    for ( size_t i = 0; i < matrix->row_count; i++ ) {
        for ( size_t j = 0; j < matrix->column_count; j++ ) {
            void* element = get_vector_element( matrix->rows[ i ], j );
            long long int product = mul_func( element, scalar );
            if (set_matrix_element( result, i, j, (void*)product ) != 0) {
                free_matrix( result );
                return NULL; // Memory allocation failed
            }
        }
    }
    return result;
}

Matrix* apply_function_to_matrix( Matrix* matrix, void* ( *func )( void* ) ){
    if ( !matrix || !func ) {
        return NULL; // Invalid input
    }
    Matrix* result = create_matrix( matrix->row_count, matrix->column_count );
    if ( !result ) {
        return NULL; // Memory allocation failed
    }
    for ( size_t i = 0; i < matrix->row_count; i++ ) {
        for ( size_t j = 0; j < matrix->column_count; j++ ) {
            void* element = get_vector_element( matrix->rows[ i ], j );
            void* new_element = func( element );
            if (set_matrix_element( result, i, j, new_element ) != 0) {
                free_matrix( result );
                return NULL; // Memory allocation failed
            }
        }
    }
    return result;
}

Matrix* map_matrix( Matrix* matrix, void* ( *func )( void* ) ){
    return apply_function_to_matrix( matrix, func );
}


long long int determinant( Matrix* matrix ){
    if ( !matrix || matrix->row_count != matrix->column_count ) {
        return 0; // Invalid matrix or not square
    }
    // Implementation for calculating the determinant (e.g., using LU decomposition or recursive expansion)
    return 0; // Placeholder return value
}

Matrix* inverse_matrix( Matrix* matrix ){
    if ( !matrix || matrix->row_count != matrix->column_count ) {
        return NULL; // Invalid matrix or not square
    }
    // Implementation for calculating the inverse of the matrix (e.g., using Gaussian elimination)
    return NULL; // Placeholder return value
}

Matrix* power_matrix( Matrix* matrix, int exponent ){
    if ( !matrix || matrix->row_count != matrix->column_count ) {
        return NULL; // Invalid matrix or not square
    }
    // Implementation for calculating the power of the matrix
    return NULL; // Placeholder return value
}


#endif // _MATRIX_C_