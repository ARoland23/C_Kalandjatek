#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include "szoba.h"
#include <stdbool.h>
typedef struct listaElem {
    szoba* ertek; //egy adott szoba
    struct listaElem* elozo;
    struct listaElem* kovetkezo;
} listaElem;

bool addToList(szoba* mit, listaElem* utolso);
listaElem* getAtIndex(listaElem* root, int index);
void listaTorol(listaElem* gyoker);
#endif // LISTA_H_INCLUDED
