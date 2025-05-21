#include <stdbool.h>
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"

//sikeres  volt-e a szoba beolvasás
#define SzobaRead {if (fscanf(szobaOlvas, "%d.", &tempRead) != 1) {listaTorol(gyokerNode);fclose(szobaOlvas);return 1;}}


/** Beolvassa az i-edik szobát.
 *
 * 1.param: hanyadik szobát kell beolvasnia.
 * 2.param: lista gyökérpointere, amibe eltárolja a szobákat.
 */
bool szobaBeolvasas(int i, listaElem* gyokerNode) {
    char filenameTemp[300];
    sprintf(filenameTemp, "szoba%d.txt", i);
    FILE* szobaOlvas = fopen(filenameTemp, "r");
    if (!szobaOlvas) {
        listaTorol(gyokerNode);
        return 1;
    }
    szoba* sz = malloc(sizeof(szoba));
    if (!sz) {
        listaTorol(gyokerNode);
        fclose(szobaOlvas);
        return 1;
    }
    sz->leiras = sz->atmenet = sz->atmenetfeltetel = NULL;
    sz->megvizsgalt = false;
    if (!addToList(sz, gyokerNode))
    {
        free(sz);
        listaTorol(gyokerNode);
        fclose(szobaOlvas);
        return 1;
    }
    int tempRead;

    SzobaRead;
    sz->harc = tempRead;

    SzobaRead;
    sz->heal = tempRead;

    SzobaRead;
    sz->kard = tempRead;

    SzobaRead;
    sz->kulcs = tempRead;

    SzobaRead;
    sz->kulcs2 = tempRead;

    SzobaRead;
    sz->atmenetSzam = tempRead;

    if (sz->atmenetSzam > 0)
    {
        sz->atmenet = malloc(sizeof(int) * sz->atmenetSzam);
        if (!sz->atmenet) {
            listaTorol(gyokerNode);
            fclose(szobaOlvas);
            return 1;
        }
        sz->atmenetfeltetel = malloc(sizeof(char) * sz->atmenetSzam);
        if (!sz->atmenetfeltetel)
        {
            listaTorol(gyokerNode);
            fclose(szobaOlvas);
            return 1;
        }
        for (int j = 0; j < sz->atmenetSzam; j++)
        {
            SzobaRead;
            sz->atmenet[j] = tempRead;
            char tempReadC;
            if (fscanf(szobaOlvas, "%c.", &tempReadC) != 1)
            {
                listaTorol(gyokerNode);
                fclose(szobaOlvas);
                return 1;
            }
            sz->atmenetfeltetel[j] = tempReadC;
        }
    }

    int allocated = 1;
    sz->leiras = malloc(allocated * sizeof(char));
    if (!sz->leiras)
    {
        listaTorol(gyokerNode);
        fclose(szobaOlvas);
        return 1;
    }

    int readIndex = 0;
    //szoba leírását beolvassa
    for (;;)
    {
        tempRead = fgetc(szobaOlvas);
        char tempReadC;
        if (tempRead == EOF)
            tempReadC = 0; //null terminátor
        else
            tempReadC = tempRead;
        if (readIndex == allocated)
        {
            char* tempLeiras = realloc(sz->leiras, (allocated *= 2) * sizeof(char));
            if (!tempLeiras)
            {
                listaTorol(gyokerNode);
                fclose(szobaOlvas);
                return 1;
            }
            sz->leiras = tempLeiras;
        }
        memcpy(sz->leiras + readIndex++, &tempReadC, 1);
        if (tempRead == EOF)
            break;
    }
    fclose(szobaOlvas);
}


//beolvassa amit a játékos beír
char* readLine() {
    int allocated = 1, read = 0;
    char* t = malloc(allocated * sizeof(char));
    if (!t)
        return NULL;
    int r;
    for (;;)
    {
        r = getchar();
        if (read == allocated)
        {
            char* tomb = realloc(t, allocated *= 2);
            if (tomb)
            {
                t = tomb;
            }
            else
            {
                free(t);
                return NULL;
            }
        }
        if (r == '\n')
        {
            t[read] = '\0';
            return t;
        }
        else
        {
            t[read] = r;
        }
        read++;
    }
}
