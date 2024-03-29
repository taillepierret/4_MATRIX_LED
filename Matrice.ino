  ////////////////////////////////////////////////// inclusion des bibliotheques utiles /////////////////////////////////////////////////////

#include "MATRIX.h"


////////////////////////////////////////////////// definition des variables pour le code //////////////////////////////////////////////////


#define NBR_MTX 4
#define periode 0   // periode d'affichage d'un pattern en milliseconde
int buffer[NBR_MTX][hauteur_matrice];
LedControl lc=LedControl(12,11,10, NBR_MTX);
/*
Broche 12 = DIN
Broche 11 = CLK
Broche 10 = CS
*/




//////Modifications de texte :

#define nb_char 18
const int* phrase[nb_char] = {esp,esp,esp,T,A,I,L,L,E,P,I,E,R,R,E,esp,esp,esp}; //message à afficher ici

//////////////////////////////




////////////////////////////////////////////////// definition des fonctions //////////////////////////////////////////////////

void init_matrix(){
  
  for (int i=0; i< NBR_MTX; i++){
    lc.shutdown(i,false);
  /* Set the brightness to a low value */
    lc.setIntensity(i,10);
  /* and clear the display */
    lc.clearDisplay(i);
  }
}


void affichage_char(int num_matrice,const int caractere[hauteur_matrice]){
  for (int i=0; i<8 ; i++){
    lc.setRow(num_matrice,i, caractere[i]);
  }
}




void defilement_gauche(const int* pattern[]){
  
  for(int j=0; j<nb_char; j++){
    for(int i = 9; i<17;i++){
      for(int col=0;col<hauteur_matrice;col++){
        for (int mat=0; mat<NBR_MTX; mat++){
          buffer[mat][col] = pattern[(j+mat)%nb_char][col] << i-9;
          buffer[mat][col] += pattern[(j+1+mat)%nb_char][col] >> 17-i;
          lc.setRow(mat,col, buffer[mat][col]);
        }  
      }
    delay(periode);
    }  
  }

}





void setup() {
  init_matrix();
}


  

////////////////////////////////////////////////// Main //////////////////////////////////////////////////

void loop(){
  defilement_gauche(phrase);
  
}
