#define MAXCOLA   50
#define MAXCAD 4
typedef struct
{
    int numeroPuerto;
    char codContainer[MAXCAD];
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
