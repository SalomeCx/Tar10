// -*- coding: utf-8 -*- 
#include <stdio.h>
#include <stdlib.h>
#include "help.h"

void manuel(int i)
{
  printf("-c\t:\tCrée une archive à partir de la liste de fichiers en argument.\n");
  printf("-v\t:\tAffiche des détails sur l'exécution de la commande.\n");
  printf("-t\t:\tListe les fichiers et répertoires contenus dans l'archive passée en paramètre.\n");
  printf("-r\t:\tAjoute de nouveaux fichiers à l'archive passée en paramètre.\n");
  printf("-u\t:\tMet l'archive à jour si les fichiers en paramètre sont plus récents.\n");
  printf("-x\t:\tExtrait les fichiers de l'archive.\n");
  printf("-f\t:\tPrécise le nom du fichier d'archive. \n");
  printf("-z\t:\tCompresse le fichier d'archive.\n");
  printf("-d\t:\tSupprime le fichier en paramètre de l'archive.\n");
  printf("-sparse\t:\tEconomise la place dans les fichiers contenants beaucoup de zéros consécutifs.\n");
  printf("-m\t:\tAffiche les différences entre les fichiers archivés et les fichiers existants.\n");
  if (i == 42)
    printf("-w\t:\tEaster egg.");
}

void usage(void)
{
  printf("Utilisation: ./tar10 <cdtrux>\n Pour afficher l'aide, ./tar10 -h\n\n");
}
