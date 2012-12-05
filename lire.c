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
int lireEntetes(char * nomArchive/*, Fichier * listHd*/){
  FILE * archive = fopen(nomArchive, "r");
  if (archive == NULL)
    printf("pas ouvert\n");
  
  char tmp[100];
  memset(tmp, '\0', 100);
  //char * tmp2 = malloc(20);

  char nom[100];
  memset(nom, '\0', 100);

  int nb = 0;
  
  while (!feof(archive))
    {
      // On assume qu'un nom de fichier fait moins de 100 caractères, comme dans les headers de la vraie fonction tar.
      fgets(nom, 100, archive);
      printf("Nom: %s", nom);
      //listNoms[nb] = nom;
      memset(nom, '\0', 100);
      // La taille.
      fgets(tmp, 100, archive);
      int taille = atoi(tmp);
      printf("Taille: %d\n", taille);

      // On passe la ligne des droits.
      memset(tmp, '\0', 100);
      fgets(tmp, 100, archive);
      printf("Droits: %s\n", tmp);
      
      // On passe la ligne de la date.
      memset(tmp, '\0', 100);
      fgets(tmp, 100, archive);
      printf("Date: %s\n", tmp);

      // On avance de taille dans le fichier, puis on saute une ligne: on arrive à l'en-tête du fichier suivant.
      memset(tmp, '\0', 100);
      fseek(archive, taille, SEEK_CUR);
      fgets(tmp, 100, archive);
      //printf("\n%s", tmp);
      memset(tmp, '\0', 100);
      printf("\n\n");
      
      nb++;
      /* fgets(tmp, 100, archive);
      printf("\n%s\n", tmp);
      printf("\n%d", taille);*/

      //printf("\n\n%d\n\n",taille);
      }
  fclose(archive);
  return (nb - 1);
}

