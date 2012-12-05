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


void ecrireNom(struct fichier hd, FILE* archive){
  //nom du fichier
  fwrite(hd.nom, 1, strlen(hd.nom), archive);
  fputc('\n', archive);
}

void ecrireTaille(struct fichier hd, FILE* archive, char* tmp){
  sprintf(tmp, "%d", hd.taille);
  fwrite(tmp, 1, sizeof(tmp), archive);
  fputc('\n', archive);
}

void ecrirePermissions(struct fichier hd, FILE* archive, char* tmp){
  sprintf(tmp, "%d", hd.permissions);
  fwrite(tmp, 1, sizeof(tmp), archive);
  fputc('\n', archive);  
}

void ecrireModification(struct fichier hd, FILE* archive){
  fwrite(hd.date, 1, 20, archive);
  fputc('\n', archive);
}

void ecrireContenu(struct fichier f, FILE* archive){
  // Descripteur de fichier;
  int fichier;  
  fichier = open(f.nom, O_RDONLY, S_IRUSR | S_IWUSR);

  //ecrire le contenu du fichier
  char * buff = malloc(sizeof(char) * f.taille);
  lseek(fichier, 0, SEEK_SET);
  read(fichier, buff, sizeof(char)*f.taille);
  fwrite(buff, sizeof(char), f.taille, archive);
  fputc('\n', archive);  
  close(fichier);
  free(buff);
}
