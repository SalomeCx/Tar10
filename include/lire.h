// -*- coding: utf-8 -*- 
#ifndef LIRE_H
#define LIRE_H

#include "header.h"

int lireEntetes(char * nomArchive, Fichier * listHd, int compteur);
int nbEntetes(char * nomArchive);
long chercherFichier(char * nomArchive, char * file);

#endif
