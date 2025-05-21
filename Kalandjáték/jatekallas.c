#include <stdio.h>
#include "jatekallas.h"
#include "Lista.h"
#include "debugmalloc.h"

/** Alapértelmezettre állítja a mentést.
 *
 * Ha sikeres: return true.
 */

bool Kitorles() {
    FILE* f = fopen("jatekallas.txt", "w");
    if (!f)
        return false;
    if (fprintf(f, "0.3.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.") < 0)
    {
        fclose(f);
        return false;
    }
    fclose(f);
    return true;
}
//megnézi, jó-e az adat
#define jatekallasBeolvas {if (fscanf(f, "%d.", &tempRead) == EOF) {fclose(f);return false;}}

/** Beolvassa a jatekallas.txt-ből a tárolt adatokat.
 *
 * 1.param: A játékállás amibe beolvassa.
 * 2.param: A lista amibe eltárolja.
 * Ha sikeres: return true.
 */
bool Beolvasas(jatekallas* ebbe, listaElem* szobak) {
    FILE* f = fopen("jatekallas.txt", "r");
    if (!f)
        return false;

    int tempRead;
    jatekallasBeolvas;
    ebbe->jelenlegiSzoba = tempRead;
    jatekallasBeolvas;
    ebbe->HP = tempRead;
    jatekallasBeolvas;
    ebbe->kard = tempRead;
    jatekallasBeolvas;
    ebbe->kulcs = tempRead;
    jatekallasBeolvas;
    ebbe->kulcs2 = tempRead;

    for (int i = 0; i < 15; i++)
    {
        jatekallasBeolvas;
        listaElem* s = getAtIndex(szobak, i);
        if (!s)
        {
            fclose(f);
            return false;
        }
        ebbe->megvizsgaltSzoba[i] = s->ertek->megvizsgalt = tempRead;
    }
    fclose(f);
    return true;
}

//megnézi, jó-e az adat
#define jatekallasMentes(a) {if (fprintf(f, "%d.", (a)) < 0) {fclose(f);return false;}}

/** Elmenti a jatekallas.txt-be a megfelelo adatokat.
 *
 * 1.param: a játékállás amiből mentenie kell az adatokat.
 * Ha sikeres: return true.
 */
bool Mentes(jatekallas* ebbol) {
    FILE* f = fopen("jatekallas.txt", "w");
    if (!f)
        return false;
    jatekallasMentes(ebbol->jelenlegiSzoba );
    jatekallasMentes(ebbol->HP );
    jatekallasMentes(ebbol->kard ? 1 : 0);
    jatekallasMentes(ebbol->kulcs ? 1 : 0);
    jatekallasMentes(ebbol->kulcs2 ? 1 : 0);
    for (int i = 0; i < 15; i++)
        jatekallasMentes(ebbol->megvizsgaltSzoba[i] ? 1 : 0);
    fclose(f);
    return true;
}
