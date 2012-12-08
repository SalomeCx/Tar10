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

#include "lire.h"

// Renvoie 0 si la lecture s'est bien passée, -1 si l'ouverture de l'archive s'est mal passée, et 1 si la lecture s'est mal passée.
int lireEntetes(char * nomArchive, Fichier * listHd, int compteur){
  FILE * archive = fopen(nomArchive, "r");
  if (archive == NULL)
    return -1;

  for (int i = 0; i < compteur; i++)
      {
	Fichier hder = headerVide();
	if (fread(hder, sizeof(struct fichier), 1, archive) == sizeof(struct fichier))
	  return 1;
	fseek(archive, hder->taille, SEEK_CUR);
	listHd[i] = malloc(sizeof(struct fichier));
	listHd[i] = hder;
	
      }

  fclose(archive);
  return 0;
  // Il faudra penser à free les headers dans le main.
}

// Duplication de code. Pas d'autre idées pour récupérer le nombre de fichiers dans l'archive.
// Passer un int * en paramètre à lireEntetes ne fonctionne pas (warnings et memory map error).
int nbEntetes(char * nomArchive)
{
  FILE * archive = fopen(nomArchive, "r");
  if (archive == NULL)
    return -1;

  int cpt = 0;
  while (1)
    {
      Fichier hder = headerVide();

      fread(hder, sizeof(struct fichier), 1, archive);

      //Quand on arrive à un fichier de taille 0, c'est-à-dire quand on a fini la lecture.
      if (hder->taille == 0)
	break;

      fseek(archive, hder->taille, SEEK_CUR);
      rmHeader(hder);
      cpt++;
    }
  fclose(archive);

  return cpt;
}

// Retourne la position du fichier file dans l'archive nomArchive.
// Duplication de code avec rmFile (dans options.c).
long chercherFichier(char * nomArchive, char * file)
{
  long position = 0;

  int nb = nbEntetes(nomArchive);

  Fichier * headers = malloc(sizeof(struct fichier) * nb);
  lireEntetes(nomArchive, headers, nb);

  FILE * archive = fopen(nomArchive, "r+");

  for (int i = 0; i < nb; i++)
    {
      // Une fois que l'on a trouvé le fichier correspondant dans l'archive.
      if (strcmp(file, headers[i]->nom) == 0)
	{
	  fclose(archive);
	  return position;
	}
      else
	{
	  // Tant qu'on ne trouve pas le fichier, on avance de la taille du fichier courant + la taille de son header.
	  position += sizeof(struct fichier);
	  position += headers[i]->taille;
	}
    }
  fclose(archive);
  return position;
}
