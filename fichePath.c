#include <stdio.h>
#include "fichePath.h"
#define MAX_ID 40

int fichePath(char * buffer, int * id){

  person person[MAX_ID];
  sprintf(buffer, "%d-fiche.html", *id);
  printf("%s", buffer);
}


int main(){

  int id;
  printf("Choisissez l' ID :\n");
  scanf("%d", &id);

  if(id > MAX_ID || id < 0){
    printf("la personne n'existe pas\n");
    return 1;
  }

  person person[MAX_ID];
  char buffer[255];
  int m = fichePath(buffer, &id);
  printf("\n%d characters written\n", m);
  return m;
}
