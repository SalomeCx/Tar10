// -*- coding: utf-8 -*- 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "options.h"
#include "header.h"
#include "lire.h"
#include "vworp.h"
#include "help.h"
char * archive;
int main(int argc, char *argv[]) {
   char* tab[argc - 4];
   //On ajouter les fichiers a archiver dans un tableau
   for (int i = 0; i < (argc -4); i++)
     {
       tab[i] = argv[i + 4];
     }

  int nb;
  static int verbose_flag;
  int c;
     
  while (1)
    {
       static struct option long_options[] =
	{
	  {"verbose", no_argument,       &verbose_flag, 1},
	  {"brief",   no_argument,       &verbose_flag, 0},
	  {"add",     no_argument,       0, 'a'},
	  {"append",  no_argument,       0, 'b'},
	  {"delete",  required_argument, 0, 'd'},
	  {"create",  required_argument, 0, 'c'},
	  {"file",    required_argument, 0, 'f'},
	  {0, 0, 0, 0}
	};
      
      int option_index = 0;
     
      c = getopt_long (argc, argv, "vwc:txhr:u:f:zd:m:",
		       long_options, &option_index);      
	
      if (c == -1)
	break;
     
      switch (c)
	{
	case 'c':
	  nb = argc - 4;
	  liste(archive, tab, nb);
	  break;


	case 'v':
	  break;

	  
	case 't':
	  listerFichier(archive);
	  break;
     

	case 'x':
	  extraireFichiers(archive);
	  break;

     
	case 'h':
	  manuel();
	  break;

     
	case 'r':
	  nb = argc - 4;
	  liste(archive, tab, nb);
	  break;


	case 'u':
	  for(int i = 0; i<nb; i++)
	    miseAJour(archive, tab[i]);
	  break;


	case 'f':
	  archive = optarg;
	  break;


	case 'z':
	  compresserArchive(archive);
	  break;



	case 'd':
	  rmFile(archive, tab[0]);
	  break;


	case 'w':
	  vworp();
	  break;


	case 'm':
	  difference(archive, tab, nb);
	  break;

     
	default:
	  abort ();
	}
    }
}
