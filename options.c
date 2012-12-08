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

/* Ajoute le fichier nomFichier à l'archive archive.
   Attention, l'archive doit être ouverte en "a+" pour ne pas effacer les fichiers déjà présents. */
void ajouterFichier(FILE* archive, char* nomFichier){
  Fichier hd = initHeader(nomFichier);

  ecrireHeader(hd,archive);   
  ecrireContenu(hd,archive);
}

/* Ajoute à l'archive nomArchive tous les fichiers contenus dans tabFichiers[].
   nbFiles représente le nombre de fichiers à rajouter, c'est à dire la taille de tabFichier[]. */
void liste(char* nomArchive, char* tabFichiers[], int nbFiles)
{
  FILE* archive = fopen(nomArchive, "a+");
  for(int i = 0; i<nbFiles; i++)
    { 
      ajouterFichier(archive, tabFichiers[i]);
    }
  fclose(archive);
}

/* Enlève le fichier fichier de l'archive nomArchive. */
void rmFile(char * nomArchive, char * fichier)
{
  /* On recherche le nombre de fichiers dans nomArchive. */
  int nb = nbEntetes(nomArchive);
  /* Initialisation et création des headers. */
  Fichier * headers = malloc(sizeof(struct fichier) * nb);
  lireEntetes(nomArchive, headers, nb);

  FILE* archive = fopen(nomArchive, "r+");

  /* offEcrire est la position du début du header du fichier à enlever dans l'archive. */
  long offEcrire = 0;
  /* reste est la taille de tout ce qui se trouve après la fin du fichier à enlever. */
  long reste = 0;

  for (int i = 0; i < nb; i++)
    {
      /* Une fois que l'on a trouvé le fichier à supprimer. */
      if (strcmp(fichier, headers[i]->nom) == 0)
	{
	  /* On récupère la taille de ce qu'il faut écrire. */
	  for (int j = (i + 1); j < nb; j++)
	    {
	      reste += sizeof(struct fichier);
	      reste += headers[j]->taille;
	    }

	  char * buff = malloc(reste);
	  /* On se place juste après le fichier à supprimer, et on lit tout le reste. */
 	  fseek(archive, (offEcrire + sizeof(struct fichier) + headers[i]->taille), SEEK_SET);
	  fread(buff, 1, reste, archive);

	  /* On se replace au début du fichier à supprimer et on écrit par dessus. */
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
  /* On troncature le fichier de (- (taille du fichier supprimé + taille du header)) car on
     réécrit par dessus le reste de l'archive. */
  truncate(nomArchive, (offEcrire + reste));
  /* On désalloue les headers. */
  for (int i = 0; i < nb; i++)
    {
      rmHeader(headers[i]);
    }
  free(headers);
}

/* Met à jour l'archive si le fichier passé en paramètre est différent de celui du même nom contenu dans l'archive. */
void miseAJour(char * nomArchive, char * fichier){
  // On récupère les headers.
  int nb = nbEntetes(nomArchive);
  Fichier * headers = malloc(sizeof(struct fichier) * nb);
  lireEntetes(nomArchive, headers, nb);

  if (estDifferent(fichier, headers, nb) == 1)
    {
	rmFile(nomArchive, fichier);
	FILE* archive = fopen(nomArchive, "a+");
	ajouterFichier(archive, fichier);
	fclose(archive);
    }
}

/* Renvoie 0 si le fichier passé en paramètre est le même que celui du même nom dans l'archive dont
   les headers sont passés en paramètre, et 1 s'il est différent.
   Cette fonction ne s'occupe pas du cas où le fichier ne serait pas contenu dans l'archive. */
int estDifferent(char * fichier, Fichier * headers, int nb)
{
  Fichier headerFichier = initHeader(fichier);
  /* On compare. */
  for (int i = 0; i < nb; i++)
    {
      if(strcmp(headers[i]->nom, headerFichier->nom) == 0)
	{
	  if(strcmp(headers[i]->date, headerFichier->date) != 0)
	    {
	      return 1;
	    }
	}
    }
  return 0;
}


/* Compresser une archive */
void compresserArchive(char * nomArchive){
  /*
  int fd[2];
  pipe(fd);

  pid_t fils = fork();
  if (fils == 0)
    {
      close(fd[0]);
      dup2(fd[1], 1);
      close(fd[1]);
      execl("gzip", "gzip", NULL);
      perror("Erreur sur exec.");
      return EXIT_FAILURE;
    }
  int stat;
  waitpid(fils1, &stat, 0);
  return WEXITSTATUS(stat);

  */
  char str[20];
  strcpy(str, "gzip ");
  strcat(str, nomArchive);
  system(str);
}


/* Décompresser une archive. */
void decompresserArchive(char * nomArchiveCompresser){
  
  char str[20];
  strcpy(str, "gzip -d ");
  strcat(str, nomArchiveCompresser);
  system(str);
}


/* Ne fonctionne probablement pas, mais sait-on jamais. Compilation OK.
   Duplication de code, sûrement. */
void difference(char *nomArchive, char *fichier[], int nbFichiers){
  int nb = nbEntetes(nomArchive);
  Fichier * headers = malloc(sizeof(struct fichier) * nb);
  lireEntetes(nomArchive, headers, nb);
  
  for (int i = 0; i < nbFichiers; i++)
    {
      if (estDifferent(fichier[i], headers, nb) == 1)
	{
	  /* On récupère la position du fichier dans l'archive. */
	  long posit = chercherFichier(nomArchive, fichier[i]);
	  /* On initialise son header. */
	  Fichier hd = initHeader(fichier[i]);

	  /* On ouvre archive et fichier pour comparer. */
	  FILE * archive = fopen(nomArchive, "r");
	  FILE * fichieri = fopen(fichier[i], "r");

	  /* On se place au début du fichier (sans son header) dans l'archive. */
	  fseek(archive, (posit + sizeof(struct fichier)), SEEK_SET);
	  printf("Fichier %s :\n", fichier[i]);

	  /* On compare jusqu'à arriver à la fin du fichier. */
	  while (!feof(fichieri))
	    {
	      char * strf = malloc(sizeof(char *));
	      char * stra = malloc(sizeof(char *));
	      
	      /* On récupère chaque ligne des deux fichiers dans un char* temporaire. */
	      strf = fgets(strf, hd->taille, fichieri);
	      stra = fgets(stra, headers[i]->taille, archive);

	      /* Si les deux lignes sont différentes, on affiche les différences. */
	      if (strcmp(strf, stra) != 0)
		{
		  printf("%s\t\t%s\n", strf, stra);
		}
	      free(strf);
	      free(stra);
	    }

	  /* Pour séparer deux fichiers. */
	  printf("------------------------------------\n\n");

	  /* On ferme le tout. */
	  fclose(archive);
	  fclose(fichieri);

	  /* On désalloue, et on passe au fichier suivant s'il existe. */
	  rmHeader(hd);
	}
    }
  free(headers);
}

/* Extrait tous les fichiers contenus dans l'archive. N'efface pas ces fichiers de l'archive. 
   Les fichiers extraites n'ont malhereusement pas les même droit et date de dernieère modification que les fichiers dans l'archive.*/
void extraireFichiers(char * nomArchive)
{
    int nb = nbEntetes(nomArchive);
    Fichier * headers = malloc(sizeof(struct fichier) * nb);
    lireEntetes(nomArchive, headers, nb);
    FILE * archive = fopen(nomArchive, "r");
   
    //long cpt = 0;
   
    /* On s'assure que l'on est au début de l'archive. */
    fseek(archive, 0, SEEK_SET);
   
    for (int i = 0; i < nb; i++)
    {
        /* A chaque tour de boucle, on ignore les headers. */
        fseek(archive, sizeof(struct fichier), SEEK_CUR);
        char * buff = malloc(sizeof(char *) * headers[i]->taille);
        /* On crée un fichier du nom voulu. S'il existe déjà, il est écrasé à cause du "w+". */
        FILE * file = fopen(headers[i]->nom, "w+");
        /* On lit le fichier dans l'archive. */
        fread(buff, 1, headers[i]->taille, archive);
        /* On l'écrit dans le nouveau fichier. */
        fwrite(buff, 1, headers[i]->taille, file);
        fclose(file);
        free(buff);
    }
}

  void listerFichier(char * nomArchive){
    int nb = nbEntetes(nomArchive);
    Fichier * headers = malloc(sizeof(struct fichier) * nb);
    lireEntetes(nomArchive, headers, nb);
    for (int i = 0; i < nb; i++)
      {
	printf("%s\n", headers[i]->nom);
	rmHeader(headers[i]);
      }
    free(headers);
  }
