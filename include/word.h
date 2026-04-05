#ifndef _WORD_H_
#define _WORD_H_

#ifdef _WORD_C_

#include <stdlib.h>
#include <string.h>

typedef struct _word_{
    void* key;
    void* value;
} Word;

// Function prototypes for Word operations
Word* create_word( void* key, void* value );
void free_word (Word* word );

// Getters and setters for Word
void* get_key( Word* word );
void* get_value( Word* word );
void set_key( Word* word, void* key );
void set_value( Word* word, void* value );

#else

typedef struct _word_ Word;

extern Word* create_word( void* key, void* value );
extern void free_word( Word* word );

extern void* get_key( Word* word );
extern void* get_value( Word* word );
extern void set_key( Word* word, void* key );
extern void set_value( Word* word, void* value );

#endif // _WORD_C_

#endif // _WORD_H_