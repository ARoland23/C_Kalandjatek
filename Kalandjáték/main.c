#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "szoba.h"
#include "jatekallas.h"
#include "Lista.h"
#include "beolvas.h"
#include "harc.h"
#include "debugmalloc.h"


int main() {
    listaElem* gyokerNode = malloc(sizeof(listaElem));
    if (!gyokerNode)
    {
        return 1;
    }

    gyokerNode->ertek = gyokerNode->elozo = gyokerNode->kovetkezo = NULL;
    for (int i = 0; i < 15; i++)
    {

        if (szobaBeolvasas(i, gyokerNode))
        {
            return 1;
        }
    }
    jatekallas j1;
    if (!Beolvasas(&j1, gyokerNode))
    {
        Kitorles();
    }
    if (!Beolvasas(&j1, gyokerNode))
    {
        listaTorol(gyokerNode);
        return 1;
    }

    int elozoSzoba = j1.jelenlegiSzoba;
    srand(time(NULL));
    while (j1.jelenlegiSzoba != 14)
    {
        szoba* jelenlegi = NULL;
        listaElem* lE = getAtIndex(gyokerNode, j1.jelenlegiSzoba);
        if (!lE)
        {
            listaTorol(gyokerNode);
            return 1;
        }
        if (!(jelenlegi = lE->ertek))
        {
            listaTorol(gyokerNode);
            return 1;
        }
        if (jelenlegi->harc)
        {
            switch (harc(gyokerNode, &j1, elozoSzoba)) {
                case 0:
                    break;
                case 1:
                    continue;
                case 2:
                    return 1;
                    break;
            }
        }
        printf("%s\r\n", jelenlegi->leiras);
        for (;;)
        {
            printf("Mit csinalsz?\r\n");
            int ennyiHelyetLatunkCsakAkkorHaMarAtvizsgaltukDeMegNemVizsgaltukAt = 0;
            for (int i = 0; i < jelenlegi->atmenetSzam + (jelenlegi->megvizsgalt ? 0 : 1); i++)
            {
                if (i == jelenlegi->atmenetSzam) {
                    printf("%i: Megvizsgalod a helyiseget\r\n", i + 1 - ennyiHelyetLatunkCsakAkkorHaMarAtvizsgaltukDeMegNemVizsgaltukAt);
                }
                else
                {
                    if (jelenlegi->atmenetfeltetel[i] == 'm' && !jelenlegi->megvizsgalt)
                    {
                        ennyiHelyetLatunkCsakAkkorHaMarAtvizsgaltukDeMegNemVizsgaltukAt++;
                    }
                    else
                    {
                        printf("%d: Tovabbmesz a %d. helyisegbe\r\n", i + 1 - ennyiHelyetLatunkCsakAkkorHaMarAtvizsgaltukDeMegNemVizsgaltukAt, jelenlegi->atmenet[i] + 1);
                    }
                }
            }
            printf("> ");
            char* read = readLine();
            if (!read)
            {
                listaTorol(gyokerNode);
                return 1;
            }
            int option = 0;
            if (sscanf(read, "%d", &option) != 1)
            {
                free(read);
                continue;
            }
            if (option < 1 || option > jelenlegi->atmenetSzam - ennyiHelyetLatunkCsakAkkorHaMarAtvizsgaltukDeMegNemVizsgaltukAt + (jelenlegi->megvizsgalt ? 0 : 1))
            {
                free(read);
                continue;
            }
            if (option == jelenlegi->atmenetSzam - ennyiHelyetLatunkCsakAkkorHaMarAtvizsgaltukDeMegNemVizsgaltukAt + 1) //vizsgal
            {
                if (jelenlegi->heal)
                {
                    if(++j1.HP > 3 )
                        j1.HP=3;

                printf("Egy elsosegelydobozt pillantottal meg, fel is hasznaltad. Az uj HP-d %i\r\n", j1.HP);
                }
                if (jelenlegi->kard)
                {
                    j1.kard = true;
                    printf("Ez eles! Talaltal egy kardot! Ezzel konnyebb lesz majd a szornyeket legyozni\r\n");
                }
                if (jelenlegi->kulcs)
                {
                    j1.kulcs = true;
                    printf("Talaltal valamit... Egy kulcsnak tunik! De vajon mit nyithat?\r\n");
                }
                if (jelenlegi->kulcs2)
                {
                    j1.kulcs2 = true;
                    printf("Talaltal valamit az asztalon... Egy nagy kulcs! Mit nyithat?\r\n");
                }
                if (ennyiHelyetLatunkCsakAkkorHaMarAtvizsgaltukDeMegNemVizsgaltukAt) {
                    printf("Talaltal egy atjarot!\r\n");
                }
                j1.megvizsgaltSzoba[j1.jelenlegiSzoba] = jelenlegi->megvizsgalt = true;
                if (!(jelenlegi->heal || jelenlegi->kard || jelenlegi->kulcs || jelenlegi->kulcs2 || ennyiHelyetLatunkCsakAkkorHaMarAtvizsgaltukDeMegNemVizsgaltukAt))
                {
                    printf("Nem talaltal semmit...\r\n");
                }
                Mentes(&j1);
                continue;
            }
            else //atmegy egy masik helyre
            {
                int atmegy = -1;
                ennyiHelyetLatunkCsakAkkorHaMarAtvizsgaltukDeMegNemVizsgaltukAt = 0;
                for (int i = 0; i < jelenlegi->atmenetSzam; i++) {
                    if (jelenlegi->atmenetfeltetel[i] == 'm' && !jelenlegi->megvizsgalt)
                    {
                        ennyiHelyetLatunkCsakAkkorHaMarAtvizsgaltukDeMegNemVizsgaltukAt++;
                    }
                    else
                    {
                        if (i + 1 - ennyiHelyetLatunkCsakAkkorHaMarAtvizsgaltukDeMegNemVizsgaltukAt == option)
                        {
                            atmegy = i;
                            break;
                        }
                    }
                }
                switch (jelenlegi->atmenetfeltetel[atmegy]) {
                    case 'm':
                    case '+':
                        elozoSzoba = j1.jelenlegiSzoba;
                        j1.jelenlegiSzoba = jelenlegi->atmenet[atmegy];
                        break;
                    case '1':
                        if (!j1.kulcs)
                        {
                            printf("Megprobalod kinyitni az ajtot... Akarmivel is probalkozol, nem nyilik ki. Hol lehet a kulcsa?\r\n");
                            continue;
                        }
                        else
                        {
                            elozoSzoba = j1.jelenlegiSzoba;
                            j1.jelenlegiSzoba = jelenlegi->atmenet[atmegy];
                        }
                        break;
                    case '2':
                        if (!j1.kulcs2)
                        {
                            printf("Megprobalod kinyitni az ajtot... Akarmivel is probalkozol, nem nyilik ki. Hol lehet a kulcsa?\r\n");
                            continue;
                        }
                        else
                        {
                            elozoSzoba = j1.jelenlegiSzoba;
                            j1.jelenlegiSzoba = jelenlegi->atmenet[atmegy];
                        }
                        break;
                }
            }
            break;
        }
        Mentes(&j1);
    }
    szoba* jelenlegi = NULL;
    listaElem* lE = getAtIndex(gyokerNode, j1.jelenlegiSzoba); //biztosan 14-es a jelenlegi szoba
    if (!lE)
    {
        listaTorol(gyokerNode);
        return 1;
    }
    if (!(jelenlegi = lE->ertek))
    {
        listaTorol(gyokerNode);
        return 1;
    }
    printf("%s", jelenlegi->leiras);
    listaTorol(gyokerNode);
    Kitorles();
    fgetc(stdin);
    return 0;
}
