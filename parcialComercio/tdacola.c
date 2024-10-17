#include "tdacola.h"
void iniciac(TCOLA *c) {
    c->pri = -1;
    c->ult = -1;
}

int vaciac(TCOLA cola) {
    return cola.pri == -1;
}

int llenac(TCOLA cola) {
    return cola.ult == MAXCOLA-1;
}

void ponec(TCOLA* c, TELEMENTOC e){
    if(c->ult != MAXCOLA)
        c->items[++(c->ult)] = e;
    if(c->pri == -1)
        c->pri = 0;
}

void sacac(TCOLA *c, TELEMENTOC *e) {
    if (c->pri != -1){
       *e = c->items[c->pri];
       if (c->pri == c->ult)
          c->pri = c->ult = -1;
        else
          c->pri++;
    }
}

void consultac(TCOLA cola, TELEMENTOC *e) {
    if (cola.pri != -1)
       *e = cola.items[cola.pri];
}
