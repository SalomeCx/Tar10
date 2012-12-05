#ifndef HEADER_H
#define HEADER_H

struct fichier{
  char* nom;
  int taille;
  int permissions;
  char* date/*[sizeof "JJ/MM/AAAA HH:MM:SS"]*/;
};

typedef struct fichier * Fichier;

char* getNom(char * fichier);
int tailleFichier(char* fichier);
int permissions(char* fichier);
void modification(Fichier *f);
Fichier initHeader(char * fichier);
void rmHeader(Fichier header);

#endif
