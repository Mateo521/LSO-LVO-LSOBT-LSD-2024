#include "Envios.h"
#include <String.h>
#ifndef UNTITLED_LSO_H
#define UNTITLED_LSO_H

#endif //UNTITLED_LSO_H
char *Mayusculas(char string[]);
typedef struct {
    Envio envios [MAX_Envios];
    int contador;
    float eExMax, eExMed, eFrMax, eFrMed, aMax, aMed, bMax, bMed, celCont,tempa,tempb, eExCant,eFrCant,aCant,bCant,costo,costoEvoE,costoEvoF,tempe,tempef;
}lsd;

void initLSD(lsd *lista) {
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


int localizarlsd(lsd *lista, char codigo[],int *pos, int p){




    float temp = 0.0;
    int i = 0;
    while (i < lista->contador && strcmp(lista->envios[i].codigo,codigo)!=0){
        temp++;
        i++;

    }
    *pos = i;

    if(i<lista->contador){
        temp++;
    }
    if(strcmp(lista->envios[i].codigo,codigo)==0){
        if(p==0) {

            if (lista->eExMax < temp) {
                lista->eExMax = temp ;

            }
            lista->eExCant++;
            lista->costoEvoE += temp;
            lista->tempe+=lista->costoEvoE;
            lista->eExMed = lista->costoEvoE / (lista->eExCant);
        }
        return 0;

    }else{
        if(p==0){

            if(lista->eFrMax<temp){
                lista->eFrMax = temp;

            }


            lista->eFrCant++;
            lista->costoEvoF+=temp;
            lista->tempef+=lista->costoEvoF;
            lista->eFrMed = lista->costoEvoF/(lista->eFrCant);

        }
        return 1;
    }

}


int AltaLSD(lsd *lista, Envio envio){

    int pos;

    int res = localizarlsd(lista, envio.codigo,&pos,1);

    if(res==1 && lista->contador != MAX_Envios){

            lista->envios[pos] = envio;

            lista->contador++;


    }else{
        //no se puede insertar
        return 1;
    }


return 0;
}


int Bajalsd(lsd *lista, Envio envio){

    int pos;

    int res = localizarlsd(lista,envio.codigo,&pos,1);

    if(res==0){
        if((strcmp(lista->envios[pos].direccion , envio.direccion)==0) && (lista->envios[pos].dni_receptor == envio.dni_receptor)
           && (lista->envios[pos].dni_remitente == envio.dni_remitente) && (strcmp(lista->envios[pos].fecha_envio,envio.fecha_envio)==0)
           && (strcmp(lista->envios[pos].fecha_recepcion,envio.fecha_recepcion)==0) && (strcmp(lista->envios[pos].nombre,envio.nombre)==0)
           && (strcmp(lista->envios[pos].nombre_r,envio.nombre_r)==0)){

            if((pos+1)== lista->contador){
                //caso en el que el elemento a elimnar es el ultimo de la lista
                lista->costo=0;
                lista->contador --;

            }else{
                //caso en el que el elemento no es el ultimo
                lista->costo = 1;
                lista->envios[pos] = lista->envios[lista->contador-1];
                lista->contador--;
            }

            lista->bCant++;

            lista->tempb+=lista->costo;

            lista->bMed=lista->tempb/(lista->bCant);

            if (lista->costo > lista->bMax) {

                lista->bMax = lista->costo; //maximo

            }

        }

    }

    return 0;

}

int evocarLSD (lsd *lista, char codigo[], Envio *envio){
    int pos;
    int res = localizarlsd(lista,codigo,&pos,0);
    if (res == 1){
        (*envio)= lista->envios[pos];
        return 1;// se
        // econtro
    }else
        return 0;
}
