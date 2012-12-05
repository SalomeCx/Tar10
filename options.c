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

  char * tmp = malloc(sizeof(struct fichier));
  Fichier hd = initHeader(nomFichier);


  ecrireNom(hd,archive);    

  ecrireTaille(hd,archive, tmp);

  ecrirePermissions(hd, archive, tmp);

  ecrireModification(hd,archive);

  ecrireContenu(hd,archive);

  free(tmp);
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

  
