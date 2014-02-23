#ifndef HEADER_H
#define HEADER_H

struct fichier{
  char nom[100];
  int taille;
  int permissions;
  char date[20]/*[sizeof "JJ/MM/AAAA HH:MM:SS"]*/;
};

typedef struct fichier * Fichier;

int tailleFichier(char* fichier);
int permissions(char* fichier);
void modification(Fichier *f);
Fichier initHeader(char * fichier);
Fichier headerVide(void);
void rmHeader(Fichier header);

#endif
