#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
#include "options.h"


char stime2[sizeof "JJ/MM/AAAA HH:MM:SS"];//[sizeof("JJ/MM/AAAA HH:MM:SS")];

int creer_archive(char* nomArchive, char* tabFichiers[], int nbFiles){
  // Fichier archive.
  FILE * archive;

  // Descripteur de fichier;
  int fichier;
  char * tmp = malloc(sizeof(char));

  //char buff;

  archive = fopen(nomArchive, "w+");
  for(int i = 0; i<nbFiles; i++){ 
    fichier = open(tabFichiers[i],O_RDONLY, S_IRUSR | S_IWUSR);

    int taille = tailleFichier(tabFichiers[i]);
    int permission = permissions(tabFichiers[i]);
    modification(tabFichiers[i]);
    
    // On écrit la taille du fichier.
    tmp = realloc(tmp, sizeof(char)*sizeof(taille));
    sprintf(tmp, "%d", taille);
    fwrite(tmp, 1, sizeof(tmp), archive);
    fwrite(" ", 1, 1, archive);
    
    // Les permissions du fichier.
    tmp = realloc(tmp, sizeof(char)*sizeof(permission));
    sprintf(tmp, "%d", permission);
    fwrite(tmp, 1, sizeof(tmp), archive);
    fwrite(" ", 1, 1, archive);

    fwrite(stime2, 1, sizeof(stime2), archive);
    fwrite(" ", 1, 1, archive);

    //lseek(fichier, SEEK_SET, 1);
    /*while((read(fichier, &buff, 0)) > 0){
      printf("test %s\n", buff);
      fwrite(&buff, sizeof(char), taille, archive);
      }*/
    close(fichier);
  }
  free(tmp);
  fclose(archive);
}

/* Retourne la taille du fichier sous forme d'un entier. */
int tailleFichier(char* fichier){
  int fd = open(fichier, O_RDONLY);
  off_t s = lseek(fd, 0, SEEK_END);

  close(fd);
  return s;
  }

int permissions(char* fichier){
  struct stat permission;
  if (stat(fichier, &permission) == -1)
    exit(1);
  return (permission.st_mode & 0777);
}

void modification(char* fichier){
  struct stat permission;
  if (stat(fichier, &permission) == -1)
    exit(1);
  //char stime[sizeof "JJ/MM/AAAA HH:MM:SS"];
  struct tm time = *localtime(&permission.st_mtime);
  strftime (stime2, sizeof stime2, "%d/%m/%Y %H:%M:%S", &time);
  //printf("%d\n", sizeof(stime));
  //printf("%s\n", stime);
}

int main(int argc, char* argv[]){

  // Récupère tous les arguments dans un tableau.
  char* tab[argc - 1];
  char* nom = "archive.tar";
  for (int i = 0; i < (argc - 1); i++)
    {
      tab[i] = argv[i + 1];
    }

  creer_archive(nom, tab, argc - 1);
  modification(argv[1]);
  }
  