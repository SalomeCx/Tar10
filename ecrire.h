// -*- coding: utf-8 -*- 
#ifndef ECRIRE_H
#define ECRIRE_H

void ecrireNom(Fichier hd, FILE* archive);
void ecrireTaille(Fichier hd, FILE* archive, char* tmp);
void ecrirePermissions(Fichier hd, FILE* archive, char* tmp);
void ecrireContenu(Fichier hd, FILE* archive);
void ecrireModification(Fichier hd, FILE* archive);

#endif

