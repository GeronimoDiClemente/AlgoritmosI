#define MAXCOLA 50
#define MAXSTR 4
typedef struct{
    char formacion[MAXSTR];
    int tipo;
} TELEMENTOC;

typedef struct{
    TELEMENTOC items[MAXCOLA];
    int pri, ult;
} TCOLA;


void iniciac(TCOLA* c);
int vaciac(TCOLA cola);
int llenac(TCOLA cola);
void ponec(TCOLA* c, TELEMENTOC elem);
void sacac(TCOLA *c, TELEMENTOC *e);
void consultac(TCOLA cola, TELEMENTOC *e);
