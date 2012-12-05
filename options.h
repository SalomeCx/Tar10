// -*- coding: utf-8 -*- 
#ifndef OPTIONS_H
#define OPTIONS_H

#include "header.h"

FILE* creerArchive(char* nomArchive);
//int tailleFichier(char * fichier);
//int permissions(char* fichier);
//void modification(struct fichier *f);
int aide();
void ajouterFichier(FILE* archive, char* nomFichier);
void liste(char *nomArchive, char* fichiers[], int nbFiles);
int ajouter(char *nomArchive, char* fichiers[]);
int listerArchive(char *nomArchive);
int mettreAJour(char *nomArchive, char* fichiers[]);
int extraire(char *nomArchive);
int compresser(char *nomArchive);
int supprimer(char *nomArchive,char* fichiers[]);
int difference(char *nomArchive,char* fichiers[]);
void compresserArchive(char * nomArchive);
void decompresserArchive(char * nomArchiveCompresser);
#endif
