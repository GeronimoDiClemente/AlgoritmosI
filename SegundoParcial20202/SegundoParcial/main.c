#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXNOM 11
#define MAXTIT 31

typedef struct nodito
{
    int ID;
    char titulo[MAXTIT];
    float duracion;
    int cantidad;
    struct nodito *sig;
}NODITO;
typedef NODITO *TSUBLISTA;

typedef struct nodo
{
    char nombre[MAXNOM];
    TSUBLISTA sublista;
    struct nodo *sig;
}NODO;
typedef NODO *TLISTA;




int main()
{
    printf("Hello world!\n");
    return 0;
}
