#ifndef _WORD_C_
#define _WORD_C_

#include "word.h"

Word* create_word( void* key, void* value ){
    if ( key == NULL || value == NULL ) {
        return NULL; // Return NULL if key or value is NULL
    }
    Word* word = ( Word* )malloc( sizeof( Word ) );
    if ( word == NULL ) {
        return NULL; // Return NULL if memory allocation fails
    }
    word->key = key;
    word->value = value;
    return word;
}

void free_word( Word* word ){
    if ( word != NULL ) {
        free( word );
    }
}

void* get_key( Word* word ){
    if ( word != NULL ) {
        return word->key;
    }
    return NULL;
}

void* get_value( Word* word ){
    if ( word != NULL ) {
        return word->value;
    }
    return NULL;
}

void set_key( Word* word, void* key ){
    if ( word != NULL ) {
        word->key = key;
    }
}

void set_value( Word* word, void* value ){
    if ( word != NULL ) {
        word->value = value;
    }
}

#endif // _WORD_C_