#ifndef HEADER_H
#define HEADER_H

struct fichier{
  char* nom;
  int taille;
  int permissions;
  char* date/*[sizeof "JJ/MM/AAAA HH:MM:SS"]*/;
};

char* getNom(char * fichier);
int tailleFichier(char* fichier);
int permissions(char* fichier);
void modification(struct fichier *f);
struct fichier * initHeader(char * fichier);
void rmHeader(struct fichier * header);

#endif
