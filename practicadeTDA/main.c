#include <stdio.h>
#include <stdlib.h>
/*
/// .h PILA ESTATICA

#define MAXPILA 20

typedef char TELEMENTOP;

typedef struct{
    TELEMENTOP vp[MAXPILA];
    int tope;
} TPILA;

void iniciap(TPILA* p);
void llenap(TPILA p);
void vaciap(TPILA p);
void ponep(TPILA* p, TELEMENTOP elem);
void sacap(TPILA* p, TELEMENTOP *elem);

/// .c PILA ESTATICA            ///tope es 0 en pila

void iniciap(TPILA* p){
    p->tope = 0;
}

void llenap(TPILA p){
    return p.tope == MAXPILA;
}

void vaciap(TPILA p){
    return p.tope == 0;
}

void ponep(TPILA* p, TELEMENTOP elem){
    if(p->tope != MAXPILA)
        p->vp[(p->tope)++] = elem;
}

void sacap(TPILA* p, TELEMENTOP* elem){
    if(p->tope != 0)
        *elem = p->vp[--(p->tope)];
}

/// .h PILA DINAMICA

typedef TELEMENTOC dato;

typedef struct nodop{
    TELEMENTOP dato;
    struct nodop* sig;
} NODOP;

typedef NODOP* TPILA;

void iniciap(TPILA* p);
void llenap(TPILA p);
void vaciap(TPILA p);
void ponep(TPILA* p, TELEMENTOP elem);
void sacap(TPILA* p, TELEMENTOP *elem);

/// .c PILA DINAMICA

void iniciap(TPILA* p){
    *p = NULL;
}

void vaciap(TPILA p){
    return p == NULL;
}

void ponep(TPILA* p, TELEMENTOP elem){
    TPILA nuevo;
    nuevo = (TPILA)malloc(sizeof(NODOP));
    nuevo->dato = elem;
    nuevo->sig = *p;
    *p = nuevo;
}

void sacap(TPILA* p, TELEMENTOP* elem){
    TPILA elim;
    if(*p){
        elim = *p;
        *elem = (*p)->dato;
        *p = (*p)->sig;
        free(elim);
    }
}

/// .h COLA ESTATICA

#define MAXCOLA 50

typedef tipoDato TELEMENTOC;

typedef struct{
    TELEMENTOC item;
    int pri, ult;
} TCOLA;

void iniciac(TCOLA* c);
int vaciac(TCOLA c);
int llenac(TCOLA c);
void ponec(TCOLA* c, TELEMENTOC elem);
void sacac(TCOLA* c, TELEMENTOC* elem);

/// .c COLA ESTATICA

void iniciac(TCOLA* c){
    c->pri = c->ult = -1;
}

int vaciac(TCOLA c){
    return c.pri == -1;
}

int llenac(TCOLA c){
    return c.ult == MAXCOLA-1;
}

void ponec(TCOLA* c, TELEMENTOC elem){
    if(c.ult != MAXCOLA-1)
        c->item[++(c->ult)] = elem;
    if(c->pri == -1)
        c->pri = 0;
}

void sacac(TCOLA* c, TELEMENTOC* elem){
    if(c->pri != -1)
        *elem = c->item[c->pri];
    if(c->pri == c->ult)
        c->pri = c->ult = -1;
    else
        c->pri++;
}

/// .h cola dinamica

typedef tipoDato TELEMENTOC;

typedef struct nodoc{
    TELEMENTOC item;
    struct nodoc* sig;
} NODOC;

typedef struct{
    NODOC* pri;
    NODOC* ult;
} TCOLA;


/// .c cola dinamica


XD
*/

/// .h pila estatica

#define MAXPILA 20

typedef tipoDato TELEMENTOP;

typedef struct{
    TELEMENTOP vp[MAXPILA];
    int tope;
} TPILA;

void iniciap(TPILA* p){
    p->tope = 0;
}

int vaciap(TPILA p){
    return p.tope == 0;
}

int llenap(TPILA p){
    return p.tope == MAXPILA;
}

void ponep(TPILA* p, TELEMENTOP elem){
    if(p->tope != MAXPILA)
        p->vp[(p->tope)++] = elem;
}

void sacap(TPILA* p, TELEMENTOP *elem){
    if(p->tope != 0)
        *elem = p->vp[--(p->tope)];
}

/// .h COLA ESTATICA
#define MAXCOLA 50

typedef tipoDato TELEMENTOC;

typedef struct{
    TELEMENTOC item;
    int pri, ult;
} TCOLA;

void iniciac(TCOLA* c){
    c->pri = c->ult = -1;
}

int vaciac(TCOLA c){
    return c->pri == -1;
}

int llenac(TCOLA c){
    return c->ult == MAXCOLA-1;
}

void ponec(TCOLA* c, TELEMENTOC elem){
    if(c->ult != MAXCOLA-1)
        c->item[++(c->ult)] = elem;
    if(c->pri == -1)
        c->pri = 0;
}

void sacac(TCOLA* c, TELEMENTOC* elem){
    if(c->ult != -1)
        *elem = c->item[c->pri];
    if(c->pri == c->ult)
        c->pri = c->ult = -1;
    else
        c->pri++;
}

/// .c pila dinamica

void iniciap(TPILA *p){
    *p = NULL;
}

int vaciap(TPILA p){
    return p == NULL;
}

void ponep(TPILA* p, TELEMENTOP elem){
    TPILA nuevo;
    nuevo = (TPILA)malloc(sizeof(NODOP));
    nuevo->dato = elem;
    nuevo->sig = *p;
    *p = nuevo;
}

void sacap(TPILA* p, TELEMENTOP* elem){
    TPILA elim;
    if(*p){
        elim = *p;
        *elem = (*p)->dato;
        *p = (*p)->sig;
        free(elim);
    }
}





















