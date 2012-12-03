// -*- coding: utf-8 -*- 
#ifndef OPTIONS_H
#define OPTIONS_H

struct fichier{
  char *nom;
  int taille;
  int permission;
  char date[sizeof "JJ/MM/AAAA HH:MM:SS"];
};

int tailleFichier(char * fichier);
int permissions(char* fichier);
void modification(struct fichier *f);
int aide();
int creer_archive(char *nomArchive, struct fichier fichiers[], int nbFiles);
int ajouter(char *nomArchive, char* fichiers[]);
int lister_archive(char *nomArchive);
int mettre_a_jour(char *nomArchive, char* fichiers[]);
int extraire(char *nomArchive);
int compresser(char *nomArchive);
int supprimer(char *nomArchive,char* fichiers[]);
int difference(char *nomArchive,char* fichiers[]);

#endif
