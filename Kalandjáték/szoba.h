#ifndef SZOBA_H_INCLUDED
#define SZOBA_H_INCLUDED
#include <stdbool.h>
typedef struct szoba {
    bool harc, heal, kard, kulcs, kulcs2;
    char* leiras;
    int* atmenet;
    char* atmenetfeltetel; //+ => nincs feltetel, m => megvizsgalas a feltetel, 1: kulcs a feltetel, 2: kulcs2 a feltetel
    int atmenetSzam; //hány szobába lehet átmenni

    bool megvizsgalt;
} szoba;

#endif // SZOBA_H_INCLUDED





