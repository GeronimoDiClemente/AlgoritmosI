#include <stdio.h>
#include <stdlib.h>
#include "tdacola.h"
#include "tdapilad.h"
#define MAXPREMIO 6

typedef struct nodo{
    char premioID[MAXPREMIO];
    float puntosN;
    int cantDisponible;
    struct nodo* sig;
} NODO;

typedef NODO* TLISTA;

void cargaL(TLISTA *lista){
    FILE* arch = fopen("LISTA.txt", "rt");
    TLISTA ult;
    *lista = NULL;
    float puntosN;
    int cantDisponible;
    char premioID[MAXPREMIO];

    if(!arch){
        printf("LISTA nulo");
    }
    else{
        while(fscanf(arch, "%s %f %d", premioID, &puntosN, &cantDisponible) == 3){
            if(!*lista){
                *lista = (TLISTA)malloc(sizeof(NODO));
                ult = *lista;
            }
            else{
                ult->sig = (TLISTA)malloc(sizeof(NODO));
                ult = ult->sig;
            }
            strcpy(ult->premioID, premioID);
            ult->puntosN = puntosN;
            ult->cantDisponible = cantDisponible;
        }
        ult->sig = NULL;
        fclose(arch);
    }
}

void muestraL(TLISTA lista){
    while(lista){
        printf("%s %.2f %d\n", lista->premioID, lista->puntosN, lista->cantDisponible);
        lista = lista->sig;
    }
}

void cargaP(TPILA *pila){
    FILE* arch = fopen("PILA.txt", "rt");
    TELEMENTOP elem;

    if(!arch){
        printf("PILA NULO");
    }
    else{
        iniciap(pila);
        while(fscanf(arch, "%s %s %f", elem.clienteID, elem.premioID, &elem.pAcum) == 3)
            ponep(pila, elem);
        fclose(arch);
    }
}

void muestraP(TPILA pila){
    TELEMENTOP elem;
    while(!vaciap(pila)){
        sacap(&pila, &elem);
        printf("%s %s %.2f\n", elem.clienteID, elem.premioID, elem.pAcum);
    }
}

void opera(TLISTA *lista, TPILA pila, TCOLA *cola){
    TLISTA act, ant, elim;
    TPILA pAux;
    TELEMENTOC elemC;
    TELEMENTOP elemP;

    while(!vaciap(pila)){
        act = *lista;
        ant = NULL;
        sacap(&pila, &elemP);
        while(act && strcmp(act->premioID, elemP.premioID) != 0){
            ant = act;
            act = act->sig;
        }
        if(act){                //encontró el premio
            if(elemP.pAcum < act->puntosN){     // NO tiene puntos necesarios
                strcpy(elemC.clienteID, elemP.clienteID);
                ponec(cola, elemC);
            }
            else{                               // SI tiene puntos necesarios
                if(act->cantDisponible > 0)        // quedan premios dispo
                    (act->cantDisponible)--;
                if (act->cantDisponible == 0){
                    if(!ant){                   //no hay mas productos
                        elim = *lista;
                        *lista = (*lista)->sig;
                        free(elim);
                        act = *lista;
                    }
                    else{
                        ant->sig = act->sig;
                        free(act);
                        act = ant->sig;
                    }
                }
            }
        }
        else{                                               //no encontro el premio
            strcpy(elemC.clienteID, elemP.clienteID);
            ponec(cola, elemC);
        }
    }
}

void muestraC(TCOLA cola){
    TELEMENTOC elemC;
    while(!vaciac(cola)){
        sacac(&cola, &elemC);
        printf("%s\t", elemC.clienteID);
    }
}


int main()
{
    TPILA pila;
    TCOLA cola;
    TLISTA lista;
    cargaL(&lista);
    printf("LISTA ORIGINAL: \n\n");
    muestraL(lista);
    cargaP(&pila);
    //muestraP(pila);
    iniciac(&cola);
    printf("\n\nLISTA ACTUALIZADA DE PREMIOS: \n\n");
    opera(&lista, pila, &cola);
    muestraL(lista);
    printf("\n\nCOLA DE ESPERA: \n\n");
    muestraC(cola);

    return 0;
}
