#include <stdio.h>
#include <stdlib.h>
#include <string.h.>
#include "tdacola.h"
#define MAX 5

typedef struct nodito
{
    char codMateria[MAX];
    struct nodito *sig;
}NODITO;
typedef NODITO *TSUBLISTA;

typedef struct nodo
{
    char matricula[MAX];
    TSUBLISTA sublista;
    struct nodo *sig;
}NODO;
typedef NODO *TLISTA;

void cargaLista(TLISTA *pl)
{
    FILE *arch;
    arch = fopen("pendientes.txt","rt");
    TLISTA ult;
    TSUBLISTA sult;
    char matricula[MAX], codMateria[MAX];;
    int dimSublista,i;

    if (arch == NULL)
        printf("Archivo vacio");
    else
    {
        *pl = NULL;
        while (fscanf(arch,"%s %d",matricula,&dimSublista) == 2)
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
            strcpy(ult->matricula,matricula);
            ult->sublista = NULL;
            for (i=0;i<dimSublista;i++)
            {
                fscanf(arch,"%s",codMateria);
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
                strcpy(sult->codMateria,codMateria);
            }
            sult->sig = NULL;
        }
        ult->sig = NULL;
    }
    fclose(arch);
}

void muestraLista (TLISTA pl)
{
    TSUBLISTA aux;

    while (pl != NULL)
    {
        aux = pl->sublista;
        printf("%s\t",pl->matricula);
        while (aux != NULL)
        {
            printf("%s\t",aux->codMateria);
            aux = aux->sig;
        }
        printf("\n");
        pl = pl->sig;
    }
}

void cargaCola(TCOLA *cola)
{
    TELEMENTOC registro;
    FILE *arch;
    arch = fopen("aprobados.txt","rt");
    if (arch == NULL)
        printf("Archivo Nulo");
    else
    {
        while (fscanf(arch,"%s %s",registro.matricula,registro.codMateria) == 2)
            ponec(cola,registro);

    }
    fclose(arch);
}

void opera (TCOLA *cola, TLISTA *pl)
{
    TELEMENTOC registro;
    TLISTA act,ant;
    TSUBLISTA sact,sant,selim;
    ant = NULL;
    sant = NULL;
    act = *pl;
    while (!vaciac(*cola))
    {
        sacac(cola,&registro);
        while (act && strcmp(registro.matricula,act->matricula) != 0)
        {
            ant = act;
            act = act->sig;
        }
        sact = act->sublista;
        while (sact && strcmp(sact->codMateria,registro.codMateria) != 0)
        {
            sant = sact;
            sact = sact->sig;
        }
        if (sact != NULL)
        {
            if (sant == NULL)
            {
                /*act->sublista = act->sublista->sig;
                free(sact);
                sact = act->sublista;*/
                selim = sact;
                sact = sact->sig;
                act->sublista = sact;
                free(selim);
            }
            else
            {
                sant->sig = sact->sig;
                free(sact);
                sact = sant->sig;
            }

        }

    }
}

int main()
{
    TLISTA pl;
    TCOLA cola;
    TELEMENTOC registro;
    cargaLista(&pl);
    iniciac(&cola);
    cargaCola(&cola);
    opera(&cola,&pl);
    /*
    printf("\nCOLA\n");
    while(!vaciac(cola))
    {
        sacac(&cola,&registro);
        printf("%s %s\n",registro.matricula,registro.codMateria);
    }
    */
    muestraLista(pl);
    return 0;
}
