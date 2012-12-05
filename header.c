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

#include "header.h"

char* getNom(char * fichier)
{
  return fichier;
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

void modification(struct fichier *f)
{
  struct stat modify;
  if (stat((*f).nom, &modify) == -1)
    exit(1);

  struct tm time = *localtime(&modify.st_mtime);
  strftime (f->date, 20/*sizeof(f->date)*/, "%d/%m/%Y %H:%M:%S", &time);
  }

struct fichier * initHeader(char * fichier)
{
  struct fichier * header = (struct fichier *) malloc(sizeof(struct fichier *));
  assert(header);

  header->date = malloc(sizeof("JJ/MM/AAAA HH:MM:SS"));
  assert(header->date);
  
  header->nom = getNom(fichier);
  header->taille = tailleFichier(fichier);
  header->permissions = permissions(fichier);
  modification(header);

  printf("%s, %d, %d, %s\n", header->nom, header->taille, header->permissions, header->date);

  return header;
}

void rmHeader(struct fichier * header)
{
  free(header->date);
  free(header);
}
