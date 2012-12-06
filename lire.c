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

#include "lire.h"

// Renvoie le nombre d'entêtes lues.
int lireEntetes(char * nomArchive, Fichier * listHd, int * compteur){
  FILE * archive = fopen(nomArchive, "r");
  if (archive == NULL)
    printf("pas ouvert\n");
  
  //char tmp[100];
  //memset(tmp, '\0', 100);
  //char * tmp2 = malloc(20);

  //char nom[100];
  //memset(nom, '\0', 100);

  for (int i = 0; i <= *compteur; i++)
      {
	// On assume qu'un nom de fichier fait moins de 100 caractères, comme dans les headers de la vraie fonction tar.
	//fgets(nom, 100, archive);
	Fichier hder = headerVide();
	/*if (*/fread(&hder, sizeof(struct fichier), 1, archive);/* != sizeof(struct fichier))
	  return 1;*/
	if (sizeof(listHd)/sizeof(struct fichier) <= *compteur)
	  listHd = realloc(listHd, *(compteur + 1) * sizeof(struct fichier));
	fseek(archive, hder->taille, SEEK_CUR);
	
	printf("Nom: %s", hder->nom);
	printf("Taille: %d\n", hder->taille);
	printf("Droits: %d\n", hder->permissions);
	printf("Date: %s\n\n\n", hder->date);
	rmHeader(hder);
	*compteur++;
      }
  fclose(archive);
  return 0;
}

