#define MAXCOLA   50
#define MAX   5

typedef struct
{
    char matricula[MAX];
    char codMateria[MAX];
}TELEMENTOC;

typedef struct {
   TELEMENTOC items[MAXCOLA];
   int pri, ult;
} TCOLA;

void iniciac(TCOLA *c);
void ponec (TCOLA *c, TELEMENTOC  elem);
void sacac(TCOLA *c, TELEMENTOC  *e);
void consultac(TCOLA cola, TELEMENTOC *e);
int vaciac(TCOLA cola);
int llenac(TCOLA cola);
