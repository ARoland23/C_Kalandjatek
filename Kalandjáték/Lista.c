#include "Lista.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"

/** Hozzáfûzi a megadott listához a megadott szobát.
 *
 * 1.param: a szoba amit hozzá kíván fûzni.
 * 2.param: a lista utolsó eleme.
 * Ha sikeres: return true.
 (majd fel kell szabadítani!)
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

/** Megnézi, hogy a megadott indexen melyik szoba van.
 *
 * 1.param: A lista gyökér pointere.
 * 2.param: A szoba sorszáma.
 * return: a keresett indexû szoba.
 */
listaElem* getAtIndex(listaElem* root, int index) {
    for (int i = 0; i < index; i++)
    {
        if (!(root = root->kovetkezo))
            break;
    }
    return root;
}

/** Törli a megadott listát és benne lévõ szobákat.
 *
 * 1.param: a lista gyökér eleme.
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
