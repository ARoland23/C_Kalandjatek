#ifndef JATEKALLAS_H_INCLUDED
#define JATEKALLAS_H_INCLUDED
#include <stdbool.h>
#include <stdio.h>
#include "lista.h"
typedef struct jatekallas {
    int jelenlegiSzoba, HP;
    bool kard, kulcs, kulcs2;
    bool megvizsgaltSzoba[15]; //melyik szob�kat vizsg�lta m�r meg a j�t�kos
} jatekallas;

bool jatekallasFajlKitorles();
bool jatekallasFajlBeolvasas(jatekallas* ebbe, listaElem* szobak);
bool jatekallasFajlMentes(jatekallas* ebbol);


#endif // JATEKALLAS_H_INCLUDED


