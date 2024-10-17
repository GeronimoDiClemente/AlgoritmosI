#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdacola.h"
#define MAXCAD 4

typedef struct nodito
{
    char codContainer[MAXCAD];
    struct nodito *sig;
}NODITO;
typedef NODITO *TSUBLISTA;

typedef struct nodo
{
    int numeroPuerto;
    TSUBLISTA sublista;
    struct nodo *sig;
}NODO;
typedef NODO *TLISTA;

void cargaLista (TLISTA *pl)
{
    TLISTA ult;
    TSUBLISTA sult;
    int numeroPuerto,dimSublista,i;
    char codContainer[MAXCAD];
    FILE *arch;
    arch = fopen("informacion.txt","rt");
    if (arch == NULL)
        printf("NULO");
    else
    {
        *pl=NULL;
        while (fscanf(arch,"%d %d",&numeroPuerto,&dimSublista) == 2)
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
            ult->numeroPuerto = numeroPuerto;
            ult->sublista = NULL;
            for (i=0;i<dimSublista;i++)
            {
                fscanf(arch,"%s",codContainer);
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
                strcpy(sult->codContainer,codContainer);
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
        printf("%d\t",pl->numeroPuerto);
        while (aux != NULL)
        {
            printf("%s\t",aux->codContainer);
            aux = aux->sig;
        }
        printf("\n");
        pl = pl->sig;
    }
}

void cargarCola (TCOLA *cola)
{
    TELEMENTOC registro;
    FILE *arch;
    arch = fopen("duplas.txt","rt");
    if (arch == NULL)
        printf("NULO");
    else
    {
        while(fscanf(arch,"%d %s",&registro.numeroPuerto,registro.codContainer) == 2)
            ponec(cola,registro);
    }
    fclose(arch);
}

void muestraCola (TCOLA *cola)
{
    TELEMENTOC registro;
    while (!vaciac(*cola))
    {
        sacac(cola,&registro);
        printf("%d %s\n",registro.numeroPuerto,registro.codContainer);
    }
}

void opera(TLISTA pl, TCOLA cola)
{
    TELEMENTOC registro;
    TLISTA act,ant;
    int k,i,repetido=0;
    TSUBLISTA sact,sant,nuevo;
    ant = NULL;
    printf("Ingrese los k elementos\n");
    scanf("%d",&k);
    for (i=0;i<k;i++)
    {
        if(!vaciac(cola))
        {
            act = *pl;
            sacac(&cola,&registro);
            while (act != NULL && act->numeroPuerto != registro.numeroPuerto)
            {
                ant = act;
                act = act->sig;
            }
            if (act != NULL) //SE ENCONTRO EL PUERTO
            {
                sant = NULL;
                sact = act->sublista;
                while (sact != NULL && strcmp(registro.codContainer,sact->codContainer)>0)
                {
                    sant = sact;
                    sact = sact->sig;
                }
                if (sact != NULL && strcmp(registro.codContainer,sact->codContainer)!=0) //NO SE ENCONTRO EL CONTAINER HAY QUE AGREGARLO
                {
                    nuevo = (TSUBLISTA)malloc(sizeof(NODITO));
                    strcpy(nuevo->codContainer,registro.codContainer);
                    if (sant == NULL) //CONTAINER NUEVO 1° ELEMENTO
                    {
                        nuevo->sig = act->sublista;
                        act->sublista = nuevo;
                    }
                    else
                    {
                        nuevo->sig = sact;
                        sant->sig = nuevo;
                    }
                }
                else if (sact == NULL)
                {
                    nuevo = (TSUBLISTA)malloc(sizeof(NODITO));
                    strcpy(nuevo->codContainer,registro.codContainer);
                    if (sant == NULL) //CONTAINER NUEVO 1° ELEMENTO
                    {
                        nuevo->sig = act->sublista;
                        act->sublista = nuevo;
                    }
                    else
                    {
                        nuevo->sig = sact;
                        sant->sig = nuevo;
                    }
                }
                else
                    repetido++;
            }
        }
    }
    muestraLista(pl);
    printf("Containers repetidos: %d",repetido);
}

int main()
{
    TLISTA pl;
    TCOLA cola;
    cargaLista(&pl);
    //muestraLista(pl);
    iniciac(&cola);
    cargarCola(&cola);
    //muestraCola(&cola);
    opera(pl,cola);



    return 0;
}
