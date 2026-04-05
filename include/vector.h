#ifndef _VECTOR_H_
#define _VECTOR_H_

#ifdef _VECTOR_C_

#include <stdlib.h>
#include <string.h>

typedef struct _vector_{
    void* *data;
    size_t size;
    size_t capacity;
} Vector;

// Function prototypes for Vector operations
Vector* create_vector(size_t initial_capacity);
void free_vector(Vector* vector);
int vector_push_back(Vector* vector, void* element);

void* get_vector_element(Vector* vector, size_t index);
size_t get_vector_size(Vector* vector);
size_t get_vector_capacity(Vector* vector);

void for_each( Vector* vector, void (*func)(void*) );

#else

typedef struct _vector_ Vector;

extern Vector* create_vector(size_t initial_capacity);
extern void free_vector(Vector* vector);
extern int vector_push_back(Vector* vector, void* element);

extern void* get_vector_element(Vector* vector, size_t index);
extern size_t get_vector_size(Vector* vector);
extern size_t get_vector_capacity(Vector* vector);

extern void for_each( Vector* vector, void (*func)(void*) );

#endif // _VECTOR_C_

#endif // _VECTOR_H_