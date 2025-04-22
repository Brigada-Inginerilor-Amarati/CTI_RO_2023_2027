#include "back.h"


void back(BackBehaviour_t behStruct){
    int st[MAX_STACK]={0};
    int k=1;    //nivelul curent din stiva
    st[k]=0;
    while (k>0){
        if (behStruct.succesor(st, k, behStruct.payload[0])){   //daca pe nivelul k din stiva avem un posibil succesor
            if(behStruct.valid(st, k)){      //verifica daca proaspata valoare pusa pe stiva este valida dpdv al problemei
                if (behStruct.solutie(st, k, behStruct.payload)){   //daca avem o intraga solutie dpdv al problemei
                    behStruct.tipar(st, k);
                }
                else{
                    k++;
                    st[k]=0;
                }
            }
            else{
                ;   //se ignrora elementul care nu este valid --> urmatorul apel la succesor va actualiza elemenul
            }   
        }
        else{
            k--;    //BACKtracking ; se coboara la nivelul anterior ... se se va continua "automat" cu urmatoeul succesor
        }
    }
}