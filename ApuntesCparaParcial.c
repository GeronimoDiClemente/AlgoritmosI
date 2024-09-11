PASO A PASO A TENER EN CUENTA REALIZANDO EJERCICIOS CUENTA

leeArchivo
void leeInscriptos() {
		inscriptos i;
		FILE *archInscriptos, *lote;

		archInscriptos = fopen("inscriptos.dat","wb");
		lote = fopen("inscriptos.txt","rt");
		if(lote != NULL) {
			while(fscanf(lote, "%s %s %d ", i.inscriptos,i.apellido,&i.inasistencias) == 3){
			   fwrite(&i, sizeof(inscriptos), 1, archInscriptos);
			}
			fclose(lote);
			fclose(archInscriptos);
		} else
			printf("archivo inscriptos.txt no existe!");
	}

CARGAR Y MOSTRAR VEC EN CASO DE QUERER VERLO Y SE INVOCA EN MAIN COMO SE VE ARRIBA

void cargarvec(records vecRec[], int *dimRec)
{
    FILE *archrecords;
    *dimRec=0;
    archrecords=fopen("records.dat","rb");
    if (archrecords!=NULL)
    {
        fread(&vecRec[0], sizeof(records),1,archrecords);
        while (!feof(archrecords)&& MAX>*dimRec)
        {
            (*dimRec)++;
            fread(&vecRec[*dimRec],sizeof(records),1,archrecords);
        }
        fclose(archrecords);
    }
}
int buscaPosicion (char codact[],records vecRec[],int dimRec)
{
    int i=0;
    while(strcmp(codact,vecRec[i].codigo))
    {
        i++;
    }
    return i;
}
void muestraVecRec(records vecRec[],int dimRec)
{

    int i;
    for (i=0;i<dimRec;i++)
    {
        printf("%s  %s  %d\n", vecRec[i].codigo, vecRec[i].nombredeporte, vecRec[i].tiempo);
    }
}

PUEDE QUE EL VECTOR SEA DE FLOAT O NUMEROS Y EL BUSCA POSICION DEBE SER DE ESTA MANERA

int buscaPosicion (float volumen, CostoAlmacen vecCos[],int dimCos)
{
    for (int i = 0; i < dimCos; i++) {
        if (volumen >= vecCos[i].desdeVol && volumen <= vecCos[i].hastaVol) {
            return i;
        }
    }
    return -1   ;
}


en caso de que haya vectores algo por el estilo:

void ActualizayLista(CostoAlmacen vecRec[],int dimRec)

int main()
{
    cargarcompeticion();
    cargarrecords();
    records vecRec[MAX];
    int dimRec;
    cargarvec(vecRec,&dimRec);
    generalistado(vecRec,dimRec);

    return 0;
}

Enfrentamiento de archivo estructura
// a donde apuntan las barras de menor significa si esta ej ea.codigo<e.codigo esta en ea pero no en e y leer del cual el valor es el menor
//es decir ea.codigo<e.codigo, el fread(&ea) pero ea.codigo>e.codigo el fread(&e)
Void actualizaArchivo()
{
	File *arch1 *arch2 *archActualizado;
	struct1 S; struct2 st; 
	Inicializamos las distintas variables necesarias;
	abrimos los 3 archivos
	arch1 =fopen("arch1.dat","rb");	
	arch2 =fopen("arch2.dat","rb");	
	archActualizado =fopen("archActualizado.dat","wb");
	if ((arch1 != NULL) && (arch2 != NULL))
	{
		En caso que haya una variable muy general se la incializa aqui.
		printf con los textos que necesite el archivo
		fread(&s, sizeof(struct1), 1, arch1);
        fread(&st, sizeof(struct2), 1, arch2);
		while(!feof(arch1) || !feof(arch2))
		{
			incializamos variables a utilizar en el enfrentamiento	
			if (!strcmp(s.variable,st.variable)) // significa que son iguales y resolver
			{
				una vez resuelto en la que son iguales por lo general se realiza el mayor cambio y se escribe y leen los dos arch
				fwrite(&s,sizeof(struct1),1,archActualizado);
				fread(&s, sizeof(struct1), 1, arch1);
				fread(&st, sizeof(struct2), 1, arch2);
			}
			else
				if(strcmp(s.variable,st.variable)>0)
				{
					se lee el primer archivo y en caso que sea necesario se escribe
					fwrite(&s,sizeof(struct1),1,archActualizado);
					fread(&s, sizeof(struct1), 1, arch1);
				}
				else // s.variable<st.variable
				{
					fread(&st, sizeof(struct2), 1, arch2);
				}
		}
		fclose(arch1);
		fclose(arch2);
		fclose(archActualizado);
	}
	
}

Mostrar el archivo actualizado
void muestraArch()
{
    struct s;
    FILE *arch;
    arch = fopen("actualizado.dat","rb");

    if (arch== NULL)
        printf("No se genero el archivo o no se encuentra\n");
    else
    {
        fread(&s,sizeof(struct1),1,arch);
        while (!feof(arch))
        {
            printf("%s %d %d %d %d", s.variable1,s.variable2,s.variable3,s.variable4,s.variable5 );
            printf("\n");
            fread(&s,sizeof(struct1),1,arch);
        }
        fclose(arch);
    }
}



COMO HACER UN ARREGLO PARA UN LISTADO DE TIPOS
#define TIPOS 10 // Definir un máximo de 10 tipos de paquete

donde declaramos las distintas variables en el actualizaArchivo
 // Arreglo para contar la cantidad de paquetes por tipo
    int conteoPorTipo[TIPOS] = {0};  // Inicializar todo en 0
	
Luego dentro del while, para evitar la centinela
 if (strcmp(e.codigo, "ZZZZZZ") == 0 || strcmp(ea.codigo, "ZZZZZZ") == 0) {
                break;  // Salir del bucle si se encuentra este código
            }
dentro del mismo while pero mas hacia el final
if (e.tipoPaquete >= 1 && e.tipoPaquete <= TIPOS) {
                conteoPorTipo[e.tipoPaquete - 1]++;  // Restar 1 porque el índice del arreglo comienza en 0
            }
			
por ultimo dentro del if !=NULL y antes de cerrar archivos
// Mostrar el resumen de la cantidad de paquetes por tipo
        printf("\n# Resumen de paquetes por tipo:\n");
        for (int i = 0; i < TIPOS; i++) {
            if (conteoPorTipo[i] > 0) {
                printf("\t .Tipo %d: %d paquetes\n", i + 1, conteoPorTipo[i]);
            }
        }
