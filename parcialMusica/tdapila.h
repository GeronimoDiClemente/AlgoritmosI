#define MAXPILA  20
#define MAXGENERO 11
typedef struct{
    char generoID[MAXGENERO];
    int minReproducciones;
} TELEMENTOP;

typedef struct {
    TELEMENTOP vp[MAXPILA];
    int tope;
} TPILA;

void iniciap(TPILA *p);
int vaciap(TPILA pila);
int llenap(TPILA pila);
void ponep(TPILA *p, TELEMENTOP elem);
void sacap(TPILA *p, TELEMENTOP *pelem);
void consultap(TPILA pila, TELEMENTOP *pelem);
void mostrarp(TPILA pila);
