// -*- coding: utf-8 -*- 
#ifndef ECRIRE_H
#define ECRIRE_H
void ecrire_taille(struct fichier f, FILE* archive, char* tmp);
void ecrire_nom(struct fichier f, FILE* archive);
void ecrire_permissions(struct fichier f, FILE* archive, char* tmp);
void ecrire_contenu(struct fichier f, FILE* archive);
void ecrire_modification(struct fichier f, FILE* archive);
#endif
