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

int creer_archive(char* nomArchive, char* tabFichiers[]){
  int archive;
  int fichier;
  char buff;
  int nbrFichiers = sizeof(tabFichiers)/sizeof(tabFichiers[0]);
  archive = open(nomArchive, O_WRONLY|O_CREAT, 0777);
  for(int i = 0; i<nbrFichiers; i++){ 
    fichier = open(tabFichiers[i],O_RDONLY);
    int taille = tailleFichier(tabFichiers[i]);
    int permission = permissions(tabFichiers[i]);
    modification(tabFichiers[i]);

    char* taille2;
    
    write(archive, "123", sizeof(taille));
    //write(archive, &permission, sizeof(permission));
    // write(archive, & stime2, sizeof(stime2));
    while((read(fichier, &buff, SEEK_SET)) > 0){
      write(archive, &buff, 1);
    }
    close(fichier);
  }  


close(archive);

}


int tailleFichier(char* fichier){
  /*struct stat permission;
  if (stat(fichier, &permission) == -1){
    exit(1);
    }
  return permission.st_size;*/
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
  printf("%d\n", sizeof(stime2));
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
  char* tab[] = {argv[1]};
  char* nom = "archive.tar";
  creer_archive(nom, tab);
  modification(argv[1]);
  }
  
