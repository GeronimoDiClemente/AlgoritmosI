#define MAXCLIENTE 4
#define MAXPREMIO 6

typedef struct{
    char clienteID[MAXCLIENTE];
    char premioID[MAXPREMIO];
    float pAcum;
} TELEMENTOP;

typedef struct nodop {
    TELEMENTOP dato ;
    struct nodop *sig;
} NODOP;
typedef NODOP *TPILA;

void iniciap(TPILA *p);
int vaciap(TPILA pila);
int llenap(TPILA pila);
void ponep(TPILA *p, TELEMENTOP elem);
void sacap(TPILA *p, TELEMENTOP *pelem);
void consultap(TPILA pila, TELEMENTOP *pelem);
