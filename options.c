// -*- coding: utf-8 -*- 
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

// Créer l'archive, et les entêtes.

FILE* creer_archive(char* nomArchive){

  // Fichier archive.
  FILE* archive;
  archive = fopen(nomArchive, "w+");

  return archive;
}

void ajouter_fichier(FILE* archive, char* nomFichier){


  // Descripteur de fichier;
  int fichier;
  char * tmp = malloc(sizeof(struct fichier));
  
  struct fichier f;
  f.nom=nomFichier;
  fichier = open(f.nom, O_RDONLY, S_IRUSR | S_IWUSR);

    
  f.taille = tailleFichier(f.nom);
  f.permission = permissions(f.nom);
  
    
  //nom du fichier
  fwrite(f.nom, 1, sizeof(f.nom), archive);
  
  // On écrit la taille du fichier.
  sprintf(tmp, "%d", f.taille);
  fwrite(tmp, 1, sizeof(tmp), archive);
  //fwrite(" ", 1, 1, archive);
  
  // Les permissions du fichier.
  sprintf(tmp, "%d", f.permission);
  fwrite(tmp, 1, sizeof(tmp), archive);
  //fwrite(" ", 1, 1, archive);
  modification(&f);
  // La date de dernière modification
  
  fwrite(f.date, 1, sizeof(f.date), archive);
  //fwrite(" ", 1, 1, archive);

  // Pour séparer l'entête du reste.
  fputc('\n', archive);
  
  //ecrire le contenu du fichier
  char * buff = malloc(sizeof(char) * f.taille);
  lseek(fichier, 0, SEEK_SET);
  read(fichier, buff, sizeof(char)*f.taille);
  fwrite(buff, sizeof(char), f.taille, archive);
  
  close(fichier);
  free(buff);
  free(tmp);
}

/* Retourne la taille du fichier sous forme d'un entier. */
int tailleFichier(char* fichier)
{
  int fd = open(fichier, O_RDONLY);
  off_t s = lseek(fd, 0, SEEK_END);
  
  close(fd);
  return s;
}

/* retourne les permissions sur le fichier. */
int permissions(char* fichier)
{
  struct stat permission;
  if (stat(fichier, &permission) == -1)
    exit(1);
  return (permission.st_mode & 0777);
}

/* Retourne la date de dernière modification. */
void modification(struct fichier *f)
{
  struct stat permission;
  if (stat((*f).nom, &permission) == -1)
    exit(1);

  struct tm time = *localtime(&permission.st_mtime);
  strftime (f->date, sizeof f->date, "%d/%m/%Y %H:%M:%S", &time);
}

void list(char* nomArchive, char* tabFichiers[], int nbFiles)
{
  FILE* archive=creer_archive(nomArchive);
  for(int i = 0; i<nbFiles; i++)
    { 
      ajouter_fichier(archive, tabFichiers[i]);
    }
  fclose(archive);
}

int main(int argc, char* argv[]){

  // Récupère tous les arguments dans un tableau.
  char* tab[argc - 1];
  char* nom = "archive.tar";
  for (int i = 0; i < (argc - 1); i++)
    {
      tab[i] = argv[i + 1];
    }

  list(nom, tab, argc - 1);
  //  modification(argv[1]);
}
  
