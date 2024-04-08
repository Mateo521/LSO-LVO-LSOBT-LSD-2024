
#include "Envios.h"
#include <String.h>
#include <math.h>
#ifndef UNTITLED_LSO_H
#define UNTITLED_LSO_H
#define MAX_Envios 300
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

    float eExMax, eExMed, eFrMax, eFrMed, aMax, aMed, bMax, bMed, celCont,tempa,tempb, eExCant,eFrCant,aCant,bCant,costo,costoEvoE,costoEvoF,tempe,tempef;
    double costo_punteros_actualizados_a,costo_punteros_actualizados_b, max_costo_a,max_costo_b;
    int num_altas,num_bajas;
} lvo;

void initLVO(lvo *lista) {
    lista->max_costo_a= 0.0;
     lista->max_costo_a= 0.0;
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


int LocalizarLVO(lvo *lista, char codigo[], int *pos, int p) {

      lista->costoEvoE=0.0;
    lista->costoEvoF=0.0;
    Nodo *actual = lista->inicio;
    Nodo *anterior = NULL;
    int i = 0;
    float temp =0.0;
    while (actual != NULL && strcmp(actual->envio.codigo, codigo) < 0) {

        temp++;
        anterior = actual;
        actual = actual->siguiente;
        i++;
    }

    *pos = i;

    if (actual != NULL && strcmp(actual->envio.codigo, codigo) == 0) {

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



int AltaLVO(lvo *lista, Envio envio) {
    int pos,temp=0;
    int i;
    if(lista->contador == MAX_Envios){
        return 2; // Lista llena
    }
    int res = LocalizarLVO(lista, envio.codigo, &pos,1);
    if (res == 0) {
        Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
        if (nuevoNodo == NULL) {
            return -1; // Error de asignaci�n de memoria
        }
        nuevoNodo->envio = envio;

        if (pos == 0 || lista->inicio == NULL) {
            nuevoNodo->siguiente = lista->inicio;
            lista->inicio = nuevoNodo;
        } else {
            Nodo *anterior = lista->inicio;
            for (i = 0; i < pos - 1; i++) {
                anterior = anterior->siguiente;
            }
            nuevoNodo->siguiente = anterior->siguiente;
            anterior->siguiente = nuevoNodo;
            lista->costo_punteros_actualizados_a += 0.5;
            printf("cambio de puntero\n");
        }

        lista->contador++;

         lista->num_altas++;

        if (lista->costo_punteros_actualizados_a > lista->max_costo_a && pos !=0) {
            lista->max_costo_a= lista->costo_punteros_actualizados_a;
        }


        return 0; // Insercion exitosa
    } else {
        return 1; // El envio ya existe en la lista
    }
}

int BajaLVO(lvo *lista, Envio envio) {
    int pos;
    int localizar_resultado = LocalizarLVO(lista, envio.codigo, &pos, 1);

    if (localizar_resultado) {
        Nodo *actual = lista->inicio;
        Nodo *anterior = NULL;
        for (int i = 0; i < pos; i++) {
            anterior = actual;
            actual = actual->siguiente;
        }
        if (anterior == NULL) {
            lista->inicio = actual->siguiente;
        } else {
            anterior->siguiente = actual->siguiente;


        if(pos!=0)
             lista->costo_punteros_actualizados_b += 0.5;

        }



         lista->num_bajas++;

        if (lista->costo_punteros_actualizados_b > lista->max_costo_b && pos !=0) {
            lista->max_costo_b= lista->costo_punteros_actualizados_b;
        }

        free(actual);

        lista->contador--;

        return 0; // Baja exitosa
    } else {
        return 1; // Envío no encontrado en la lista
    }
}

int evocarLVO(lvo *lista, char codigo[], Envio *envio) {
    int pos = 0;
    int res = LocalizarLVO(lista, codigo, &pos, 0);
    if (res == 1) {
        Nodo *actual = lista->inicio;
        for (int i = 0; i < pos; i++) {
            actual = actual->siguiente;
        }
        *envio = actual->envio;
        return 1;
    } else {
        return 0;
    }
}


#define RS_H_INCLUDED
#define MaxEnviosRS 300

#include <stdbool.h>
#include "Envios.h"



