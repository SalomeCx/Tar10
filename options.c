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
#include "lire.h"

void ajouterFichier(FILE* archive, char* nomFichier){
  Fichier hd = initHeader(nomFichier);

  ecrireHeader(hd,archive);   
  ecrireContenu(hd,archive);
}

void liste(char* nomArchive, char* tabFichiers[], int nbFiles)
{
  FILE* archive = fopen(nomArchive, "a+");
  for(int i = 0; i<nbFiles; i++)
    { 
      ajouterFichier(archive, tabFichiers[i]);
    }
  fclose(archive);
}

void rmFile(char * nomArchive, char * fichier)
{
  int nb = nbEntetes(nomArchive);
  // Initialisation.
  Fichier * headers = malloc(sizeof(struct fichier) * nb);
  lireEntetes(nomArchive, headers, nb);

  FILE* archive = fopen(nomArchive, "rw");

  long offEcrire = 0;

  for (int i = 0; i < nb; i++)
    {
      // Une fois que l'on a trouvé le fichier à supprimer.
      if (strcmp(fichier, headers[i]->nom) == 0)
	{
	  // On récupère la taille de ce qu'il faut écrire.
	  long reste = 0;
	  for (int j = (i + 1); j < nb; j++)
	    {
	      reste += sizeof(struct fichier);
	      reste += headers[j]->taille;
	    }

	  char * buff = malloc(reste);
 	  fseek(archive, (offEcrire + sizeof(struct fichier) + headers[i]->taille), SEEK_SET);
	  fread(buff, reste,1, archive);
	  printf("%s\n", buff);

	  fseek(archive, offEcrire, SEEK_SET);
	  fwrite(buff, reste, 1, archive);
	  break;
	  
	}
      else
	{
	  offEcrire += sizeof(struct fichier);
	  offEcrire += headers[i]->taille;
	}
    }

  for (int i = 0; i < nb; i++)
    {
      rmHeader(headers[i]);
    }
  free(headers);

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



  
