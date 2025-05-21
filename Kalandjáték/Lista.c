#include "Lista.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"

/** Hozz�f�zi a megadott list�hoz a megadott szob�t.
 *
 * 1.param: a szoba amit hozz� k�v�n f�zni.
 * 2.param: a lista utols� eleme.
 * Ha sikeres: return true.
 (majd fel kell szabad�tani!)
 */
bool addToList(szoba* mit, listaElem* utolso) {
    while (utolso->kovetkezo != NULL)
    {
        utolso = utolso->kovetkezo;
    }

    if (utolso->ertek == NULL)
    {
        utolso->ertek = mit;
        return true;
    }
    listaElem* uj = malloc(sizeof(listaElem));
    if (!uj)
        return false;

    uj->ertek = mit;
    uj->elozo = utolso;
    uj->kovetkezo = NULL;
    utolso->kovetkezo = uj;
    return true;
}

/** Megn�zi, hogy a megadott indexen melyik szoba van.
 *
 * 1.param: A lista gy�k�r pointere.
 * 2.param: A szoba sorsz�ma.
 * return: a keresett index� szoba.
 */
listaElem* getAtIndex(listaElem* root, int index) {
    for (int i = 0; i < index; i++)
    {
        if (!(root = root->kovetkezo))
            break;
    }
    return root;
}

/** T�rli a megadott list�t �s benne l�v� szob�kat.
 *
 * 1.param: a lista gy�k�r eleme.
 */
void listaTorol(listaElem* gyoker) {
    if (!gyoker)
        return;
    listaElem* temp = gyoker;
    for (;;)
    {
        gyoker = temp;
        if (gyoker->ertek)
        {
            if (gyoker->ertek->leiras)
                free(gyoker->ertek->leiras);
            if (gyoker->ertek->atmenet)
                free(gyoker->ertek->atmenet);
            if (gyoker->ertek->atmenetfeltetel)
                free(gyoker->ertek->atmenetfeltetel);
            free(gyoker->ertek);
        }
        temp = gyoker->kovetkezo;
        free(gyoker);
        if (!temp)
            return;
    }
}
