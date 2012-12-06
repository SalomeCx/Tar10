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
#include <assert.h>
#include "options.h"


void ecrireHeader(Fichier hd, FILE* archive){
  fwrite(hd, 1, sizeof(struct fichier), archive);
  //fputc('\n', archive);
}

void ecrireTaille(Fichier hd, FILE* archive, char* tmp){
  sprintf(tmp, "%d", hd->taille);
  fwrite(tmp, 1, sizeof(tmp), archive);
  fputc('\n', archive);
}

void ecrirePermissions(Fichier hd, FILE* archive, char* tmp){
  sprintf(tmp, "%d", hd->permissions);
  fwrite(tmp, 1, sizeof(tmp), archive);
  fputc('\n', archive);  
}

void ecrireModification(Fichier hd, FILE* archive){
  fwrite(hd->date, 1, 20, archive);
  fputc('\n', archive);
}

void ecrireContenu(Fichier hd, FILE* archive){
  // Descripteur de fichier;
  int fichier;  
  fichier = open(hd->nom, O_RDONLY, S_IRUSR | S_IWUSR);
  //fputc('\n', archive);
  //ecrire le contenu du fichier
  char * buff = malloc(sizeof(char) * (hd->taille));
  assert(buff);
  lseek(fichier, 0, SEEK_SET);
  read(fichier, buff, sizeof(char)*hd->taille);
  fwrite(buff, sizeof(char), hd->taille, archive);
  fputc('\n', archive);  
  close(fichier);
  free(buff);
}

