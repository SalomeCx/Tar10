// -*- coding: utf-8 -*- 
#ifndef OPTIONS_H
#define OPTIONS_H

#include "header.h"

int aide();
int estDifferent(char * fichier, Fichier * headers, int nb);
void ajouterFichier(FILE* archive, char* nomFichier);
void liste(char *nomArchive, char* fichiers[], int nbFiles);
int ajouter(char *nomArchive, char* fichiers[]);
void listerFichier(char *nomArchive);
int mettreAJour(char *nomArchive, char* fichiers[]);
void extraireFichiers(char *nomArchive);
int compresser(char *nomArchive);
void miseAJour(char * nomArchive, char * fichier);
int supprimer(char *nomArchive,char* fichiers[]);
void difference(char *nomArchive,char* fichiers[], int nb);
void rmFile(char * nomArchive, char * fichier);
void compresserArchive(char * nomArchive);
void decompresserArchive(char * nomArchiveCompresser);

#endif
