/*
// -*- coding: utf-8 -*-
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "sparse.h"
#include "header.h"


int nbLignes(struct sparse sp){
  return sizeof(sp.matrice)/sizeof(*(sp.matrice));
}


void liberer(struct sparse sp){
  free(sp.matrice);
  free(sp.a);
  free(sp.a);
  free(sp.ja);
}


//utilise pour allouer le nombre de bits a 1 pour sparse
void ajouterAlloc(int *i){
  i = realloc(i,sizeof(i)+sizeof(int));
}


//calcul de IA pour sparse
void calculerIa(struct sparse sp){
  int iac = 0;
  int ac = 0;
  sp.ia = malloc((sp.nbLignes+1)*sizeof(int));
  for(int i=0;i<sp.nbLignes;i++){
    for(int j=0;j<300;j++){
      if(sp.matrice[i][j]!=0){
	if(i==iac){
	  sp.ia[iac]=ac;
	  iac++;
	}
	ac++;
      }
    }
  }
  sp.ia[iac] = ac;
}
//calcul de JA pour sparse
void calculerJa(struct sparse sp){
  int jac = 0;
  sp.ja = malloc(sizeof(sp.a));
  for(int i = 0; i < sp.nbLignes; i++){
    for(int j = 0; j < 300; j++){
      if(sp.matrice[i][j]!=0){
	sp.ja[jac]=j;
	jac++;
	}
    }
  }
}


void calculerA(struct sparse sp){
  //implementation Yale Sparse Matrix
  sp.a=malloc(sizeof(int));
  int ac=0;//compteur de c 
  for (int i=0;i<sp.nbLignes;i++){
    for(int j=0;j<sp.nbColonnes;j++){
      if(sp.matrice[i][j]!=0){
	sp.a[ac]=sp.matrice[i][j];
	ajouterAlloc(sp.a);
	ac++;
      }
    }
  }
}
void sparse(char *fichier){
  struct sparse sp;
  matrice(sp,fichier);
  nbLignes(sp);
  calculerA(sp);
  calculerIa(sp);
  calculerJa(sp);
  liberer(sp);
}
  
void matrice(struct sparse sp,char *fichier){
  int fd = open(fichier, O_RDWR|O_CREAT, S_IRUSR | S_IWUSR);
  int taille = tailleFichier(fichier);  
  sp.nbLignes = taille/300+1;
  sp.matrice = malloc(sp.nbLignes);
  for (int i=0;i<sp.nbLignes;i++){
    for(int j=0;j<sp.nbColonnes;j++){
      read(fd,&sp.matrice[i][j],1);
    }
  }
}

void restaurerSparse(struct sparse sp){
  for(int ac = 0; ac < sizeof(sp.a); ac++){
    for(int iac = 0; iac < sizeof(sp.ia); iac++){
      for(int index = sp.ia[iac]; index < sp.ia[iac+1]; index++){
	sp.matrice[iac][sp.ja[ac]] = sp.a[index];
      }
    }
  }
}
*/
