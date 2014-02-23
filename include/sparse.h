/*
// -*- coding: utf-8 -*- 
#ifndef SPARSE_H
#define SPARSE_H

typedef struct sparse * Sparse;
//implementation Yale Sparse Matrix
struct sparse{
  int **matrice;
  int nbLignes;
  int *ja;
  int *a;
  int *ia;
  const int nbColonnes;
}nbColonnes = 300;

int** nbLignes(int **matrice);

//utilise pour allouer le nombre de bits a 1 pour sparse
void ajouterAlloc(int *i);

//calcul de IA pour sparse
void calculIa(struct sparse sp);

//calcul de JA pour sparse
void calculerJa(struct sparse sp);

void calculerA(struct sparse sp);

void sparse(char *fichier);

void matrice(struct sparse sp,char *fichier);

void liberer(struct sparse sp);

void restaurerSparse(struct sparse sp);

#endif
*/
