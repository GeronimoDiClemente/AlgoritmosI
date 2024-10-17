#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdapila.h"
#include "tdacola.h"
#define MAXCOD 6

typedef struct nodo
{
    char codPremio[MAXCOD];
    float puntosNecesarios;
    int cantidad;
    struct nodo *sig;
}NODO;
typedef NODO *TLISTA;

void cargaLista (TLISTA *pl)
{
    TLISTA ult;
    char codPremio[MAXCOD];
    float puntosNecesarios;
    int cantidad;
    FILE *arch;
    arch = fopen("Lista.txt","rt");
    *pl = NULL;
    while (fscanf(arch,"%s %f %d",codPremio,&puntosNecesarios,&cantidad) == 3)
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
        strcpy(ult->codPremio,codPremio);
        ult->puntosNecesarios = puntosNecesarios;
        ult->cantidad = cantidad;
    }
    ult->sig = NULL;
    fclose(arch);
}

void muestraLista (TLISTA pl)
{
    while (pl != NULL)
    {
        printf("%s %.2f %d\n",pl->codPremio,pl->puntosNecesarios,pl->cantidad);
        pl = pl->sig;
    }
}

void cargaPila (TPILA *pila)
{
    TELEMENTOP registro;
    FILE *arch;
    arch = fopen ("Pila.txt","rt");
    if (arch == NULL)
        printf("NULO");
    else
    {
        while (fscanf(arch,"%s %s %f",registro.codCliente,registro.codPremio,&registro.acumulados) == 3)
            ponep(pila,registro);
    }
    fclose(arch);
}

void muestraPila (TPILA pila)
{
    TELEMENTOP registro;
    while (!vaciap(pila))
    {
        sacap(&pila,&registro);
        printf("%s %s %.2f\n",registro.codCliente,registro.codPremio,registro.acumulados);
    }

}

void muestraCola (TCOLA cola)
{
    TELEMENTOC registro;
    while (!vaciac(cola))
    {
        sacac(&cola,&registro);
        printf("%s\n",registro.codCliente);
    }
}

void opera (TPILA pila, TLISTA *pl,TCOLA *cola)
{
    TLISTA act,ant,elim;
    TELEMENTOP registro;
    TELEMENTOC registroc;
    while (!vaciap(pila))
    {
        act = *pl;
        ant = NULL;
        sacap(&pila,&registro);
        while (act != NULL && strcmp(act->codPremio,registro.codPremio)!=0)
        {
            ant = act;
            act = act->sig;
        }
        if (act != NULL) //ENCONTRO EL NODO
        {
            if (registro.acumulados >= act->puntosNecesarios)
            {
                (act->cantidad)--;
            }
            else //NO TIENE PUNTOS NECESARIOS
            {
                strcpy(registroc.codCliente,registro.codCliente);
                ponec(cola,registroc);
            }
            if (act->cantidad == 0)//ELIMINAR NODO
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
        }
        else
        {
            strcpy(registroc.codCliente,registro.codCliente);
            ponec(cola,registroc);

        }
    }
}
int main()
{
    TLISTA pl;
    TPILA pila;
    TCOLA cola;
    cargaLista(&pl);
    printf("LISTA ORIGINAL\n\n");
    muestraLista(pl);
    iniciap(&pila);
    iniciac(&cola);
    cargaPila(&pila);
    printf("\nPILA\n\n");
    muestraPila(pila);
    opera(pila,&pl,&cola);
    printf("\nLISTA FINAL\n\n");
    muestraLista(pl);
    printf("\nCOLA\n\n");
    muestraCola(cola);
    return 0;
}
