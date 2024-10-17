#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdacola.h"
#define MAXCAJA 4

typedef struct{
    char IDcajaNueva[MAXCAJA];
    int K;
} ELEMCAJAS;

typedef struct nodo{
    char IDcaja[MAXCAJA];
    float saldoCaja;
    TCOLA clientes;
    struct nodo* sig;
} NODO;

typedef NODO* TLISTA;

void cargaLista(TLISTA *lista){
    FILE* arch = fopen("LISTA.txt", "rt");
    TLISTA act;
    TELEMENTOC elem;
    int dimCola, i;
    char IDcaja[MAXCAJA];
    float saldoCaja;
    *lista = NULL;
    if(!arch){
        printf("NULO LISTA");
    }
    else{
        while(fscanf(arch, "%s %f %d", IDcaja, &saldoCaja, &dimCola) == 3){
            if(!*lista){
                *lista = (TLISTA)malloc(sizeof(NODO));
                act = *lista;
            }
            else{
                act->sig = (TLISTA)malloc(sizeof(NODO));
                act = act->sig;
            }
            strcpy(act->IDcaja, IDcaja);
            act->saldoCaja = saldoCaja;
            iniciac(&act->clientes);
            for(i = 0; i<dimCola; i++){
                fscanf(arch, "%f %c", &elem.importe, &elem.Tdescuento);
                ponec(&act->clientes, elem);
            }
        }
        act->sig = NULL;
    }
    fclose(arch);
}

void muestraL(TLISTA lista){
    TELEMENTOC elem;
    TCOLA aux;

    while(lista){
        iniciac(&aux);
        printf("%s %.2f\n", lista->IDcaja, lista->saldoCaja);
        while(!vaciac(lista->clientes)){
            sacac(&lista->clientes, &elem);
            ponec(&aux, elem);
            printf("%.2f %c\t", elem.importe, elem.Tdescuento);
        }
        printf("\n");
        while(!vaciac(aux)){
            sacac(&aux, &elem);
            ponec(&lista->clientes, elem);
        }
        lista = lista->sig;
    }
}

void opera(TLISTA* lista){
    FILE* arch = fopen("CAJAS.txt", "rt");
    ELEMCAJAS elemC;
    TCOLA auxCola;
    TELEMENTOC elem;
    TLISTA act = *lista, ant = NULL, elim, nuevo;
    int contCola, i, contCajaAgregada =0, contCajaElim =0;
    float saldoTotal;
    if(!arch){
        printf("NULO arch");
    }
    else{
        while(fscanf(arch, "%s %d", elemC.IDcajaNueva, &elemC.K) == 2){
            ant = NULL;
            act = *lista;
            while(act && strcmp(act->IDcaja, elemC.IDcajaNueva) != 0){            //ya que el archivo esta desordenado
                ant = act;
                act = act->sig;
            }
            if(act){                             /// SI EL IDENTIFICADOR EXISTE
                contCola = 0;
                iniciac(&auxCola);
                saldoTotal = 0;
                while(!vaciac(act->clientes)){
                    sacac(&act->clientes, &elem);
                    ponec(&auxCola, elem);
                    contCola++;
                }
                if(elemC.K >= contCola){        //K > CANT CLIENTES
                    contCajaElim++;
                    while(!vaciac(auxCola)){
                        sacac(&auxCola, &elem);
                        if(elem.Tdescuento == 'S')
                            saldoTotal+= elem.importe - (elem.importe)*0.1;
                        else
                            saldoTotal+= (elem.importe);
                    }
                    act->saldoCaja += saldoTotal;
                    printf("Caja %s eliminada. Saldo $ %.2f\n\n", act->IDcaja, act->saldoCaja);
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
                }                                       // K < CANT CLIENTES
                else{
                    for(i=0; i<elemC.K; i++){           //saco los clientes que me dio K
                        sacac(&auxCola, &elem);
                        if(elem.Tdescuento == 'S')
                            saldoTotal+= elem.importe - (elem.importe)*0.1;
                        else
                            saldoTotal+= (elem.importe);

                    }
                    while(!vaciac(auxCola)){            //el resto de clientes lo meto en la cola original devuelta
                        sacac(&auxCola, &elem);
                        ponec(&act->clientes, elem);
                    }
                    act->saldoCaja += saldoTotal;
                }
            }                                           /// SI EL IDENTIFICADOR NO EXISTE
            else{
                contCajaAgregada++;
                nuevo = (TLISTA)malloc(sizeof(NODO));
                strcpy(nuevo->IDcaja, elemC.IDcajaNueva);
                nuevo->saldoCaja = elemC.K;

                iniciac(&nuevo->clientes);
                act = *lista;
                ant = NULL;
                while(act && strcmp(act->IDcaja, nuevo->IDcaja) < 0){       ///CORREGIR me tira que b03 es mas grande que b04
                    ant = act;
                    act = act->sig;
                }
                if(!ant){
                    nuevo->sig = *lista;
                    *lista = nuevo;
                    act = *lista;

                }
                else{
                    nuevo->sig = act;
                    ant->sig = nuevo;
                }
            }
        }

        printf("%d Cajas agregadas", contCajaAgregada);
        printf("\t %d Cajas eliminadas\n\n", contCajaElim);
        fclose(arch);
    }
}

void muestraL2(TLISTA lista){
    TELEMENTOC elem;
    TCOLA aux;
    float acumCajas=0;
    int cantCajas=0, contClientes=0;

    while(lista){
        iniciac(&aux);
        printf("%s %.2f\n", lista->IDcaja, lista->saldoCaja);
        acumCajas += lista->saldoCaja;
        cantCajas++;
        while(!vaciac(lista->clientes)){
            sacac(&lista->clientes, &elem);
            contClientes++;
            printf("%.2f %c\t", elem.importe, elem.Tdescuento);
        }
        printf("\n");
        lista = lista->sig;
    }
    printf("\n\nPromedio de las cajas $%.2f\n", acumCajas/cantCajas);
    printf("Cantidad de clientes en espera promedio x caja: %.2f", (float)contClientes/cantCajas);
}

int main()
{
    TLISTA lista;
    cargaLista(&lista);
    printf("LISTA ORGINIAL\n\n");
    muestraL(lista);
    opera(&lista);
    printf("\n\n\n LISTA ACTUALIZADA: \n\n");
    muestraL2(lista);
    return 0;
}
