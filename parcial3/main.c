#include <stdio.h>
#include <stdlib.h>
#include "tdapilad.h"
#include <string.h>
#define MAXMOZO 4

typedef struct nodo{
    char mozoID[MAXMOZO];
    TPILA importes;
    struct nodo* sig;
} NODO;

typedef NODO* TLISTA;

void cargaL(TLISTA* lista){
    FILE* arch = fopen("restaurante.txt", "rt");
    TLISTA ult;
    char mozoID[MAXMOZO];
    int dimPila, i;
    TELEMENTOP elem;
    *lista = NULL;

    if(!arch){
        printf("NULO restaurante");
    }
    else{
        while(fscanf(arch, "%s %d", mozoID, &dimPila) == 2){
            if(!*lista){
                *lista = (TLISTA)malloc(sizeof(NODO));
                ult = *lista;
            }
            else{
                ult->sig = (TLISTA)malloc(sizeof(NODO));
                ult = ult->sig;
            }
            strcpy(ult->mozoID, mozoID);
            iniciap(&ult->importes);
            for(i=0; i<dimPila; i++){
                fscanf(arch, "%f", &elem);
                ponep(&ult->importes, elem);
            }
        }
        ult->sig = NULL;
        fclose(arch);
    }
}

void muestraL(TLISTA lista){
    TELEMENTOP elem;
    while(lista){
        printf("%s ", lista->mozoID);
        while(!vaciap(lista->importes)){
            sacap(&lista->importes, &elem);
            printf("%.2f\t", elem);
        }
        printf("\n");
        lista = lista->sig;
    }
}

void opera(TLISTA* lista, char mozoX[]){
    TLISTA ant, act, elim;
    act = *lista;
    ant = NULL;
    TELEMENTOP elem;
    TPILA auxPila;
    float acumTotal=0, acumXMozo=0;
    int contMozos=0, contMesasTotal=0, esMozo, porc = 0, recaudado, contMesasMozo=0;
    while(act){
        contMozos++;
        iniciap(&auxPila);
        esMozo = 0;
        while(!vaciap(act->importes)){
            sacap(&act->importes, &elem);
            ponep(&auxPila, elem);
            contMesasTotal++;
            if(!strcmp(act->mozoID, mozoX)) {           //lo hago adentro asi no me cuenta todos
                acumXMozo += elem;
                esMozo = 1;
                contMesasMozo++;
            }
            acumTotal += elem;
        }

        while(!vaciap(auxPila)) {                   //Re inserto elementos en la pila
            sacap(&auxPila, &elem);
            ponep(&act->importes, elem);
        }


        if(esMozo){                                //si es el mozo elimina
            if(!ant){
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
        else{                                      // si no es el mozo avanza
            ant = act;
            act = act->sig;
        }
    }

    porc = (acumXMozo*100)/acumTotal;

    if(porc >= 40)
        recaudado = 50;
    else if(porc >= 30)
        recaudado = 35;
        else if(porc>=15)
            recaudado = 18;
            else
                recaudado = 0;

    if(contMesasMozo > contMesasTotal/(float)contMozos)
        recaudado += 10;

    printf("Codigo de Mozo %s: $ %.2f\n\n", mozoX, (float)recaudado);
    printf("Total que recaudo el restaurante: %.2f\n\n", acumTotal);
    printf("Cantidad de mesas promedio atendido por mozo: %.2f\n\n", contMesasTotal/(float)contMozos);
}

int main()
{
    char mozoX[MAXMOZO];
    TLISTA lista;
    cargaL(&lista);
    //muestraL(lista);
    printf("Ingrese el mozo que desea liquidar: ");
    scanf("%s", mozoX);
    opera(&lista, mozoX);
    muestraL(lista);
    return 0;
}
