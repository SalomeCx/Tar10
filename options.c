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

/*void ecrire_fichier(char *fichier, char *buffer){
  fwrite(buffer, 1, sizeof(buffer), fichier);
  }*/
void creer(char* nomArchive, struct fichier tabFichiers[], int nbFiles){
  // Fichier archive.
  FILE * archive;

  // Descripteur de fichier;
  int fichier;
  char * tmp = malloc(sizeof(struct fichier));
  
  archive = fopen(nomArchive, "w+");
  for(int i = 0; i<nbFiles; i++)
    { 
      fichier = open(tabFichiers[i].nom, O_RDONLY, S_IRUSR | S_IWUSR);
      
      tabFichiers[i].taille = tailleFichier(tabFichiers[i].nom);
      tabFichiers[i].permission = permissions(tabFichiers[i].nom);
      
      
      //nom du fichier
      fwrite(tabFichiers[i].nom, 1, sizeof(tabFichiers[i].nom), archive);
      
      // On écrit la taille du fichier.
      sprintf(tmp, "%d", tabFichiers[i].taille);
      fwrite(tmp, 1, sizeof(tmp), archive);
      //fwrite(" ", 1, 1, archive);
      
      // Les permissions du fichier.
      sprintf(tmp, "%d", tabFichiers[i].permission);
      fwrite(tmp, 1, sizeof(tmp), archive);
      //fwrite(" ", 1, 1, archive);
      modification(&tabFichiers[i]);
      // La date de dernière modification
      
      fwrite(tabFichiers[i].date, 1, sizeof(tabFichiers[i].date), archive);
      //fwrite(" ", 1, 1, archive);
      // Pour séparer l'entête du reste.
      fputc('\n', archive);
      
      char * buff = malloc(sizeof(char) * tabFichiers[i].taille);
      lseek(fichier, 0, SEEK_SET);
      read(fichier, buff, sizeof(char)*tabFichiers[i].taille);
      fwrite(buff, sizeof(char), tabFichiers[i].taille, archive);
      
      close(fichier);
      free(buff);
  }
  free(tmp);
  fclose(archive);
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

void list(void)
{
}

int main(int argc, char* argv[]){

  // Récupère tous les arguments dans un tableau.
  struct fichier tab[argc - 1];
  char* nom = "archive.tar";
  for (int i = 0; i < (argc - 1); i++)
    {
      tab[i].nom = argv[i + 1];
    }

  creer(nom, tab, argc - 1);
  //  modification(argv[1]);
}
  
