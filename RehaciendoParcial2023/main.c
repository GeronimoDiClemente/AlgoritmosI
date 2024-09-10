#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// a donde apuntan las barras de menor significa si esta ej ea.codigo<e.codigo esta en ea pero no en e y leer del cual el valor es el menor
// hacer una tabla para costo almacen y llamarlo con pos = buscaposicion y laburarlo
typedef struct
{
    char codigo[7];
    int tipoPaquete;
    float volumen;
    float costoAsegurado;
}existenciaInicial;

typedef struct
{
    char codigo[7];
    int tipoPaquete;
    float volumen;
    float costoAsegurado;
}existenciaAnterior;


typedef struct
{
    float desdeVol;
    float hastaVol;
    float costo;
}CostoAlmacen;

void leeExistIniAnterior() {
		existenciaAnterior ea;
		FILE *archExistIniAnterior, *lote;

		archExistIniAnterior = fopen("ExistIniAnterior.dat","wb");
		lote = fopen("ExistIniAnterior.txt","rt");
		if(lote != NULL) {
			while(fscanf(lote, "%s %d %f %f", ea.codigo,&ea.tipoPaquete,&ea.volumen,&ea.costoAsegurado) == 4){
			   fwrite(&ea, sizeof(existenciaAnterior), 1, archExistIniAnterior);
			}
			fclose(lote);
			fclose(archExistIniAnterior);
		} else
			printf("archivo ExistIniAnterior.txt no existe!");
	}


void leeExistenciaInicial() {
		existenciaInicial e;
		FILE *archExistencia, *lote;

		archExistencia = fopen("ExistenciaInicial.dat","wb");
		lote = fopen("ExistenciaInicial.txt","rt");
		if(lote != NULL) {
			while(fscanf(lote, "%s %d %f %f", e.codigo,&e.tipoPaquete,&e.volumen,&e.costoAsegurado) == 4){
			   fwrite(&e, sizeof(existenciaInicial), 1, archExistencia);
			}
			fclose(lote);
			fclose(archExistencia);
		} else
			printf("archivo ExistenciaInicial.txt no existe!");
	}

void leeCostoAlmacen() {
		CostoAlmacen c;
		FILE *archCosto, *lote;

		archCosto = fopen("CostoAlmacen.dat","wb");
		lote = fopen("CostoAlmacen.txt","rt");
		if(lote != NULL) {
			while(fscanf(lote, "%f %f %f", &c.desdeVol,&c.hastaVol,&c.costo) == 3){
			   fwrite(&c, sizeof(CostoAlmacen), 1, archCosto);
			}
			fclose(lote);
			fclose(archCosto);
		} else
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
void ActualizayLista()
{
    FILE *archExisIniAnt, *archExistenciaInicial, *archCostoAlmacen, *archDespacho;
    existenciaInicial e; existenciaAnterior ea; CostoAlmacen c;
    archExisIniAnt = fopen("ExistIniAnterior.dat","rb");
    archExistenciaInicial=fopen("ExistenciaInicial.dat","rb");


    if ((archExisIniAnt!=NULL)&&(archExistenciaInicial!=NULL))
    {
        archDespacho= fopen("Despacho.dat","wb");
        fread(&e,sizeof(existenciaInicial),1,archExistenciaInicial);
        fread(&ea,sizeof(existenciaAnterior),1,archExisIniAnt);

        while(!feof(archExisIniAnt)||!feof(archExistenciaInicial))
         {
                if (strcmp(ea.codigo,e.codigo)==0)
                {

                    fread(&e,sizeof(existenciaInicial),1,archExistenciaInicial);
                    fread(&ea,sizeof(existenciaAnterior),1,archExisIniAnt);
                }
                else
                    if(strcmp(ea.codigo,e.codigo)>0)
                    {

                         fread(&e,sizeof(existenciaInicial),1,archExistenciaInicial);

                    }
                    else // ea.codigo < e.codigo
                     {
                        fwrite(&e,sizeof(existenciaInicial),1,archDespacho);
                        fread(&ea,sizeof(existenciaAnterior),1,archExisIniAnt);
                     }
         }

        fclose(archExisIniAnt);
        fclose(archExistenciaInicial);
        fclose(archDespacho);
    }
}

void muestraDespacho()
{
    existenciaInicial e;
    FILE *archDespacho;
    archDespacho = fopen("Despacho.dat","rb");

    if (archDespacho == NULL)
        printf("No se genero el archivo o no se encuentra\n");
    else
    {
        fread(&e,sizeof(existenciaInicial),1,archDespacho);
        while (!feof(archDespacho))
        {
            printf("\n");
            printf("%s %d %.2f %.2f ", e.codigo,e.tipoPaquete,e.volumen,e.costoAsegurado);


            fread(&e,sizeof(existenciaInicial),1,archDespacho);
        }
        fclose(archDespacho);
    }
}
int main()
{
    leeExistIniAnterior();
    leeExistenciaInicial();
    leeCostoAlmacen();
    ActualizayLista();
     //muestraArch();
    //muestraArch2();
    muestraDespacho();
        return 0;
}
