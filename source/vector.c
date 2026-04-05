#ifndef _VECTOR_C_
#define _VECTOR_C_

#include "vector.h"

Vector* create_vector(size_t initial_capacity){
    if (initial_capacity == 0) {
        initial_capacity = 1; // Ensure at least one element can be stored
    }
    Vector* vector = (Vector*)malloc(sizeof(Vector));
    if (vector == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }
    vector->data = (void**)malloc(initial_capacity * sizeof(void*));
    if (vector->data == NULL) {
        free(vector); // Free the vector struct if data allocation fails
        return NULL;
    }
    vector->size = 0;
    vector->capacity = initial_capacity;
    return vector;
}

void free_vector(Vector* vector){
    if (vector != NULL) {
        free(vector->data);
        free(vector);
    }
}

int vector_push_back(Vector* vector, void* element){
    if (vector == NULL || element == NULL) {
        return -1; // Return -1 if vector or element is NULL
    }
    if (vector->size >= vector->capacity) {
        // Resize the vector if it's full
        size_t new_capacity = vector->capacity * 2;
        void** new_data = (void**)malloc(new_capacity * sizeof(void*));
        if (new_data == NULL) {
            return -1; // Return -1 if memory reallocation fails
        }
        memcpy(new_data, vector->data, vector->size * sizeof(void*));
        free(vector->data);
        vector->data = new_data;
        vector->capacity = new_capacity;
    }
    vector->data[vector->size] = element;
    vector->size++;
    return 0; // Return 0 on success
}

void* get_vector_element(Vector* vector, size_t index){
    if (vector == NULL || index >= vector->size) {
        return NULL; // Return NULL if vector is NULL or index is out of bounds
    }
    return vector->data[index];
}

size_t get_vector_size(Vector* vector){
    if (vector == NULL) {
        return 0; // Return 0 if vector is NULL
    }
    return vector->size;
}

size_t get_vector_capacity(Vector* vector){
    if (vector == NULL) {
        return 0; // Return 0 if vector is NULL
    }
    return vector->capacity;
}

void for_each( Vector* vector, void (*func)(void*) ){
    if (vector == NULL || func == NULL) {
        return; // Do nothing if vector or function is NULL
    }
    for (size_t i = 0; i < vector->size; i++) {
        func(vector->data[i]);
    }
}

#endif // _VECTOR_C_