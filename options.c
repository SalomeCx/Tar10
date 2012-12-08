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

// Ajoute le fichier nomFichier à l'archive archive.
// Attention, l'archive doit être ouverte en "a+" pour ne pas effacer les fichiers déjà présents.
void ajouterFichier(FILE* archive, char* nomFichier){
  Fichier hd = initHeader(nomFichier);

  ecrireHeader(hd,archive);   
  ecrireContenu(hd,archive);
}

// Ajoute à l'archive nomArchive tous les fichiers contenus dans tabFichiers[].
// nbFiles représente le nombre de fichiers à rajouter, c'est à dire la taille de tabFichier[].
void liste(char* nomArchive, char* tabFichiers[], int nbFiles)
{
  FILE* archive = fopen(nomArchive, "a+");
  for(int i = 0; i<nbFiles; i++)
    { 
      ajouterFichier(archive, tabFichiers[i]);
    }
  fclose(archive);
}

// Enlève le fichier fichier de l'archive nomArchive.
void rmFile(char * nomArchive, char * fichier)
{
  // On recherche le nombre de fichiers dans nomArchive
  int nb = nbEntetes(nomArchive);
  // Initialisation et création des headers.
  Fichier * headers = malloc(sizeof(struct fichier) * nb);
  lireEntetes(nomArchive, headers, nb);

  FILE* archive = fopen(nomArchive, "r+");

  // offEcrire est la position du début du header du fichier à enlever dans l'archive.
  long offEcrire = 0;
  // reste est la taille de tout ce qui se trouve après la fin du fichier à enlever.
  long reste = 0;

  for (int i = 0; i < nb; i++)
    {
      // Une fois que l'on a trouvé le fichier à supprimer.
      if (strcmp(fichier, headers[i]->nom) == 0)
	{
	  // On récupère la taille de ce qu'il faut écrire.
	  for (int j = (i + 1); j < nb; j++)
	    {
	      reste += sizeof(struct fichier);
	      reste += headers[j]->taille;
	    }

	  char * buff = malloc(reste);
	  // On se place juste après le fichier à supprimer, et on lit tout le reste.
 	  fseek(archive, (offEcrire + sizeof(struct fichier) + headers[i]->taille), SEEK_SET);
	  fread(buff, 1, reste, archive);

	  // On se replace au début du fichier à supprimer et on écrit par dessus.
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
  fclose(archive);
  // On troncature le fichier de (- (taille du fichier supprimé + taille du header)) car on
  // réécrit par dessus le reste de l'archive.
  truncate(nomArchive, (offEcrire + reste));
  // On désalloue les headers.
  for (int i = 0; i < nb; i++)
    {
      rmHeader(headers[i]);
    }
  free(headers);
}

//met a jour l'archive si la date de modification du fichier passe en parametre est differente de celle du fichier correspondant contenu dans l'archive
void miseAJour(char * nomArchive, char * fichier){
  FILE * archive = fopen(nomArchive, "rw");
  Fichier headerFichier = initHeader(fichier);
  int nb = nbEntetes(nomArchive);
  Fichier * headers = malloc(sizeof(struct fichier) * nb);
  lireEntetes(nomArchive, headers, nb);

  for (int i = 0; i < nb; i++){
    if(strcmp(headers[i]->nom, headerFichier->nom) == 0)
      if(strcmp(headers[i]->date, headerFichier->date) != 0){
	rmFile(nomArchive, fichier);
	ajouterFichier(archive, fichier);
      }
  }
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



  
