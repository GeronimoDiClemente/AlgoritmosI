#include "tdapilad.h"
#include <stdlib.h>

void iniciap(TPILA *p) {
    *p = NULL;
}

int vaciap(TPILA pila) {
   return pila == NULL;
}

void ponep(TPILA *p, TELEMENTOP elem) {
    TPILA nuevo;
    nuevo = (TPILA)malloc(sizeof(NODOP));
    nuevo->sig = *p; nuevo->dato = elem;
    *p = nuevo;
}

void sacap(TPILA *p, TELEMENTOP *pelem){
    TPILA elim;
    if(*p != NULL){
        *pelem = (*p)->dato;
        elim = *p;
        *p = (*p)->sig;
        free(elim);
    }
}

void consultap(TPILA pila, TELEMENTOP *pelem) {
    if(pila != NULL)
       *pelem = pila->dato;
}

//Considerando el tamanio del heap como "inifinito" una pila dinamica nunca podria estar llena
int llenap(TPILA pila) {
    return 0;
}
