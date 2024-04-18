
#include "Envios.h"
#include <String.h>
#include <math.h>
#ifndef UNTITLED_LSO_H
#define UNTITLED_LSO_H
#define MAX_Envios 250
#endif //UNTITLED_LSO_H

//  float eExMax=0.0, eExMed=0.0, eFrMax=0.0, eFrMed=0.0, aMax=0.0, aMed=0.0, bMax=0.0, bMed=0.0, celCont=0.0;
//   int eExCant=0,eFrCant=0,aCant=0,bCant=0;
typedef struct Nodo {
    Envio envio;
    struct Nodo* siguiente;
} Nodo;

char *Mayusculas(char string[]);

typedef struct {
    Nodo* inicio;
    Nodo* anterior;
    Nodo* actual;
    int contador;

    float eExMax, eExMed, eFrMax, eFrMed, aMax, aMed, bMax, bMed, celCont,tempa,tempb, eExCant,eFrCant,aCant,bCant,costo,costoEvoE,costoEvoF,tempe,tempef,AltaMaxima,AltaMedia,BajaMaxima,BajaMedia;
    double costo_punteros_actualizados_a,costo_punteros_actualizados_b, max_costo_a,max_costo_b;
    int num_altas,num_bajas;
} lvo;

void initLVO(lvo *lista) {
    lista->max_costo_a= 0.0;


lista->AltaMaxima=0.0;
lista->AltaMedia=0.0;
lista->BajaMaxima=0.0;
lista->BajaMedia=0.0;


    lista->inicio = NULL;
    lista->contador = 0;
    lista->num_altas = 0 ;
    lista->num_bajas = 0 ;
    lista->costo_punteros_actualizados_a = 0.0;
     lista->costo_punteros_actualizados_b = 0.0;

    lista->eExMax = 0.0;
    lista->eExMed = 0.0;
    lista->eFrMax = 0.0;
    lista->eFrMed = 0.0;
    lista->aMax = 0.0;
    lista->aMed = 0.0;
    lista->bMax = 0.0;
    lista->bMed = 0.0;
    lista->celCont = 0.0;
    lista->tempa = 0.0;
    lista->tempb = 0.0;
    lista->eExCant = 0;
    lista->eFrCant = 0;
    lista->aCant = 0.0;
    lista->bCant = 0.0;
    lista->costo = 0.0;
    lista->costoEvoE = 0.0;
    lista->costoEvoF = 0.0;
    lista->tempe = 0.0;
    lista->tempef = 0.0;
}


int LocalizarLVO(lvo *lista, char codigo[], int p) {


    lista->costoEvoE=0.0;
    lista->costoEvoF=0.0;
    float temp =0.0;


    lista->actual=lista->inicio;
    lista->anterior=lista->actual;


    int i = 0;
    while (lista->actual != NULL && strcmp(lista->actual->envio.codigo, codigo) < 0) {


        temp++;
        lista->anterior = lista->actual;
        lista->actual = lista->actual->siguiente;
        i++;
    }
      if (lista->actual != NULL) {


     temp++;

        }
    if (lista->actual != NULL && strcmp(lista->actual->envio.codigo, codigo) == 0) {

        if(p==0){

            if(lista->eExMax<temp){
                lista->eExMax = temp;
            }
            lista->eExCant++;
            lista->costoEvoE+=temp;
            lista->tempe+=lista->costoEvoE;


            lista->eExMed= lista->tempe/ lista->eExCant;
        }

        return 1;
    } else {


        if(p==0){
            if(lista->eFrMax<temp){
                lista->eFrMax = temp;
            }

            lista->eFrCant++;
            lista->costoEvoF+=temp;
            lista->tempef+=lista->costoEvoF;

            lista->eFrMed= lista->tempef/ lista->eFrCant;

        }

        return 0;

    }
    return 0;
}





int AltaLVO(lvo *lista, Envio envio) {
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
   float temp = 0;

   if(nuevoNodo ==NULL){
       return 0;
   }else{

       nuevoNodo->siguiente = NULL;
       nuevoNodo->envio = envio;

       if(LocalizarLVO(lista,envio.codigo,1)){
           free(nuevoNodo);
           return 0;


       }else{
           if(lista->inicio==lista->actual){

                   nuevoNodo->siguiente=lista->inicio;
                   lista->inicio=nuevoNodo;
                   lista->actual=lista->inicio;
                   temp+=1;

           }else{

                   lista->anterior->siguiente=nuevoNodo;
                   nuevoNodo->siguiente=lista->actual;
                   temp+=1;



           }


           //CALCULO DE COSTOS
           lista->costo = temp;
           if (lista->costo > lista->aMax) {

               lista->aMax = lista->costo; //maximo



           }

           lista->aCant++;
           lista->tempa+=lista->costo; //promedio
           lista->contador++;

           lista->aMed=lista->tempa/(lista->aCant);


           return  1;
       }

   }



}


int BajaLVO(lvo *lista, Envio envio) {
    float temp = 0;

    if (LocalizarLVO(lista, envio.codigo, 1)==0) {
        return 0;
    } else {
        if ((strcmp(lista->actual->envio.direccion, envio.direccion) == 0) &&
            (lista->actual->envio.dni_receptor == envio.dni_receptor)
            && (lista->actual->envio.dni_remitente == envio.dni_remitente) &&
            (strcmp(lista->actual->envio.fecha_envio, envio.fecha_envio) == 0)
            && (strcmp(lista->actual->envio.fecha_recepcion, envio.fecha_recepcion) == 0) &&
            (strcmp(lista->actual->envio.nombre, envio.nombre) == 0)
            && (strcmp(lista->actual->envio.nombre_r, envio.nombre_r) == 0)) {

            if (lista->actual == lista->inicio) {
                lista->inicio = lista->actual->siguiente;
                lista->anterior = lista->inicio;
            } else {
                lista->anterior->siguiente = lista->actual->siguiente;
            }

            free(lista->actual);
            lista->actual = lista->inicio;

            temp += 0.5;


            lista->contador--;

            lista->costo = temp;

            if (lista->costo > lista->bMax) {

                lista->bMax = lista->costo; //maximo

            }

            lista->tempb+=lista->costo; //promedio

            lista->bCant++;

            lista->bMed=lista->tempb/(lista->bCant);





            return 1;
            }
        else{
            return 0;
        }

    }

}

int evocarLVO(lvo *lista,char codigo[], Envio *envio) {

    if(LocalizarLVO(lista,codigo,0)){
        *envio = lista->actual->envio;
        return  1;
    }
    else{
        return  0;
    }

}


#define RS_H_INCLUDED
#define MaxEnviosRS 300

#include <stdbool.h>
#include "Envios.h"



