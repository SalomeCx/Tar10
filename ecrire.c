// -*- coding: utf-8 -*- 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
#include "options.h"

void ecrire_taille(struct fichier f, FILE* archive, char* tmp){
  f.taille = tailleFichier(f.nom);
  // On écrit la taille du fichier.
  sprintf(tmp, "%d", f.taille);
  fwrite(tmp, 1, sizeof(tmp), archive);
 //fwrite(" ", 1, 1, archive);
}

void ecrire_nom(struct fichier f, FILE* archive){
  //nom du fichier
  fwrite(f.nom, 1, sizeof(f.nom), archive);
}

void ecrire_permissions(struct fichier f, FILE* archive, char* tmp){
  f.permissions = permissions(f.nom);
  
  // Les permissions du fichier.
  sprintf(tmp, "%d", f.permissions);
  fwrite(tmp, 1, sizeof(tmp), archive);
  //fwrite(" ", 1, 1, archive);
}

void ecrire_modification(struct fichier f, FILE* archive){
  modification(&f);
  // La date de dernière modification
  
  fwrite(f.date, 1, sizeof(f.date), archive);
  //fwrite(" ", 1, 1, archive);
}

void ecrire_contenu(struct fichier f, FILE* archive){
  // Descripteur de fichier;
  int fichier;  
  fichier = open(f.nom, O_RDONLY, S_IRUSR | S_IWUSR);

  //ecrire le contenu du fichier
  char * buff = malloc(sizeof(char) * f.taille);
  lseek(fichier, 0, SEEK_SET);
  read(fichier, buff, sizeof(char)*f.taille);
  fwrite(buff, sizeof(char), f.taille, archive);
  close(fichier);
  free(buff);
}
