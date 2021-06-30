#include <stdio.h>
#include "titreHTMLperson.h"
#define MAX_ID 40

int titreHTMLperson(char * buffer, int * id){

  person person[MAX_ID];
  printf("<h2>%s %s</h2>", person[*id].firstname, person[*id].lastname);

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
  int m = titreHTMLperson(buffer, &id);
  printf("\n%d characters written\n", m);
  return m;
}
