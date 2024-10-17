#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdapila.h"
#define MAX 11

typedef struct nodito
{
    int precio;
    struct nodito *sig;
}NODITO;
typedef NODITO *TSUBLISTA;

typedef struct nodo
{
    char nombre[MAX];
    float precioRef;
    TSUBLISTA sublista;
    struct nodo *sig;
}NODO;
typedef NODO *TLISTA;

void cargaLista (TLISTA *pl)
{
    FILE *arch;
    TLISTA ult;
    TSUBLISTA sult;
    int dimSublista,i,precio;
    char nombre[MAX];
    float precioRef;
    arch = fopen("precios.txt","rt");
    if (arch == NULL)
        printf("Archivo Nulo");
    else
    {
        *pl = NULL;
        while (fscanf(arch,"%s %f %d",nombre,&precioRef,&dimSublista) == 3)
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
            ult->precioRef = precioRef;
            ult->sublista = NULL;
            for (i=0; i<dimSublista; i++)
            {
                fscanf(arch,"%d",&precio);
                if (ult->sublista == NULL)
                {
                    ult->sublista = (TSUBLISTA)malloc(sizeof(NODITO));
                    sult = ult->sublista;
                }
                else
                {
                    sult->sig = (TSUBLISTA)malloc(sizeof(NODITO));
                    sult = sult->sig;
                }
                sult->precio = precio;
            }
            sult->sig = NULL;
        }
        ult->sig = NULL;
    }
    fclose(arch);
}

void muestraLista (TLISTA pl)
{
    while (pl != NULL)
    {
        printf("%s\t %.2f",pl->nombre,pl->precioRef);
        while (pl->sublista != NULL)
        {
            printf("\n%d",pl->sublista->precio);
            pl->sublista = pl->sublista->sig;
        }
        printf("\n");
        pl = pl->sig;
    }

}

void opera (TLISTA *pl)
{
    TLISTA act,ant,elim;
    TPILA pila;
    int cont,dimSublista;
    TELEMENTOP registro;
    iniciap(&pila);
    ant = NULL;
    act = *pl;
    while (act != NULL)
    {
        cont = 0;dimSublista = 0;
        while (act->sublista != NULL)
        {
            dimSublista++;
            if (act->sublista->precio>act->precioRef)
                cont++;

            act->sublista = act->sublista->sig;
        }
        if (cont == dimSublista)
        {
            strcpy(registro.nombre,act->nombre);
            ponep(&pila,registro);
            if (ant == NULL)
            {
                elim = *pl;
                (*pl) = (*pl)->sig;
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

    printf("Pila\n");
    while (!vaciap(pila))
    {
        sacap(&pila,&registro);
        printf("%s\t",registro.nombre);
    }
    printf("\n\n");
}
int main()
{
    TELEMENTOP registro;
    TLISTA pl;
    TPILA pila;
    cargaLista(&pl);
    //muestraLista(pl);

    opera(&pl);
    muestraLista(pl);


    return 0;
}
