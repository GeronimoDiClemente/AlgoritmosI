#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdacolad.h"
#define MAX 5

typedef struct nodol
{
    char codDestino[MAX];
    TCOLA cola;
    struct nodo *sig;
}NODOL;
typedef NODOL *TLISTA;

typedef struct
{
    char codDestino[MAX];
    int asientos;
}libres;

void cargaLista (TLISTA *pl)
{
    TLISTA ult;
    FILE *arch;
    char codDestino[MAX];
    int dimCola,i;
    TELEMENTOC numero;
    arch = fopen("aerolinea.txt","rt");
    if (arch == NULL)
        printf("NULO");
    else
    {
        *pl=NULL;
        while(fscanf(arch,"%s %d",codDestino,&dimCola) == 2)
        {
            if (*pl == NULL)
            {
                *pl = (TLISTA)malloc(sizeof(NODOL));
                ult = *pl;
            }
            else
            {
                ult->sig = (TLISTA)malloc(sizeof(NODOL));
                ult = ult->sig;
            }
            strcpy(ult->codDestino,codDestino);
            iniciac(&ult->cola);
            for (i=0;i<dimCola;i++)
            {
                fscanf(arch,"%d",&numero);
                ponec(&ult->cola,numero);
            }
        }
        ult->sig = NULL;
    }
    fclose(arch);
}

void muestraLista (TLISTA pl)
{
    TELEMENTOC numero;
    while (pl != NULL)
    {
        printf("%s\t",pl->codDestino);
        while (!vaciac(pl->cola))
        {
            sacac(&pl->cola,&numero);
            printf("%d\t",numero);
        }
        printf("\n");
        pl = pl->sig;
    }
}

void cargarLibres (libres v[], int *dimLib)
{
    int i;
    printf ("Ingrese la dimension del vector");
    scanf("%d",dimLib);
    for (i=0;i<*dimLib;i++)
    {
        printf ("Ingrese el codigo del destino\n");
        scanf("%s",v[i].codDestino);
        printf ("Ingrese cantidad de asientos libres\n");
        scanf("%d",&v[i].asientos);
    }
}

void muestraTabla(libres vec[], int dim)
{
    int i;
    for(i = 0; i < dim; i++)
        printf("%s %d\n", vec[i].codDestino, vec[i].asientos);
}
int main()
{
    int dimLib;
    TLISTA pl;
    libres v[4];
    cargaLista(&pl);
    muestraLista(pl);
    cargarLibres(v,&dimLib);
    muestraTabla(v,dimLib);
    return 0;
}
