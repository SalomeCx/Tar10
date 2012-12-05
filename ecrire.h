// -*- coding: utf-8 -*- 
#ifndef ECRIRE_H
#define ECRIRE_H

void ecrireNom(struct fichier hd, FILE* archive);
void ecrireTaille(struct fichier hd, FILE* archive, char* tmp);
void ecrirePermissions(struct fichier hd, FILE* archive, char* tmp);
void ecrireContenu(struct fichier hd, FILE* archive);
void ecrireModification(struct fichier hd, FILE* archive);

#endif

