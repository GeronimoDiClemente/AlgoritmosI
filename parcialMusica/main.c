#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdapila.h"
#define MAXTITULO 31
#define MAXGENERO 11
#define MAX -999

typedef struct nodito{
    int ID;
    char titulo[MAXTITULO];
    int duracion;
    int cantReproducciones;
    struct nodito* sig;
} NODITO;

typedef NODITO* TSUBLISTA;

typedef struct nodo{
    char generoID[MAXGENERO];
    TSUBLISTA canciones;
    struct nodo* sig;
} NODO;

typedef NODO* TLISTA;

typedef struct nodo2{
    char titulo[MAXTITULO];
    int ID, duracion;
    struct nodo* sig;
} NODO2;

typedef NODO2* TLISTA2;

void cargaL(TLISTA *lista){
    FILE* arch = fopen("MUSICA.txt", "rt");
    TLISTA ult;
    TSUBLISTA sult;
    char generoID[MAXGENERO], titulo[MAXTITULO];
    int ID, duracion, cantReproducciones, dimSub, i;
    *lista = NULL;

    if(!arch){
        printf("NULO LISTA");
    }
    else{
        while(fscanf(arch, "%s %d", generoID, &dimSub) == 2){
            if(!*lista){
                *lista = (TLISTA)malloc(sizeof(NODO));
                ult = *lista;
            }
            else{
                ult->sig = (TLISTA)malloc(sizeof(NODO));
                ult = ult->sig;
            }
            strcpy(ult->generoID, generoID);
            ult->canciones = NULL;
            for(i=0; i<dimSub; i++){
                fscanf(arch, "%d %s %d %d", &ID, titulo, &duracion, &cantReproducciones);
                if(!ult->canciones){
                    ult->canciones = (TSUBLISTA)malloc(sizeof(NODITO));
                    sult = ult->canciones;
                }
                else{
                    sult->sig = (TSUBLISTA)malloc(sizeof(NODITO));
                    sult = sult->sig;
                }
                sult->ID = ID;
                sult->duracion = duracion;
                sult->cantReproducciones = cantReproducciones;
                strcpy(sult->titulo, titulo);
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
        printf("%s\n", lista->generoID);
        aux = lista->canciones;
        while(aux){
            printf("%d %s %d %d\n", aux->ID, aux->titulo, aux->duracion, aux->cantReproducciones);
            aux = aux->sig;
        }
        printf("\n\n");
        lista = lista->sig;
    }

}

void cargaP(TPILA *pila){
    TELEMENTOP elem;
    FILE* arch = fopen("PILA.txt", "rt");

    if(!arch){
        printf("null pila");
    }
    else{
        while(fscanf(arch, "%s %d", elem.generoID, &elem.minReproducciones) == 2){
            ponep(pila, elem);
        }
        fclose(arch);
    }
}

void muestraP(TPILA pila){
    TELEMENTOP elem;
    while(!vaciap(pila)){
        sacap(&pila, &elem);
        printf("%s %d\n", elem.generoID, elem.minReproducciones);
    }
}

void opera(TLISTA lista, TPILA *pila, TLISTA2 *lista2){
    TELEMENTOP elem;
    TLISTA act=lista, ant=NULL;
    TSUBLISTA sact, sant, selim;
    TLISTA2 nuevo2;
    TPILA auxPila;
    int contEliminadas, contCanciones;
    *lista2 = NULL;
    iniciap(&auxPila);

    while(!vaciap(*pila)){       //cargo elementos pila en pAux, REINSERTAR AL FINAL
        sacap(pila, &elem);
        ponep(&auxPila, elem);
    }
    while(!vaciap(auxPila)){
        sacap(&auxPila, &elem);
        act = lista;
        ant = NULL;
        while(act && strcmp(elem.generoID, act->generoID) != 0){
            ant = act;
            act = act->sig;
        }
        if(act){
            contEliminadas = 0;
            contCanciones = 0;
            sact = act->canciones;
            sant = NULL;
            while(sact){
                if(sact->cantReproducciones >= elem.minReproducciones){
                    sant = sact;
                    sact = sact->sig;
                }
                else{               //agrego a la lista2 si es menor a la minreproduccion
                    nuevo2 = (TLISTA2)malloc(sizeof(NODO2));
                    nuevo2->duracion = sact->duracion;
                    nuevo2->ID = sact->ID;
                    strcpy(nuevo2->titulo, sact->titulo);
                    if(!*lista2){           //agrego a la lista 2
                        *lista2 = nuevo2;
                        (*lista2)->sig = NULL;      ///sino espacio extra
                    }
                    else{
                        nuevo2->sig = *lista2;
                        *lista2 = nuevo2;
                    }

                    if(!sant){              //elimino de la sublista
                        selim = act->canciones;
                        act->canciones = act->canciones->sig;
                        free(selim);
                        sact = act->canciones;
                    }
                    else{
                        sant->sig = sact->sig;
                        free(sact);
                        sact = sant->sig;
                    }
                    contEliminadas++;
                }
                contCanciones++;
            }
        }
        if(contCanciones != contEliminadas)             //Elimino de la pila el que se quedo sin canciones
            ponep(pila, elem);
    }
}

void muestraL2(TLISTA2 lista2){
    int acumDuracion = 0, contCanciones = 0, MAXDURACION = MAX;
    char MAXtitulo[MAXTITULO];
    while(lista2){
        printf("%s %d %d\n", lista2->titulo, lista2->ID, lista2->duracion);
        if(lista2->duracion > MAXDURACION){
            MAXDURACION = lista2->duracion;
            strcpy(MAXtitulo, lista2->titulo);
        }
        acumDuracion+=lista2->duracion;
        contCanciones++;
        lista2 = lista2->sig;
    }
    printf("Cancion de mayor duracion: %s\n", MAXtitulo);
    printf("Duracion Promedio: %.2f\n", (float)acumDuracion/contCanciones);
}

int main()
{
    TLISTA lista;
    TPILA pila;
    TLISTA2 lista2;
    printf("LISTA ORIGINAL: \n\n");
    cargaL(&lista);
    muestraL(lista);
    //printf("\n\nPILA ORIGINAL: \n\n");
    iniciap(&pila);
    cargaP(&pila);
    //muestraP(pila);
    opera(lista, &pila, &lista2);
    printf("PILA LUEGO DEL OPERA: \n");
    muestraP(pila);
    printf("\nLISTA ACTUALIZADA:\n\n");
    muestraL2(lista2);
    return 0;
}
