#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdacola.h"
#define MAXCONT 4


typedef struct nodito{
    char contID[MAXCONT];
    struct nodito* sig;
} NODITO;

typedef NODITO* TSUBLISTA;

typedef struct nodo{
    int puertoID;
    TSUBLISTA containers;
    struct nodo* sig;
} NODO;

typedef NODO* TLISTA;

void cargaL(TLISTA* lista){
    FILE* arch = fopen("informacion.txt", "rt");
    int puertoID, dimSub,i;
    char contID[MAXCONT];
    TLISTA ult;
    TSUBLISTA sult;
    *lista = NULL;

    if(!arch){
        printf("NULO INFO");
    }
    else{
        while(fscanf(arch, "%d %d", &puertoID, &dimSub) == 2){
            if(!*lista){
                *lista = (TLISTA)malloc(sizeof(NODO));
                ult = *lista;
            }
            else{
                ult->sig = (TLISTA)malloc(sizeof(NODO));
                ult = ult->sig;
            }
            ult->puertoID = puertoID;
            ult->containers = NULL;
            for(i = 0; i<dimSub; i++){
                fscanf(arch, "%s", contID);
                if(!ult->containers){
                    ult->containers = (TLISTA)malloc(sizeof(NODO));
                    sult = ult->containers;
                }
                else{
                    sult->sig = (TLISTA)malloc(sizeof(NODO));
                    sult = sult->sig;
                }
                strcpy(sult->contID, contID);

            }
            sult->sig = NULL;
        }
        ult->sig = NULL;
        fclose(arch);
    }
}

void muestraL(TLISTA lista){
    TSUBLISTA aux;
    while(lista){
        printf("%d\n", lista->puertoID);
        aux = lista->containers;
        while(aux){
            printf("%s\n", aux->contID);
            aux = aux->sig;
        }
        lista = lista->sig;
    }
}

void cargaC(TCOLA* cola){
    FILE* arch = fopen("duplas.txt", "rt");
    TELEMENTOC elem;


    if(!arch){
        printf("cola nulo");
    }
    else{
        iniciac(cola);
        while(fscanf(arch, "%d %s", &elem.puertoID, elem.contID) == 2){
            ponec(cola, elem);
        }
        fclose(arch);
    }
}

void muestraC(TCOLA cola){
    TELEMENTOC elem;
    while(!vaciac(cola)){
        sacac(&cola, &elem);
        printf("%d %s\n", elem.puertoID, elem.contID);
    }

}

void opera(TLISTA lista, TCOLA cola){
    TSUBLISTA sact, sant, snuevo;
    TLISTA act, ant; //para reiniciar lista
    TELEMENTOC elem;
    int contRepetidos=0, K, i;


    printf("\n\nIngrese un K para analizar: ");
    scanf("%d", &K);

    for(i=0; i<K; i++){
        if(!vaciac(cola)){
            sacac(&cola, &elem);
            act = lista;
            ant = NULL;
            while(act && elem.puertoID != act->puertoID){
                ant = act;
                act = act->sig;
            }
            if(act){        // si encontro
                sact = act->containers;
                sant = NULL;
                while(sact && strcmp(elem.contID, sact->contID) > 0){     // aca comprubea que el container no existe
                    sant = sact;
                    sact = sact->sig;
                }
                if(sact && strcmp(elem.contID, sact->contID) != 0){       //se que tengo que insertar algo y no esta repetido
                    snuevo = (TSUBLISTA)malloc(sizeof(NODITO));
                    strcpy(snuevo->contID, elem.contID);
                    if(!sant){
                        snuevo->sig = act->containers;
                        act->containers = snuevo;
                    }
                    else{
                        snuevo->sig = sact;
                        sant->sig = snuevo;
                    }
                }
                else if(!sact){                                         // si el puerto esta vacio o  es el ultimo elemento (sact == NULL)
                    snuevo = (TSUBLISTA)malloc(sizeof(NODITO));
                    strcpy(snuevo->contID, elem.contID);
                    if(!sant){
                        snuevo->sig = act->containers;
                        act->containers = snuevo;
                    } else {
                        snuevo->sig = sact;
                        sant->sig = snuevo;
                    }
                }
                else{                                               // solamente se repite
                    contRepetidos++;
                }
            }
        }
    }
    printf("\n\nCantidad de containers repetidos: %d\n\n", contRepetidos);
}

int main()
{
    TLISTA lista;
    TCOLA cola;
    cargaL(&lista);
    muestraL(lista);
    cargaC(&cola);
    //muestraC(cola);
    opera(lista, cola);
    printf("\n\n");
    muestraL(lista);

    return 0;
}
