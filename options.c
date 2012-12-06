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
#include <assert.h>
#include <string.h>
#include <time.h>
#include "options.h"
#include "ecrire.h"
#include "header.h"

// Créer l'archive, et les entêtes.

FILE* creerArchive(char* nomArchive){

  // Fichier archive.
  FILE* archive;
  archive = fopen(nomArchive, "a+");

  return archive;
}

void ajouterFichier(FILE* archive, char* nomFichier){
  Fichier hd = initHeader(nomFichier);

  ecrireHeader(hd,archive);   
  ecrireContenu(hd,archive);
}

void liste(char* nomArchive, char* tabFichiers[], int nbFiles)
{
  FILE* archive=creerArchive(nomArchive);
  for(int i = 0; i<nbFiles; i++)
    { 
      ajouterFichier(archive, tabFichiers[i]);
    }
  fclose(archive);
}

//Compresser une archive
void compresserArchive(char * nomArchive){
  
  char str[20];
  strcpy(str, "gzip ");
  strcat(str, nomArchive);
  system(str);
}


//Decompresser une archive
void decompresserArchive(char * nomArchiveCompresser){
  
  char str[20];
  strcpy(str, "gzip -d ");
  strcat(str, nomArchiveCompresser);
  system(str);
}



  
