#ifndef __KVS_H
#define __KVS_H



typedef struct {
    unsigned int cheie;
    double valoare;
} El_t;

typedef struct kvs* KVS_t;  // The publicly accessible KVS type is a pointer to a "hidden" structure

KVS_t initKVS();

KVS_t adauga(KVS_t, El_t);

void printKVS(KVS_t);

int comparakvs(const void *a, const void *b);

int cauta(KVS_t, unsigned);

#endif // __KVS_H