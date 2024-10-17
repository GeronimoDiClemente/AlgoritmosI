#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdacola.h"
#define MAXCAJA 4

typedef struct nodo
{
    char IDcaja[MAXCAJA];
    float saldo;
    int dimCola;
    TCOLA cola;
    struct nodo *sig;
}NODO;
typedef NODO *TLISTA;

void cargaLista (TLISTA *pl)
{
    TELEMENTOC registro;
    char IDcaja[MAXCAJA],descuento;
    float saldo,importe;
    int dimCola,i;
    TLISTA ult;
    FILE *arch;
    arch = fopen("archLista.txt","rt");
    *pl = NULL;
    if (arch == NULL)
        printf ("NULO");
    else
    {
        while (fscanf(arch,"%s %f %d",IDcaja,&saldo,&dimCola) == 3)
        {
            if (*pl == NULL)
            {
                *pl = (TLISTA)malloc(sizeof(NODO));
                ult =*pl;
            }
            else
            {
                ult->sig = (TLISTA)malloc(sizeof(NODO));
                ult = ult->sig;
            }
            strcpy(ult->IDcaja,IDcaja);
            ult->saldo = saldo;
            ult->dimCola = dimCola;
            iniciac(&ult->cola);
            for (i=0;i<dimCola;i++)
            {
                fscanf(arch,"%f %c",&registro.importe,&registro.descuento);
                ponec(&ult->cola,registro);
            }

        }
        ult->sig = NULL;
    }
    fclose(arch);
}

void muestraLista (TLISTA pl)
{
    TCOLA aux;
    TELEMENTOC registro;
    while (pl != NULL)
    {
        aux = pl->cola;
        printf("%s %.2f\n",pl->IDcaja,pl->saldo);
        while (!vaciac(aux))
        {
            sacac(&aux,&registro);
            printf("%.2f %c\n",registro.importe,registro.descuento);
        }
        printf("\n");
        pl = pl->sig;
    }
}
void opera (TLISTA *pl)
{
    TELEMENTOC registro;
    int K, i;
    char IDcaja[MAXCAJA];
    FILE *arch;
    TLISTA act, ant, nuevo, elim;

    arch = fopen("identificador.txt", "rt");
    if (arch == NULL)
    {
        printf("Error al abrir el archivo 'identificador.txt'\n");
        return;
    }

    while (fscanf(arch, "%s %d", IDcaja, &K) == 2)
    {
        ant = NULL;
        act = *pl;

        // Busca la caja con el ID indicado
        while (act != NULL && strcmp(act->IDcaja, IDcaja) != 0)
        {
            ant = act;
            act = act->sig;
        }

        if (act != NULL) // Si encontró la caja
        {
            if (K >= act->dimCola) // Recorre toda la caja
            {
                for (i = 0; i < act->dimCola; i++)
                {
                    sacac(&act->cola, &registro);
                    if (registro.descuento == 'S')
                        registro.importe -= registro.importe * 0.1;
                    act->saldo += registro.importe;
                }

                printf("CAJA ELIMINADA %s saldo %.2f\n", act->IDcaja, act->saldo);

                // Elimina la caja
                if (ant == NULL) // Si es el primer nodo
                {
                    elim = *pl;
                    *pl = (*pl)->sig;
                    free(elim);
                    act = *pl; // Avanza al siguiente nodo
                }
                else
                {
                    ant->sig = act->sig;
                    free(act);
                    act = ant->sig; // Avanza al siguiente nodo
                }
            }
            else // Recorre solo K elementos
            {
                for (i = 0; i < K; i++)
                {
                    sacac(&act->cola, &registro);
                    if (registro.descuento == 'S')
                        registro.importe -= registro.importe * 0.1;
                    act->saldo += registro.importe;
                }
            }
        }
        else // Si no encontró la caja, inserta una nueva
        {
            nuevo = (TLISTA)malloc(sizeof(NODO));
            strcpy(nuevo->IDcaja, IDcaja);
            nuevo->saldo = K;
            nuevo->dimCola = 0; // Asumimos que la cola empieza vacía
            iniciac(&nuevo->cola);
            nuevo->sig = NULL;

            // Inserta la nueva caja en la posición correcta
            if (ant == NULL) // Si debe ir al inicio de la lista
            {
                nuevo->sig = *pl;
                *pl = nuevo;
            }
            else // Si debe ir en el medio o al final
            {
                nuevo->sig = act;
                ant->sig = nuevo;
            }
        }
    }

    fclose(arch);
}


int main()
{
    TLISTA pl;
    cargaLista(&pl);
    opera(&pl);
    muestraLista(pl);
    return 0;
}
