#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20
#define TIPOS 10 // Definir un máximo de 10 tipos de paquete
// a donde apuntan las barras de menor significa si esta ej ea.codigo<e.codigo esta en ea pero no en e y leer del cual el valor es el menor
// hacer una tabla para costo almacen y llamarlo con pos = buscaposicion y laburarlo
typedef struct
{
    char codigo[7];
    unsigned int tipoPaquete;
    float volumen;
    float costoAsegurado;
} existenciaInicial;

typedef struct
{
    char codigo[7];
    unsigned int tipoPaquete;
    float volumen;
    float costoAsegurado;
} existenciaAnterior;


typedef struct
{
    float desdeVol;
    float hastaVol;
    float costo;
} CostoAlmacen;

void leeExistIniAnterior()
{
    existenciaAnterior ea;
    FILE *archExistIniAnterior, *lote;

    archExistIniAnterior = fopen("ExistIniAnterior.dat","wb");
    lote = fopen("ExistIniAnterior.txt","rt");
    if(lote != NULL)
    {
        while(fscanf(lote, "%s %d %f %f", ea.codigo,&ea.tipoPaquete,&ea.volumen,&ea.costoAsegurado) == 4)
        {
            fwrite(&ea, sizeof(existenciaAnterior), 1, archExistIniAnterior);
        }
        fclose(lote);
        fclose(archExistIniAnterior);
    }
    else
        printf("archivo ExistIniAnterior.txt no existe!");
}


void leeExistenciaInicial()
{
    existenciaInicial e;
    FILE *archExistencia, *lote;

    archExistencia = fopen("ExistenciaInicial.dat","wb");
    lote = fopen("ExistenciaInicial.txt","rt");
    if(lote != NULL)
    {
        while(fscanf(lote, "%s %d %f %f", e.codigo,&e.tipoPaquete,&e.volumen,&e.costoAsegurado) == 4)
        {
            fwrite(&e, sizeof(existenciaInicial), 1, archExistencia);
        }
        fclose(lote);
        fclose(archExistencia);
    }
    else
        printf("archivo ExistenciaInicial.txt no existe!");
}

void leeCostoAlmacen()
{
    CostoAlmacen c;
    FILE *archCosto, *lote;

    archCosto = fopen("CostoAlmacen.dat","wb");
    lote = fopen("CostoAlmacen.txt","rt");
    if(lote != NULL)
    {
        while(fscanf(lote, "%f %f %f", &c.desdeVol,&c.hastaVol,&c.costo) == 3)
        {
            fwrite(&c, sizeof(CostoAlmacen), 1, archCosto);
        }
        fclose(lote);
        fclose(archCosto);
    }
    else
        printf("archivo CostoAlmacen.txt no existe!");
}



void muestraArch()
{
    existenciaInicial e;
    FILE *arch;
    arch = fopen("ExistenciaInicial.dat","rb");

    if (arch== NULL)
        printf("No se genero el archivo o no se encuentra\n");
    else
    {
        fread(&e,sizeof(existenciaInicial),1,arch);
        while (!feof(arch))
        {
            printf("%s %d %.2f %.2f ", e.codigo,e.tipoPaquete,e.volumen,e.costoAsegurado );
            printf("\n");
            fread(&e,sizeof(existenciaInicial),1,arch);
        }
        fclose(arch);
    }
}
void muestraArch2()
{
    CostoAlmacen c;
    FILE *arch;
    arch = fopen("CostoAlmacen.dat","rb");

    if (arch== NULL)
        printf("No se genero el archivo o no se encuentra\n");
    else
    {
        fread(&c,sizeof(CostoAlmacen),1,arch);
        while (!feof(arch))
        {
            printf("\n");
            printf("%.2f %.2f %.2f", c.desdeVol,c.hastaVol,c.costo );


            fread(&c,sizeof(CostoAlmacen),1,arch);
        }
        fclose(arch);
    }
}

void cargarvec(CostoAlmacen vecCos[], int *dimCos)
{
    FILE *archcostos;
    *dimCos=0;
    archcostos=fopen("CostoAlmacen.dat","rb");
    if (archcostos!=NULL)
    {
        fread(&vecCos[0], sizeof(CostoAlmacen),1,archcostos);
        while (!feof(archcostos)&& MAX>*dimCos)
        {
            (*dimCos)++;
            fread(&vecCos[*dimCos],sizeof(CostoAlmacen),1,archcostos);
        }
        fclose(archcostos);
    }
}
int buscaPosicion (float volumen, CostoAlmacen vecCos[],int dimCos)
{
    int i=0;
    while (i<dimCos  && volumen <= vecCos[i].desdeVol)
    {
        i++;
    }
    if (volumen >= vecCos[i].desdeVol)
        return i;
    else
        return -1;

}


void ActualizayLista(CostoAlmacen vecCos[],int dimCos)
{
    FILE *archExisIniAnt, *archExistenciaInicial, *archCostoAlmacen, *archDespacho;
    existenciaInicial e;
    existenciaAnterior ea;
    CostoAlmacen c;
    archExisIniAnt = fopen("ExistIniAnterior.dat","rb");
    archExistenciaInicial=fopen("ExistenciaInicial.dat","rb");
    int pos,contPaq;
    float costoTotalAseg, costoTotalAlm, contResumen,volumenProm,volumenTotal;

    // Arreglo para contar la cantidad de paquetes por tipo
    int conteoPorTipo[TIPOS] = {0};  // Inicializar todo en 0


    if ((archExisIniAnt!=NULL)&&(archExistenciaInicial!=NULL))
    {
        archDespacho= fopen("Despacho.dat","wb");
        fread(&e,sizeof(existenciaInicial),1,archExistenciaInicial);
        fread(&ea,sizeof(existenciaAnterior),1,archExisIniAnt);
        costoTotalAlm=0;
        costoTotalAseg=0;
        contResumen=0;
        volumenProm=0;
        volumenTotal=0;
        contPaq=0;

        while(!feof(archExisIniAnt)||!feof(archExistenciaInicial))
        {

            if (strcmp(e.codigo, "ZZZZZZ") == 0 || strcmp(ea.codigo, "ZZZZZZ") == 0)
            {
                break;  // Salir del bucle si se encuentra este código
            }
            if (strcmp(ea.codigo,e.codigo)==0)
            {

                fread(&e,sizeof(existenciaInicial),1,archExistenciaInicial);
                fread(&ea,sizeof(existenciaAnterior),1,archExisIniAnt);
            }
            else if(strcmp(ea.codigo,e.codigo)>0)
            {

                fread(&e,sizeof(existenciaInicial),1,archExistenciaInicial);

            }
            else // ea.codigo < e.codigo
            {
                fwrite(&ea,sizeof(existenciaAnterior),1,archDespacho);
                fread(&ea,sizeof(existenciaAnterior),1,archExisIniAnt);
            }
            volumenTotal+=e.volumen;
            pos = buscaPosicion(e.volumen,vecCos,dimCos);
            costoTotalAlm+=vecCos[pos].costo;
            costoTotalAseg+=e.costoAsegurado;
            (contPaq++);
            // Contar el tipo de paquete
            if (e.tipoPaquete >= 1 && e.tipoPaquete <= TIPOS)
            {
                conteoPorTipo[e.tipoPaquete - 1]++;  // Restar 1 porque el índice del arreglo comienza en 0
            }

        }

        volumenProm = volumenTotal / contPaq;

        printf("#Para la jornada actual\n");
        printf("\t\t .Costo total asegurado: %.2f\n", costoTotalAseg);
        printf("\t\t .Costo total de almacenamiento: %.2f\n", costoTotalAlm);
        printf("\t\t .volumen promedio por paquete: %.2f\n", volumenProm);

        // Mostrar el resumen de la cantidad de paquetes por tipo
        printf("\n# Resumen de paquetes por tipo:\n");
        for (int i = 0; i < TIPOS; i++)
        {
            if (conteoPorTipo[i] > 0)
            {
                printf("\t .Tipo %d: %d paquetes\n", i + 1, conteoPorTipo[i]);
            }
        }


        fclose(archExisIniAnt);
        fclose(archExistenciaInicial);
        fclose(archDespacho);
    }
}

void muestraDespacho()
{
    existenciaAnterior ea;
    FILE *archDespacho;
    archDespacho = fopen("Despacho.dat","rb");

    if (archDespacho == NULL)
        printf("No se genero el archivo o no se encuentra\n");
    else
    {
        fread(&ea,sizeof(existenciaAnterior),1,archDespacho);
        while (!feof(archDespacho))
        {
            printf("\n");
            printf("%s %d %.2f %.2f ", ea.codigo,ea.tipoPaquete,ea.volumen,ea.costoAsegurado);


            fread(&ea,sizeof(existenciaAnterior),1,archDespacho);
        }
        fclose(archDespacho);
    }
}
int main()
{
    CostoAlmacen vecCos[MAX];
    int dimCos;
    cargarvec(vecCos,&dimCos);
    leeExistIniAnterior();
    leeExistenciaInicial();
    leeCostoAlmacen();
    ActualizayLista(vecCos,dimCos);
    //muestraArch();
    //muestraArch2();
    muestraDespacho();
    return 0;
}




