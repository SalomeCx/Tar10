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

  // Pour être sûr de la taille de mon tableau.
  listHd = realloc(listHd, compteur * sizeof(struct fichier));
  assert(listHd);
  printf("%d\n", compteur);
  for (int i = 0; i < compteur; i++)
      {
	Fichier hder = headerVide();
	if (fread(hder, sizeof(struct fichier), 1, archive) == sizeof(struct fichier))
	  return 1;
	fseek(archive, hder->taille, SEEK_CUR);
	listHd[i] = malloc(sizeof(struct fichier));
	printf("%lo, %lo\n", sizeof(listHd[i]), sizeof(hder));
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
