#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
typedef struct
{
    char numero[8];
    char fecha[10];
    int duracionllamada;
    char codigo[5];
}llamadas;
typedef struct
{
    char codigo[5];
    int duracion;
    int costo;
}costos;

void leeLlamadas() {
		llamadas l;
		FILE *archLlamadas, *lote;

		archLlamadas = fopen("llamadas.dat","wb");
		lote = fopen("llamadas.txt","rt");
		if(lote != NULL) {
			while(fscanf(lote, "%s %s %d %s", l.numero,l.fecha,&l.duracionllamada,l.codigo) == 4){
			   fwrite(&l, sizeof(llamadas), 1, archLlamadas);
			}
			fclose(lote);
			fclose(archLlamadas);
		} else
			printf("archivo llamadas.txt no existe!");
	}

void leeCostos() {
		costos c;
		FILE *archCostos, *lote;

		archCostos = fopen("costos.dat","wb");
		lote = fopen("costos.txt","rt");
		if(lote != NULL) {
			while(fscanf(lote, "%s %d %d ", c.codigo,&c.duracion,&c.costo) == 3){
			   fwrite(&c, sizeof(costos), 1, archCostos);
			}
			fclose(lote);
			fclose(archCostos);
		} else
			printf("archivo costos.txt no existe!");
	}

void cargarCostos (costos vec[], int *dimCos) // como se carga un vecotr
{
    FILE *arch;
    arch = fopen("costos.dat", "rb");
    *dimCos = 0;
    if (arch != NULL)
    {
        fread(&vec[0], sizeof(costos), 1,arch);
        while (!feof(arch) && MAX > *dimCos)
        {
            (*dimCos)++;
            fread(&vec[*dimCos], sizeof(costos), 1,arch);
        }
        fclose(arch);
    }
}
int buscaPosicion(costos vec[],int dimCos,char codActual[6], int duracion) // busca posicion y en el genera listado lo llamas con un pos=buscaPosicion
{
    int i=0;
    while (strcmp(codActual,vec[i].codigo) && i<dimCos)
    {
        i++;
    }
	while (duracion>vec[i].duracion)
		i++;
	return i;
}

void generaListado(costos vec[], int dimCos)
{
    llamadas l;
    FILE *arch;
    int cantLlamdia, acumSegundos,llamMax,pos;
    char numAct[8],fechaAct[11],NumMaxGasto[8];
    float acumGasto,gastoTotal,gastoMax;
    arch = fopen("llamadas.dat","rb");
    if (arch!= NULL)
    {
        gastoMax=0;
        fread(&l,sizeof(llamadas),1,arch);
        while (!feof(arch))
        {
            strcpy(numAct,l.numero);
            gastoTotal=0;
            printf("Nro Celular %s\n",numAct);
            printf("Fecha\t\t Cant.Llamadas del dia \t\t Total de segundos \tLLamada mas larga \t\t Gasto diario\n");
            while(!feof(arch)&&(!strcmp(numAct,l.numero)))
             {
                strcpy(fechaAct,l.fecha);
                acumGasto=0; acumSegundos=0;cantLlamdia=0;llamMax=0;
                while(!feof(arch)&&(!strcmp(numAct,l.numero))&& !strcmp(fechaAct,l.fecha))
                {
                    cantLlamdia++;
                    acumSegundos+=l.duracionllamada;
                    if (l.duracionllamada>llamMax)
                    {
                        llamMax=l.duracionllamada;
                    }
                    pos=buscaPosicion(vec,dimCos,l.codigo,l.duracionllamada);
                    acumGasto+=vec[pos].costo;
                    fread(&l,sizeof(llamadas),1,arch);
                }
                gastoTotal+=acumGasto;
               printf("%s\t\t\t%d\t\t %d\t\t\t %d\t\t\t\t %.2f\n",fechaAct,cantLlamdia,acumSegundos,llamMax,acumGasto);
             }
             if (gastoTotal>gastoMax)
                {
                    gastoMax=gastoTotal;
                    strcpy(NumMaxGasto,l.numero);
                }
        printf("Gasto total: %.2f\n",gastoTotal);
        }
        printf("Nro.celular con mayor gasto: %s",NumMaxGasto);
        fclose(arch);
    }
}

int main()
{
    costos vec[MAX];
    int dimCos;
    cargarCostos (vec,&dimCos);
    leeLlamadas();
    leeCostos();
    generaListado(vec,dimCos);

    return 0;
}
