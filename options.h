#ifndef OPTIONS_H
#define OPTIONS_H

int tailleFichier(char *);
int permissions(char* fichier);
void modification(char* fichier);
int aide();
int creer_archive(char *nomArchive, char* fichiers[]);
int ajouter(char *nomArchive, char* fichiers[]);
int lister_archive(char *nomArchive);
int mettre_a_jour(char *nomArchive, char* fichiers[]);
int extraire(char *nomArchive);
int compresser(char *nomArchive);
int supprimer(char *nomArchive,char* fichiers[]);
int difference(char *nomArchive,char* fichiers[]);

#endif
