#ifndef _STIVA_H

#define _STIVA_H

    extern int TEST;
    typedef unsigned Element_t;
    typedef enum {STIVA_OK, STIVA_FULL, STIVA_EMPTY, STIVA_ALLOC_ERR} StatusCode_t;

    typedef struct Stiva* Stiva_t;   //tipul stiva accesibil "public" este un pointer catre o structura "ascunsa"

    Stiva_t makeStack();
    StatusCode_t push(Stiva_t, Element_t);
    StatusCode_t pop(Stiva_t, Element_t*);
    StatusCode_t peek(Stiva_t, Element_t*);

    void printStatus();

    StatusCode_t destroyStack(Stiva_t);

#endif



