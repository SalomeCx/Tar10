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

// On écrit le header en entier directement dans la structure.
void ecrireHeader(Fichier hd, FILE* archive){
  fwrite(hd, 1, sizeof(struct fichier), archive);
 }

void ecrireContenu(Fichier hd, FILE* archive){
  // Descripteur de fichier;
  int fichier;  
  fichier = open(hd->nom, O_RDONLY, S_IRUSR | S_IWUSR);
  //ecrire le contenu du fichier
  char * buff = malloc(sizeof(char) * (hd->taille));
  assert(buff);
  // On se place au début du fichier
  lseek(fichier, 0, SEEK_SET);
  // On lit le tout.
  read(fichier, buff, sizeof(char)*hd->taille);
  // On écrit tout. Le fichier est ouvert en a+, donc on n'écrase pas les headers.
  fwrite(buff, sizeof(char), hd->taille, archive);
  close(fichier);
  free(buff);
}
