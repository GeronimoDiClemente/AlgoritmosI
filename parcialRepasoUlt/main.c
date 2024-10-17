#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdacola.h"
#define MAXSTR 50

typedef struct nodito{
    int tipo, cant;
    struct nodito* sig;
} NODITO;

typedef NODITO* TSUBLISTA;

typedef struct nodo{
    char formacion[MAXSTR];
    TSUBLISTA vagones;
    struct nodo* sig;
} NODO;

typedef NODO* TLISTA;

void cargaC(TCOLA* c){
    TELEMENTOC elem;
    FILE* arch = fopen("COLA.txt", "rt");

    if(!arch){
        printf("NULO COLA");
    }
    else{
        iniciac(c);
        while(fscanf(arch, "%s %d", elem.formacion, &elem.tipo) == 2){
            ponec(c, elem);
        }
        fclose(arch);
    }
}

void muestraC(TCOLA cola){
    TELEMENTOC elem;
    while(!vaciac(cola)){
        sacac(&cola, &elem);
        printf("%s %d", elem.formacion, elem.tipo);
    }
}

void opera(TLISTA* lista, TCOLA cola){
    TELEMENTOC elem;
    TLISTA ant, act, nuevo;
    TSUBLISTA sant, sact, snuevo;
    *lista = NULL;
    char formacionAct[MAXSTR];

    while(!vaciac(cola)){
        sacac(&cola, &elem);
        strcpy(formacionAct, elem.formacion);
        nuevo = (TLISTA)malloc(sizeof(NODO));
        strcpy(nuevo->formacion, formacionAct);
        nuevo->vagones = NULL;
        if(!*lista){
            nuevo->sig = NULL;
            *lista = nuevo;
            ant = NULL;
            act = *lista;
            act->vagones = NULL;
        }
        else{
            if(strcmp(elem.formacion, act->formacion) != 0){                // si son distintos hago nodos
                while(act && strcmp(nuevo->formacion,act->formacion) > 0){
                    ant = act;
                    act = act->sig;
                }
                if(!ant){
                    nuevo->sig = *lista;
                    *lista = nuevo;
                    act = *lista;
                    act->vagones = NULL;
                }
                else{
                    nuevo->sig = act;
                    ant->sig = nuevo;
                }
            }
            else{                                                           //si son iguales cargo sub
                snuevo = (TSUBLISTA)malloc(sizeof(NODITO));
                // snuevo->cant++; agregar en insercion
                snuevo->tipo = elem.tipo;
                if(!act->vagones){          //si es el primer nodito
                    snuevo->sig = NULL;
                    act->vagones = snuevo;
                    sact = act->vagones;
                    sant = NULL;
                }
                else{
                    if(sact->tipo != elem.tipo){
                        while(act && snuevo->tipo > sact->tipo){
                            sant = sact;
                            sact = sact->sig;
                        }
                        if(!sant){
                            snuevo->sig = act->vagones;
                            act->vagones = snuevo;
                            sact = act->vagones;

                        }
                        else{
                            snuevo->sig = sact;
                            sant->sig = snuevo;
                        }
                        sact->cant = 1;
                    }
                    else{
                        sact->cant++;
                    }
                }
            }
        }
    }
}

void muestraL(TLISTA lista){
    while(lista){
        printf("%s\n\n", lista->formacion);
        while(lista->vagones){
            printf("%d %d\n\n", lista->vagones->cant, lista->vagones->tipo);
            lista->vagones = lista->vagones->sig;
        }
        lista = lista->sig;
    }
}

int main()
{
    TCOLA cola;
    TLISTA lista;
    cargaC(&cola);
    //muestraC(cola);
    opera(&lista, cola);
    muestraL(lista);
    return 0;
}
