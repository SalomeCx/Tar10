// -*- coding: utf-8 -*- 
#include <stdio.h>
#include <stdlib.h>
#include "help.h"

void helpc(void)
{
  printf("-c\t:\tCrée une archive à partir de la liste de fichiers en argument. \n");
}

void helpv(void)
{
  printf("-v\t:\tAffiche des détails sur l'exécution de la commande.\n");
}

void helpt(void)
{
  printf("-t\t:\tListe les fichiers et répertoires contenus dans l'archive passée en paramètre.\n");
}

void helpr(void)
{
  printf("-r\t:\tAjoute de nouveaux fichiers à l'archive passée en paramètre.\n");
}

void helpu(void)
{
  printf("-u\t:\tMet l'archive à jour si les fichiers en paramètre sont plus récents.\n");
}

void helpx(void)
{
  printf("-x\t:\tExtrait les fichiers de l'archive.\n");
}

void helpf(void)
{
  printf("-f\t:\tPrécise le nom du fichier d'archive. \n");
}

void helpz(void)
{
  printf("-z\t:\tCompresse le fichier d'archive.\n");
}

void helpd(void)
{
  printf("-d\t:\tSupprime le fichier en paramètre de l'archive.\n");
}

void helpsparse(void)
{
  printf("-sparse\t:\tEconomise la place dans les fichiers contenants beaucoup de zéros consécutifs.\n");
}

void helpm(void)
{
  printf("-m\t:\tAffiche les différences entre les fichiers archivés et les fichiers existants.\n");
}
