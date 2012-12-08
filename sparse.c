int** nbLignes(int **matrice){
  return sizeof(matrice)/sizeof(*matrice);
}

//utilise pour allouer le nombre de bits a 1 pour sparse
void ajouterAlloc(int *i){
  i = realloc(i,sizeof(i)+sizeof(int));
}

//calcul de IA pour sparse
int* calculIa(int **matrice, int *a,int nbLignes){
  int iac = 0;
  int ac = 0;
  int *ia = malloc((nbLignes+1)*sizeof(int));
  for(int i=0;i<nbLignes;i++){
    for(int j=0;j<300;j++){
      if(matrice[i][j]!=0){
	if(i==iac){
	  ia[iac]=ac;
	  iac++;
	}
	ac++;
      }
    }
  }
  ia[iac] = ac;
  return ia;
}
//calcul de JA pour sparse
int* calculerJa(int **matrice,int *a,int nbLignes){
  int jac = 0;
  int* ja = malloc(sizeof(a));
  for(int i = 0; i < nbLignes; i++){
    for(int j = 0; j < 300; j++){
      if(matrice[i][j]!=0){
	ja[jac]=j;
	jac++;
	}
    }
  }
  return ja;
}


int* calculerA(char **matrice){
  //implementation Yale Sparse Matrix
  int *a=malloc(sizeof(int));
  int ac=0;//compteur de c 
  int nbLignes = nbLignes(matrice);
  int nbColonnes = 300;
  for (int i=0;i<nbLignes;i++){
    for(int j=0;j<nbColonnes;j++){
      if(matrice[i][j]!=0){
	a[ac]=matrice[i][j];
	ajouterAlloc(a);
	ac++;
      }
    }
  }
  return a;
}

void sparse(char *fichier){
  int **matrice = matrice(fichier);
  int nbLignes = nbLignes(matrice);
  int *a = calculerA();
  int *ia = calculerIa(matrice,a,nbLignes);
  int *ja = calculerJa(matrice,a,nbLignes);
  liberer(matrice,a,ai,aj);
}
  
int** matrice(char *fichier){
  //implementation Yale Sparse Matrix
  int fd = open(fichier, O_WRDONLY|O_CREAT, S_IRUSR | S_IWUSR);
  int taille = tailleFichier(fichier);  
  int nbLignes = taille/300+1;
  int nbColonnes = 300;
  int *buff[nbColonnes] = malloc(nbLignes);
  for (int i=0;i<nbLignes;i++){
    for(int j=0;j<nbColonnes;j++){
      read(fichier,buff[i][j],1);
    }
  }
  fd.close();
  return buff;
}

void liberer(int **matrice,int *a, int *ai, int *aj){
  free(buff);
  free(a);
  free(ai);
  free(aj);
}

int* restaurerSparse(int **buff, int *a, int *ai, int *aj){
  for(int ac = 0; ac < sizeof(a); ac++){
    for(int iac = 0; iac < sizeof(ia); iac++){
      for(int index = ia[iac]; index < ia[iac+1]; index++){
	buff[iac]][ja[ac]] = a[index];
      }
    }
  }
