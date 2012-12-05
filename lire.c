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


char * lireNom(char * nomArchive){
  FILE* archive;
  int buff = 0;
  char * nom;  
  archive = fopen(nomArchive, "r");
  if (archive == NULL)
    printf("pas ouvert\n");
  do{
    buff = fgetc(archive);
    //printf("%c", buff);
    if (buff == '#'){
      fgets(nom, 0, archive);
      //printf("%s\n", nom);
    }
  }
    while(buff != EOF);
  // printf("%lu\n", sizeof(nom));
  return nom;
  fclose(archive);
}


  int main(int argc, char *argv[]) {
    char * nom;
    char * archive = "archive.txt";
    nom = lireNom(archive);
    //printf("%lu\n", sizeof(nom));
    printf("%s\n", nom);
    return EXIT_SUCCESS;
  }
  
