//
// Created by lautaro on 19/8/2023.
//
#include "Envios.h"
#include <String.h>
#ifndef UNTITLED_LSO_H
#define UNTITLED_LSO_H
#define MAX_Envios 250
#endif //UNTITLED_LSO_H
char *Mayusculas(char string[]);
typedef struct {
    Envio envios [MAX_Envios];
    int contador;
    float eExMax, eExMed, eFrMax, eFrMed, aMax, aMed, bMax, bMed, celCont,tempa,tempb, eExCant,eFrCant,aCant,bCant,costo,costoEvoE,costoEvoF,tempe,tempef;
}lso;

void initLSO(lso *lista) {
    lista->eExMax = 0.0;
    lista->eExMed = 0.0;
    lista->eFrMax = 0.0;
    lista->eFrMed = 0.0;
    lista->aMax = 0.0;
    lista->aMed = 0.0;
    lista->bMax = 0.0;
    lista->bMed = 0.0;
    lista->celCont = 0.0;
    lista->eExCant = 0;
    lista->eFrCant = 0;
    lista->aCant = 0.0;
    lista->bCant = 0.0;
    lista->tempa = 0.0;
    lista->tempb = 0.0;
    lista->tempe= 0.0;
    lista->tempef= 0.0;
}

int Localizar(lso *lista, char codigo[], int *pos, int p) {

    lista->costoEvoE=0.0;
    lista->costoEvoF=0.0;
    float temp =0.0;
    int i = 0;

    while (i < lista->contador && strcmp(lista->envios[i].codigo, codigo) < 0) {
        temp++;
        i++;
    }

    *pos = i;


    if(i<lista->contador){
        temp++;
    }

    if (i < lista->contador && strcmp(lista->envios[i].codigo, codigo) == 0) {


        if(p==0){

            if(lista->eExMax<temp){
                lista->eExMax = temp+1;
            }

            lista->eExCant++;
            lista->costoEvoE+=temp;
            lista->tempe+=lista->costoEvoE;
            lista->eExMed = lista->tempe/(lista->eExCant);



        }


        return 1;
    } else {


        if(i<lista->contador){

            temp++;
        }
        if(p==0){
            if(lista->eFrMax<temp){
                lista->eFrMax = temp+1;
            }

            lista->eFrCant++;
            lista->costoEvoF+=temp;
            lista->tempef+=lista->costoEvoF;
            lista->eFrMed = lista->tempef/(lista->eFrCant);

        }

        return 0;

    }

}


int AltaLSO(lso *lista, Envio envio) {
    lista->costo =0.0;
    int pos,temp=0;
    int i;
    if(lista->contador == MAX_Envios){
        return 2;
    }
    int res = Localizar(lista, envio.codigo, &pos,1);
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
int BajaLSO(lso *lista,Envio envio) {
    lista->costo =0.0;

    int conf;



    int pos, i;

    int localizar_resultado = Localizar(lista, envio.codigo , &pos,1);

    if( (strcmp(lista->envios[pos].direccion , envio.direccion)==0) && (lista->envios[pos].dni_receptor == envio.dni_receptor)
        && (lista->envios[pos].dni_remitente == envio.dni_remitente) && (strcmp(lista->envios[pos].fecha_envio,envio.fecha_envio)==0)
        && (strcmp(lista->envios[pos].fecha_recepcion,envio.fecha_recepcion)==0) && (strcmp(lista->envios[pos].nombre,envio.nombre)==0)
        && (strcmp(lista->envios[pos].nombre_r,envio.nombre_r)==0)){

        if (localizar_resultado) {
            for (i = pos; i < lista->contador-1; i++) {
                lista->costo++; //corrimiento
                lista->envios[i] = lista->envios[i + 1];
            }



            lista->contador--;


            if (lista->costo > lista->bMax) {

                lista->bMax = lista->costo; //maximo

            }

            lista->tempb+=lista->costo; //promedio


            lista->bMed=lista->tempb/(lista->bCant+1);



            lista->bCant++; //cantidad de bajas



            return 0;

        }

    }else {
        return 1;
    }



}

int evocarLSO (lso *lista, char codigo[], Envio *envio){
    int pos;
    int res = Localizar(lista,codigo,&pos,0);
    if (res == 1){
        (*envio)= lista->envios[pos];
        return 1;// se
        // econtro
    }else
        return 0;
}
