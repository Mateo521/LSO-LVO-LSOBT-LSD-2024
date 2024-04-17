
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


int LocalizarLVO(lvo *lista, char codigo[], Nodo **anterior, int p) {


    lista->costoEvoE=0.0;
    lista->costoEvoF=0.0;
    float temp =0.0;


    Nodo *actual = lista->inicio;
    int i = 0;
    while (actual != NULL && strcmp(actual->envio.codigo, codigo) < 0) {
            temp++;
        *anterior = actual;
        actual = actual->siguiente;
        i++;
    }
      if (i < lista->contador) {


     temp++;

        }
    if (actual != NULL && strcmp(actual->envio.codigo, codigo) == 0) {

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





void AltaLVO(lvo *lista, Envio nuevoEnvio) {
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->envio = nuevoEnvio;
    nuevoNodo->siguiente = NULL;
    Nodo *anterior = NULL;
    int encontrado = LocalizarLVO(lista, nuevoEnvio.codigo, &anterior, 1);
    if (encontrado) {
        free(nuevoNodo);
        return;
    }

    if (anterior != NULL) {

               lista->costo_punteros_actualizados_a += 0.5;
    nuevoNodo->siguiente = anterior->siguiente;
} else {

     lista->costo_punteros_actualizados_a += 0.5;
    nuevoNodo->siguiente = lista->inicio;
}
    if (anterior == NULL) {
        lista->inicio = nuevoNodo;


    } else {


           lista->costo_punteros_actualizados_a += 0.5;
        anterior->siguiente = nuevoNodo;
    }
    lista->contador++;


        lista->num_altas++;
         if (lista->costo_punteros_actualizados_a > lista->max_costo_a) {
            lista->max_costo_a = lista->costo_punteros_actualizados_a;


        }

       lista->AltaMaxima = lista->max_costo_a/lista->num_altas;


       lista->AltaMedia = lista->costo_punteros_actualizados_a/lista->num_altas;
}


void BajaLVO(lvo *lista, Envio envio) {
    Nodo *anterior = NULL;
    int pos;
    int encontrado = LocalizarLVO(lista, envio.codigo, &anterior, 1);
    if (!encontrado) {
        return;
    }
    Nodo *eliminar;
    if (anterior != NULL) {
        eliminar = anterior->siguiente;
    } else {
        eliminar = lista->inicio;
    }

    // Variable para almacenar el costo de cambio de puntero
    float costoCambioPuntero = 0; // Cambiado a float para permitir incrementos de 0.5

    if (eliminar->siguiente == NULL) {
        // Si el nodo a eliminar es el último nodo
        if (anterior != NULL) {
            anterior->siguiente = NULL;
        } else {
            lista->inicio = NULL;
        }
    } else {
        // Si el nodo a eliminar no es el último nodo
        if (anterior != NULL) {
            anterior->siguiente = eliminar->siguiente;
            // Calcular el costo de cambio de puntero
            costoCambioPuntero += 0.5; // Incrementar el contador en 0.5
        } else {
            lista->inicio = eliminar->siguiente;
        }
    }

    free(eliminar);
    lista->contador--;

    // Incrementar el contador de punteros actualizados
    lista->costo_punteros_actualizados_b += costoCambioPuntero;

    // Actualizar el máximo costo de cambio de puntero
    if (lista->costo_punteros_actualizados_b > lista->max_costo_b) {
        lista->max_costo_b = lista->costo_punteros_actualizados_b;
    }

    // Incrementar el contador de bajas
    lista->num_bajas++;

    // Calcular la media de los costos de cambio de puntero
       lista->BajaMaxima = lista->max_costo_b/lista->num_bajas;


       lista->BajaMedia = lista->costo_punteros_actualizados_b/lista->num_bajas;
}



int evocarLVO(lvo *lista, char codigo[], Envio *envio) {

    Nodo *anterior = NULL;
    int pos;
    int res = LocalizarLVO(lista, codigo, &anterior, 0);
    if (res == 1) {
        if (anterior != NULL) {
    *envio = anterior->siguiente->envio;
} else {
    *envio = lista->inicio->envio;
}
        return 1; // Se encontró el envío
    } else {
        return 0; // No se encontró el envío
    }
}


#define RS_H_INCLUDED
#define MaxEnviosRS 300

#include <stdbool.h>
#include "Envios.h"



