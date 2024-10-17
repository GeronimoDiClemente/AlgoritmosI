#include <stdio.h>
#include <stdlib.h>
#include "tdacola.h"
#define DIMSUB 4

typedef struct nodito
{
    int numero;
    struct nodito *sig;
} NODITO;
typedef NODITO *TSUBLISTA;

typedef struct nodo
{
    TSUBLISTA sublista;
    struct nodo *sig;
} NODO;
typedef NODO *TLISTA;

void cargaLista (TLISTA *pl)
{
    FILE *arch;
    arch = fopen("carton.txt","rt");
    TLISTA ult;
    TSUBLISTA sult;
    int i,numero;
    *pl = NULL;
    if (arch == NULL)
        printf("NUlO");
    else
    {
        while (!feof(arch))
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
            ult->sublista = NULL;
            for (i=0; i<DIMSUB; i++)
            {
                fscanf(arch,"%d",&numero);
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
                sult->numero = numero;
            }
            sult->sig = NULL;
        }
        ult->sig = NULL;
    }
    fclose(arch);
}

void cargaCola (TCOLA *cola)
{
    TELEMENTOC numero;
    FILE *arch;
    arch = fopen("sorteados.txt","rt");
    if (arch == NULL)
        printf("NULO");
    else
        while (fscanf(arch,"%d",&numero) == 1)
            ponec(cola,numero);
    /*
    printf("\nCOLA:\n");
    while (!vaciac(*cola))
    {
        sacac(cola,&numero);
        printf("%d\t",numero);
    }
    printf("\n");
    */
    fclose(arch);
}


void muestraLista (TLISTA pl)
{
    TSUBLISTA aux;
    while (pl != NULL)
    {
        aux = pl->sublista;
        while (aux != NULL)
        {
            printf("%d\t",aux->numero);
            aux = aux->sig;
        }
        pl = pl->sig;
        printf("\n");
    }
}

void opera (TLISTA *pl, TCOLA *cola)
{
    TLISTA act;
    TSUBLISTA sact,sant,elim;
    TELEMENTOC sorteado;
    int numero,contDecena;

    while (!vaciac(*cola))
    {
        sacac(cola,&sorteado);
        act = *pl;
        contDecena = -10;
        while (act != NULL)
        {
            contDecena+=10;
            sant = NULL;
            sact = act->sublista;
            while (sact != NULL && sact->numero != sorteado)
            {
                sant = sact;
                sact = sact->sig;
            }
            if (sact != NULL)
            {

                if (sant == NULL)
                {
                    elim = act->sublista;
                    act->sublista = act->sublista->sig;
                    free(elim);
                    sact = act->sublista;
                }
                else
                {
                    sant->sig = sact->sig;
                    free(sact);
                    sact = sant->sig;
                }
            }
            if (act->sublista == NULL)
                printf("eliminada decena %d\n",contDecena);
            act = act->sig;
        }

    }
}

int main()
{
    TCOLA cola;
    TLISTA pl;
    cargaLista(&pl);
    //muestraLista(pl);
    iniciac(&cola);
    cargaCola(&cola);
    opera(&pl,&cola);
    muestraLista(pl);
    return 0;
}
