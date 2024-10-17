#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdapilad.h"
#define MAXNOM 9

typedef struct nodo
{
    char nombre[MAXNOM];
    TPILA pila;
    struct nodo *sig;
}NODO;
typedef NODO *TLISTA;

void cargaLista (TLISTA *pl)
{
    char nombre[MAXNOM],palo;
    int i,nuemro,dimPila;
    FILE *arch;
    TLISTA ult;
    TELEMENTOP registro;
    arch = fopen("Archivo.txt","rt");
    *pl = NULL;
    if (arch == NULL)
        printf("NULO");
    else
    {
        while (fscanf(arch,"%s %d",nombre,&dimPila) == 2)
        {
            if (*pl == NULL)
            {
                *pl = (TLISTA)malloc(sizeof(NODO));
                ult = *pl;
            }
            else
            {
                ult->sig = (TLISTA)malloc(sizeof(NODO));
                ult = ult->sig;
            }
            strcpy(ult->nombre,nombre);
            iniciap(&ult->pila);
            for (i=0;i<dimPila;i++)
            {
                fscanf(arch,"%d %c",&registro.numero,&registro.palo);
                ponep(&ult->pila,registro);
            }
        }
        ult->sig = NULL;
    }
    fclose(arch);
}

void muestraLlista (TLISTA pl)
{
    TELEMENTOP registro;
    while (pl != NULL)
    {
        printf("%s\n",pl->nombre);
        while (!vaciap(pl->pila))
        {
            sacap(&pl->pila,&registro);
            printf("%d %c\n",registro.numero,registro.palo);
        }
        printf("\n");
        pl = pl->sig;
    }
}


void recorreLista (TLISTA *pl)
{
    int cont,dimPila;
    char paloAct;
    TLISTA act,ant,elim;
    TELEMENTOP registro;
    ant = NULL;
    act = *pl;
    while (act != NULL)
    {
        dimPila=0;
        sacap(&act->pila,&registro);
        paloAct = registro.palo;
        cont = 0;
        while (!vaciap(act->pila))
        {
            dimPila++;
            if (registro.palo == paloAct)
                cont++;
            paloAct = registro.palo;
            sacap(&act->pila,&registro);
        }
        if (cont == dimPila) //ELIMINAMOS
        {
            if (ant == NULL)
            {
                elim = *pl;
                *pl = (*pl)->sig;
                free(elim);
                act = *pl;
            }
            else
            {
                ant->sig = act->sig;
                free(act);
                act = ant->sig;
            }

        }
        ant = act;
        act = act->sig;
    }
}
int main()
{
    TLISTA pl;
    int dimPila;
    cargaLista(&pl);
    recorreLista(&pl);
    muestraLlista(pl);
    return 0;
}
