

#include "Envios.h"
#include <String.h>
#include <math.h>
#ifndef UNTITLED_LSO_H
#define UNTITLED_LSO_H
#define MAX_Envios 250
#endif //UNTITLED_LSO_H

//  float eExMax=0.0, eExMed=0.0, eFrMax=0.0, eFrMed=0.0, aMax=0.0, aMed=0.0, bMax=0.0, bMed=0.0, celCont=0.0;
//   int eExCant=0,eFrCant=0,aCant=0,bCant=0;

char *Mayusculas(char string[]);
typedef struct {
    Envio envios [MAX_Envios];
    int contador;
   int vector_aux[MAX_Envios];
    float eExMax, eExMed, eFrMax, eFrMed, aMax, aMed, bMax, bMed, celCont,tempa,tempb, eExCant,eFrCant,aCant,bCant,costo,costoEvoE,costoEvoF,tempe,tempef;



    // Nuevos campos para seguimiento de LocalizarLSOBT
    int exitos;
    int fracasos;
    int max_exitos;
    int max_fracasos;
    int total_exitos;
    int total_fracasos;
    int total_celdas_consultadas_exitos;
    int total_celdas_consultadas_fracasos;
    float media_exitos;
    float media_fracasos;

}lsobt;


void initLSOBT(lsobt *lista) {
     lista->exitos = 0;
    lista->fracasos  = 0;
    lista->max_exitos = 0;
    lista->max_fracasos = 0;
    lista->total_exitos = 0;
    lista->total_fracasos = 0;
    lista-> total_celdas_consultadas_fracasos = 0;
    lista->total_celdas_consultadas_exitos = 0;
    lista->media_fracasos = 0.0;
    lista->media_exitos = 0.0;
    // Nuevas variables para el seguimiento de éxitos y fracasos

    lista->eExMax = 0.0;
    lista->eExMed = 0.0;
    lista->eFrMax = 0.0;
    lista->eFrMed = 0.0;
    lista->aMax = 0.0;
    lista->aMed = 0.0;
    lista->bMax = 0.0;
    lista->bMed = 0.0;
    lista->celCont = 0.0;
    lista->eExCant = 0.0;
    lista->eFrCant = 0.0;
    lista->aCant = 0.0;
    lista->bCant = 0.0;
    lista->tempa = 0.0;
    lista->tempb = 0.0;
    lista->tempe= 0.0;
    lista->tempef= 0.0;
}



int LocalizarLSOBT(lsobt *lista, char codigo[], int *pos, int p) {
    int celdas_consultadas = 0;
    int li = 0; // li inclusivo
    int ls = lista->contador; // ls exclusivo
    int m;

    while (li < ls) {
        m = ceil((li + ls) / 2); //Segmento mas grande a izquierda
        celdas_consultadas++;

        if (strcmp(codigo, lista->envios[m].codigo) == 0) {


            *pos = m;
            if (p == 0) {

                lista->exitos++;
                lista->total_exitos++;
                if (celdas_consultadas > lista->max_exitos) {
                    lista->max_exitos = celdas_consultadas ;
                }

                lista->total_celdas_consultadas_exitos += celdas_consultadas; // Actualizar el total de celdas consultadas para éxitos
                lista->media_exitos = (float) lista->total_celdas_consultadas_exitos / lista->total_exitos; // Calcular la media para éxitos
            }
            return 1; // Elemento encontrado
        } else if (strcmp(codigo, lista->envios[m].codigo) < 0) {
            ls = m;
        } else {
            li = m + 1;
        }
    }

    *pos = li;

    if (p == 0) {
        lista->fracasos++;
        lista->total_fracasos++;
        if (celdas_consultadas > lista->max_fracasos) {
            lista->max_fracasos = celdas_consultadas ;
        }
        lista->total_celdas_consultadas_fracasos += celdas_consultadas; // Actualizar el total de celdas consultadas para fracasos
        lista->media_fracasos = (float) lista->total_celdas_consultadas_fracasos / lista->total_fracasos; // Calcular la media para fracasos
    }

    return 0; // Elemento no encontrado
}



int AltaLSOBT(lsobt *lista, Envio envio) {
    lista->costo =0.0;
    int pos,temp=0;
    int i;
    if(lista->contador == MAX_Envios){
        return 2;
    }
    int res = LocalizarLSOBT(lista, envio.codigo, &pos,1);
    if (res == 0) {

        for (i = lista->contador-1; i >= pos; i--) {
            lista->costo++; //corrimiento

            lista->envios[i + 1] = lista->envios[i];
        }

        lista->envios[pos] = envio;
        lista->contador++;


        if (lista->costo > lista->aMax) {

            lista->aMax = lista->costo; //maximo



        }


        lista->tempa+=lista->costo; //promedio

        lista->aMed=lista->tempa/(lista->aCant+1);

        lista->aCant++; //cantidad de altas



        return 0;
    } else {


        return 1;
    }

}






int BajaLSOBT(lsobt *lista, Envio envio) {
    lista->costo =0.0;
    int pos, i;
    int encontrado = LocalizarLSOBT(lista, envio.codigo, &pos,1);

    if( (strcmp(lista->envios[pos].direccion , envio.direccion)==0) && (lista->envios[pos].dni_receptor == envio.dni_receptor)
        && (lista->envios[pos].dni_remitente == envio.dni_remitente) && (strcmp(lista->envios[pos].fecha_envio,envio.fecha_envio)==0)
        && (strcmp(lista->envios[pos].fecha_recepcion,envio.fecha_recepcion)==0) && (strcmp(lista->envios[pos].nombre,envio.nombre)==0)
        && (strcmp(lista->envios[pos].nombre_r,envio.nombre_r)==0)){

        if (encontrado) {
            for (i = pos; i < lista->contador - 1; i++) {
                lista->costo++; //corrimiento
                lista->envios[i] = lista->envios[i + 1];
            }

            pos--;
            lista->contador--;



            if (lista->costo > lista->bMax) {

                lista->bMax = lista->costo; //maximo

            }

            lista->tempb+=lista->costo; //promedio


            lista->bMed=lista->tempb/(lista->bCant+1);


            lista->bCant++; //cantidad de bajas
            return 0;
        } else {
            return 1;
        }
    }
    return 0;
}





int evocarLSOBT(lsobt *lista, char codigo[], Envio *envio) {
    int pos;
    int encontrado = LocalizarLSOBT(lista, codigo, &pos,0);

    if (encontrado) {

        *envio = lista->envios[pos];
        return 1;
    } else {
        return 0;
    }
}

