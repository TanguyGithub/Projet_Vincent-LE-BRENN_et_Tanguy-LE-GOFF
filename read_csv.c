#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filemanagerh"
#define SIZE 200

void read_csv(){
  FILE * fp = fopen("40.csv", "r");
  if(fp == NULL){
    printf("Impossible d'ouvrir le fichier\n");
    exit(1);
  }

  char ligne[SIZE];
  while(fgets(ligne, sizeof(ligne), fp)){
    const char * delimiter = ",";
    char * strToken = strtok(ligne, delimiter);
    while(strToken != NULL){
      printf("%s\n", strToken);
      strToken = strtok(NULL, delimiter);
    }
  }
}

int main(){
  read_csv();
  return 0;
}
