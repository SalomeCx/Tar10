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

FILE* creer_archive(char* nomArchive){

  // Fichier archive.
  FILE* archive;
  archive = fopen(nomArchive, "a+");

  return archive;
}

void ajouter_fichier(FILE* archive, char* nomFichier){

  char * tmp = malloc(sizeof(struct fichier));
  struct fichier f;
  f.nom=nomFichier;

  ecrire_nom(f,archive);    

  ecrire_taille(f,archive,tmp);

  ecrire_permissions(f,archive,tmp);

  ecrire_modification(f,archive);

  ecrire_contenu(f,archive);

  free(tmp);
}

void liste(char* nomArchive, char* tabFichiers[], int nbFiles)
{
  FILE* archive=creer_archive(nomArchive);
  for(int i = 0; i<nbFiles; i++)
    { 
      ajouter_fichier(archive, tabFichiers[i]);
    }
  fclose(archive);
}

  
