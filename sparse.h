// -*- coding: utf-8 -*- 
#ifndef OPTIONS_H
#define OPTIONS_H

int** nbLignes(int **matrice);

//utilise pour allouer le nombre de bits a 1 pour sparse
void ajouterAlloc(int *i);

//calcul de IA pour sparse
int* calculIa(int **matrice, int *a,int nbLignes);

//calcul de JA pour sparse
int* calculerJa(int **matrice,int *a,int nbLignes);

int* calculerA(char **matrice);

void sparse(char *fichier);

int** matrice(char *fichier);

void liberer(int **matrice,int *a, int *ai, int *aj);

int* restaurerSparse(int **buff, int *a, int *ai, int *aj);

#endif
