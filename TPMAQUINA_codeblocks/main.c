
#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Envios.h"
#include "LSO.h"
#include "LSD.h"
#include "LVO.h"
#include "LSOBT.h"

#define MAX_Envios 250

/*

 En resumen, las listas vinculadas ordenadas y las listas desordenadas son ideales para manipular grandes volúmenes
 de datos debido a su eficiencia en la inserción y eliminación. Sin embargo, su rendimiento puede no ser óptimo para
 operaciones que requieren un acceso aleatorio rápido, como en el caso de evocaciones exitosas o de fracaso.

 Por otro lado, es importante destacar que, en el contexto de evocaciones donde se requiere un acceso rápido a los
 datos ordenados, la lista secuencial ordenada con búsqueda por trisección emerge como una opción altamente eficiente.
 Esta técnica aprovecha la estructura ordenada de la lista para realizar búsquedas rápidas, dividiendo iterativamente la
 lista en tres partes y descartando las secciones irrelevantes en función de la clave de búsqueda.


Además, es crucial tener en cuenta que la Lista Secuencial Ordenada (LSO) puede resultar menos conveniente en comparación
con las otras estructuras debido a los costos asociados con las operaciones de inserción y eliminación.
 */




int LecturaOperaciones();
char* Mayusculas();
void mostrarestructura();
void mostrarSubmenu()
{

    printf("--Submenu--\n");
    printf("1. Mostrar Lista Secuencial Ordenada (LSO)\n");
    printf("2. Mostrar Lista Secuencial Desordenada (LSD):\n");
    printf("3. Mostrar Lista Secuencial Ordenada con Busqueda por Triseccion (LSOBT)\n");
    printf("4. Mostrar Lista Vinculada Ordenada (LVO)\n");
    printf("5. Volver al Menu Principal\n");
}
char *Mayusculas(char string[])
{
    int i;
    for(i=0; string[i]!='\0'; i++)
    {
        string[i]= toupper(string[i]);
    }
    return  string;
}
void mostrarestructuraLSO(lso *lista)
{
    int i;

    for(i = 0 ; i < lista->contador; i++)
    {
        mostrarenvio(lista->envios[i]);
        getchar();
    }
    printf("Total de %d envios\n", lista->contador);

}
void mostrarestructuraLSD(lsd *lista)
{

    int i;

    for(i = 0 ; i < lista->contador; i++)
    {
        mostrarenvio(lista->envios[i]);
        getchar();
    }
    printf("Total de %d envios\n", lista->contador);

}


void mostrarestructuraLSOBT(lsobt *lista){
    int i;

    for(i = 0 ; i < lista->contador; i++)
    {
        mostrarenvio(lista->envios[i]);
        getchar();
    }
    printf("Total de %d envios\n", lista->contador);

}


void mostrarestructuraLVO(lvo *lista)
{
    Nodo *actual = lista->inicio;

    while (actual != NULL)
    {
        mostrarenvio(actual->envio);
        getchar();
        actual = actual->siguiente;
    }

    printf("Total de %d envios\n", lista->contador);
}






int main()
{


    int opcion, submenu_opcion;

    lso lso;
    lsd lsd;
    lvo lvo;
    lsobt lsobt;
    lso.contador=0;

    lsobt.contador=0;
    initLSO(&lso);
    initLSD(&lsd);
    initLSOBT(&lsobt);
    initLVO(&lvo);



    do
    {
        // Menú principal

        printf("1. Comparacion de estructuras\n");
        printf("2. Mostrar Estructura\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
            case 1:
                system("cls");
               LecturaOperaciones(&lso,&lsd, &lsobt,&lvo);

                printf("\n         AltaMax | AltaMed | BajaMax | BajaMed | Max.Ev.Ex | Med.Ev.Ex | Max.Ev.Fr | Med.Ev.Fr|\n");
                printf("-----------------------------------------------------------------------------------------------\n");
                printf("LSO   :: %.2f   |   %.2f |  %.2f  |  %.2f  |   %.2f   |  %.2f    |  %.2f    |  %.2f   | \n",lso.aMax, lso.aMed, lso.bMax, lso.bMed, lso.eExMax, lso.eExMed, lso.eFrMax, lso.eFrMed);
                printf("-----------------------------------------------------------------------------------------------\n");
                printf("LSOBT  :: %.2f |   %.2f |  %.2f  |  %.2f  |   %d   |  %.2f    |  %d    |  %.2f   | \n",lsobt.aMax, lsobt.aMed, lsobt.bMax, lsobt.bMed, lsobt.max_exitos, lsobt.media_exitos, lsobt.max_fracasos, lsobt.media_fracasos);
                printf("-----------------------------------------------------------------------------------------------\n");
                printf("LSD  :: %.2f   |   %.2f |  %.2f  |  %.2f  |   %.2f   |  %.2f    |  %.2f    |  %.2f   | \n",lsd.aMax, lsd.aMed, lsd.bMax, lsd.bMed, lsd.eExMax, lsd.eExMed, lsd.eFrMax, lsd.eFrMed);
                printf("-----------------------------------------------------------------------------------------------\n");
                printf("LVO   :: %.2f   |   %.2f |  %.2f  |  %.2f  |   %.2f   |  %.2f    |  %.2f    |  %.2f   | \n",lvo.aMax, lvo.aMed, lvo.bMax, lvo.bMed, lvo.eExMax, lvo.eExMed, lvo.eFrMax, lvo.eFrMed);
                printf("-----------------------------------------------------------------------------------------------\n");

                break;
            case 2:


                // system("cls");
                do
                {
                    mostrarSubmenu();
                    printf("Seleccione una opcion: ");
                    scanf("%d", &submenu_opcion);
                    switch (submenu_opcion)
                    {
                        case 1:
                            system("cls");

                            printf("Lista Secuencial Ordenada:\n");
                            mostrarestructuraLSO(&lso);
                            break;
                        case 2:
                            system("cls");

                            printf("Lista Secuencial Desordenada c(LSD):\n");
                            mostrarestructuraLSD(&lsd);

                            break;
                        case 3:
                            system("cls");
                            printf("Lista Secuencial con Busqueda de Triseccion c(LSOBT):\n");

                            mostrarestructuraLSOBT(&lsobt);

                            break;
                        case 4:
                            system("cls");
                            printf("Lista Vinculada Ordenada c(LVO):\n");
                            mostrarestructuraLVO(&lvo);
                            break;
                        case 5:
                            system("cls");
                            // Volver
                            break;
                        default:
                            system("cls");
                            printf("Opcion no valida. Intente de nuevo.\n");
                    }
                }
                while (submenu_opcion != 5);

                break;
            case 3:
                system("cls");
                printf("Saliendo de la aplicacion.\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    }
    while (opcion != 3);


    return 0;
}
int LecturaOperaciones(lso *lso,lsd *lsd,lsobt *lsobt, lvo *lvo)
{

    // Declaraciones e inicializaciones

    Envio aux,aux2;
    FILE* fp;
    char cwd[1024];



    // Obtener el directorio actual
    if (_getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("Error al obtener el directorio actual");
        return 1;
    }




    // Concatenar la ruta del archivo al directorio actual
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s\\%s", cwd, "/Operaciones-Envios.txt");

    // Intentar abrir el archivo en modo lectura
    if ((fp = fopen(filepath, "r")) == NULL) {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }


    else
    {

        int codigoOperador=0,i;
        while (!(feof(fp)))
        {


            fscanf(fp, "%d", &codigoOperador);


            fscanf(fp, " %[^\n]", aux.codigo);
            for(i=0;i<=8;i++){
                aux.codigo[i]=toupper(aux.codigo[i]);
            }
            if (codigoOperador == 1 || codigoOperador == 2)
            {

                // Leer y procesar los datos para Alta o Baja
                fscanf(fp, "%d", &aux.dni_receptor);

                fscanf(fp, " %[^\n]", aux.nombre);
                for(i=0;i<=strlen(aux.nombre);i++){
                    aux.nombre[i]=toupper(aux.nombre[i]);
                }
                fscanf(fp, " %[^\n]", aux.direccion);
                for(i=0;i<=strlen(aux.direccion);i++){
                    aux.direccion[i]=toupper(aux.direccion[i]);
                }
                fscanf(fp, "%d", &aux.dni_remitente);
                fscanf(fp, " %[^\n]", aux.nombre_r);
                for(i=0;i<=strlen(aux.nombre_r);i++){
                    aux.nombre_r[i]=toupper(aux.nombre_r[i]);
                }
                fscanf(fp, " %[^\n]", aux.fecha_envio);
                fscanf(fp, " %[^\n]", aux.fecha_recepcion);

                // Llama a la función correspondiente para alta o baja en las estructuras
                if(codigoOperador == 1)
                {
                    //  mostrarenvio(aux);
                    AltaLSO(lso, aux);
                    AltaLSD(lsd,aux);


                    AltaLSOBT(lsobt,aux);

                    AltaLVO(lvo,aux);


                }
                if(codigoOperador == 2)
                {


                    Bajalsd(lsd,aux);
                    BajaLSO(lso,aux);


                    BajaLSOBT(lsobt,aux);
                    BajaLVO(lvo,aux);

                }

            }
            else if (codigoOperador == 3)
            {




                evocarLSD(lsd,aux.codigo,&aux2);
                evocarLSO(lso,aux.codigo,&aux2);
                evocarLSOBT(lsobt,aux.codigo,&aux2);
                evocarLVO(lvo,aux.codigo,&aux2);
            }
            else
            {
                // Maneja el caso de código de operación no reconocido
                printf("Error: Codigo de operación no reconocido.\n");
                //break;
            }

        }

        fclose(fp);


        return 1;
    }

}
