// -*- coding: utf-8 -*- 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "options.h"
#include "header.h"
#include "lire.h"

int main(int argc, char *argv[]) {
  
  // Récupère tous les arguments dans un tableau.
  char* tab[argc - 1];
  char* nomArchive = "archive.tar";
  for (int i = 0; i < (argc - 1); i++)
    {
      tab[i] = argv[i + 1];
    }
  liste(nomArchive, tab, argc - 1);
  
  int nb = nbEntetes(nomArchive);
  // Initialisation.
  Fichier * headers = malloc(sizeof(struct fichier) * nb);

  lireEntetes(nomArchive, headers, nb);

  for (int i = 0; i < nb; i++)
    {
      printf("Nom: %s\n", headers[i]->nom);
      printf("Taille: %d\n", headers[i]->taille);
      printf("Droits: %d\n", headers[i]->permissions);
      printf("Date: %s\n\n", headers[i]->date);
      rmHeader(headers[i]);
    }

  free(headers);

  int opt;
  char format[]="hvtx:crufzdm:";
  
  while ((opt = getopt(argc, argv, format)) != -1) {  
    
    switch (opt) {  
    case 'h':  
      printf ("Paramètre h recontré\n");  
      break;  
    case 'v':  
      printf ("Paramètre v recontré\n");  
      break;  
    case 't':  
      printf ("Paramètre t rencontré avec argument %s\n", optarg);  
      break;  
    case 'x':  
      printf ("Paramètre x rencontré avec argument %s\n", optarg);  
      break;  
    case 'c':  
      printf ("Paramètre c recontré\n");  
      break;  
    case 'r':  
      printf ("Paramètre r recontré\n");  
      break;  
    case 'u':  
      printf ("Paramètre u rencontré avec argument %s\n", optarg);  
      break;  
    case 'f':  
      printf ("Paramètre f rencontré avec argument %s\n", optarg);  
      break;
    case 'z':  
      printf ("Paramètre z recontré\n");  
      break;  
    case 'd':  
      printf ("Paramètre d recontré\n");  
      break;  
    case 'm':  
      printf ("Paramètre m rencontré avec argument %s\n", optarg);  
      break;    
    }  
  }
  return EXIT_SUCCESS; 
}
