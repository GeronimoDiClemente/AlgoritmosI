#define MAXPILA  20
#define MAXCOD  4
#define MAXPREM  6

typedef struct
{
    char codCliente[MAXCOD];
    char codPremio[MAXPREM];
    float acumulados;
}TELEMENTOP;

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
