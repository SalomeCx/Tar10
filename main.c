// -*- coding: utf-8 -*- 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include "options.h"

int main(int argc, char *argv[]) {
  
  // Récupère tous les arguments dans un tableau.
  char* tab[argc - 1];
  char* nom = "archive.txt";
  for (int i = 0; i < (argc - 1); i++)
    {
      tab[i] = argv[i + 1];
    }
  liste(nom, tab, argc - 1);

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
