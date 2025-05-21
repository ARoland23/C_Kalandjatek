#include <stdbool.h>
#include <stdlib.h>
#include "jatekallas.h"
#include "debugmalloc.h"


/** Elkezdi a harcot.
 *
 * 1.param: a szobák listájának a gyökere.
 * 2.param: az adott játékállás.
 * 3.param: az elõzõ szoba sorszáma. (menekülés)
 * return 1: játékos vesztett vagy menekül.
 * return 0: játékos nyer.
 * return 2: hiba.
 */
int harc(listaElem* gyokerNode, jatekallas* j1, int elozoSzoba) {
    bool menekul = false, nyertem = false, vesztettem = false;
    printf("Valami mozgast veszel eszre a szemed sarkabol. Pillanatokon belul megtamad valami! Kezdodik a csata! ");
    while (!menekul && !nyertem && !vesztettem) {
        printf("Mit csinalsz?\r\n1. elmenekulsz\r\n2. kuzdesz az eletedert (%i HP-d van mar csak)\r\n> ", j1->HP);
        char* read = readLine();
        if (!read) {
            listaTorol(gyokerNode);
            return 2;
        }
        int option;
        if (sscanf(read, "%d", &option) != 1)
        {
            free(read);
            continue;
        }
        switch (option) {
            //játékos köre
            //menekülés
            case 1:
                j1->jelenlegiSzoba = elozoSzoba;
                menekul = true;
                break;
            //támadás
            case 2:
                if ((rand() % 20) + 1 > 10 - (j1->kard ? 5 : 0))
                {
                    nyertem = true;
                }
                else
            //elenfél köre
                {
                    if ((rand() % 20) + 1 > 10)
                    {
                        if (--j1->HP == 0)
                        {
                            printf("Eltalal es belehalsz a seruleseidbe!!\r\n");
                            j1->jelenlegiSzoba = 0;
                            j1->HP = 3;
                            j1->kard = j1->kulcs = j1->kulcs2 = false;
                            for (int i = 0; i < 15; i++)
                                j1->megvizsgaltSzoba[i] = false;
                            vesztettem = true;
                            Mentes(j1);
                            Beolvasas(j1, gyokerNode);
                        }
                        else
                        {
                            printf("Eltalaltak!\r\n");
                        }
                    }
                    else
                    {
                        printf("Megprobal eltalalni de nem sikerul neki!!\r\n");
                    }
                }
                break;
            default:
                free(read);
                continue;
        }
        free(read);
    }
    if (vesztettem || menekul)
        return 1;

    if (nyertem)
        printf("Nyertel!\r\n");
    return 0;
}

