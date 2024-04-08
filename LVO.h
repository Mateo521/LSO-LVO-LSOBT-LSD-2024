
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
} lvo;

void initLVO(lvo *lista) {
    lista->inicio = NULL;
    lista->contador = 0;

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
    Nodo *actual = lista->inicio;
    Nodo *anterior = NULL;
    int i = 0;

    while (actual != NULL && strcmp(actual->envio.codigo, codigo) < 0) {
        anterior = actual;
        actual = actual->siguiente;
        i++;
    }

    *pos = i;

    if (actual != NULL && strcmp(actual->envio.codigo, codigo) == 0) {
        return 1;
    } else {
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
        }

        lista->contador++;

        return 0; // Inserci�n exitosa
    } else {
        return 1; // El env�o ya existe en la lista
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
        }

        free(actual);

        lista->contador--;

        return 0; // Baja exitosa
    } else {
        return 1; // Envío no encontrado en la lista
    }
}

int evocacionLVO (lvo *lista, char codigo[], Envio *envio){
    int pos = 0, i= 0;
    int res = Localizar(lista,codigo,&pos,0);
    if (res == 1){
        Nodo *anterior = lista->inicio;
        for (i = 0; i < pos - 1; i++) {
            anterior = anterior->siguiente;
        }

        *envio = anterior->envio;
    }

}
#define RS_H_INCLUDED
#define MaxEnviosRS 300

#include <stdbool.h>
#include "Envios.h"



