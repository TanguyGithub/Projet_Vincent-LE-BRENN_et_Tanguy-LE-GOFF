#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mainVersionFinale.h"
#define MAX_PERSONNE 200
#define MAX_ID 200
#define GRAND_TAB 100
//seulement 2 donc on s'arrete à 6
#define GENERATION 6



int main(){

  person Test[MAX_PERSONNE+1];

  //Affectaction et ouverture du fichier
  FILE *fic= fopen("200.csv","r");
  signed char texte[256];
  signed char tmp[256];

  int i,k;

  //Si la lecture du fichier echoue, le programme quit automatiquement.
  if(fic == NULL)
    exit(1);

  //variables de passage
  int a,b,c;
  char name[20];
  char lname[20];
  char birth[20];
  char birthzip[20];
  signed char stockage[255];
  int tab_ancetre[GENERATION];

  i=0;

  // variable de la fonction bortherhood :
  int id;

  //Boucle pour parcourir le fichier csv
  while(fgets(texte,255, fic) != NULL){

    strcpy(stockage, texte);
    //printf("%s\n", stockage);

    // Passage sur des variables pour la lisibilité
    a=atoi(strtok(stockage,","));
    b=atoi(strtok(NULL, ","));
    c=atoi(strtok(NULL,","));
    strcpy(name, strtok(NULL,","));
    strcpy(lname, strtok(NULL,"," ));
    strcpy(birth, strtok(NULL,","));
    strcpy(birthzip, strtok(NULL," "));
    //printf("%d,%d,%d,%s %s,%s,%s\n", a, b,c, name, lname, birth, birthzip);

    //Affectaction des variables précèdentes sur le tableau de struct.
    Test[i].id=a;
    Test[i].father_id=b;
    Test[i].mother_id=c;
    strcpy(Test[i].firstname, name);
    strcpy(Test[i].lastname, lname);
    strcpy(Test[i].birthzipcode, birthzip);
    strcpy(Test[i].birthdate, birth);

    //suivre le parcour de la boucle
    //verification si les Affectaction ont bien eu lieu.
    /*printf("%d,%d,%d,%s,%s,%s,%s\n",
    Test[i].id, Test[i].father_id,Test[i].mother_id, Test[i].firstname, Test[i].lastname,  Test[i].birthdate, Test[i].birthzipcode);*/

    i++;
  }

  int Tab_Longueur = i;

  //lier la populations
  link_populations(Test, Tab_Longueur);

  int Id_Person_choix;
  int Id_Pere, Id_Mere;


  int choix;
  printf("\nBonjour, choissisez une action.\n\n");
  printf(" 1:Parcourir la liste \n 2:afficher  les informations de la personne. \n 3:Connaitre les freres de la personne.\n 4:Connaitre les parents de la personne.\n 5:Afficher tout l arbre généalogique de la personne.\n 6:Voir le rendu sur un site internet. \n 0:Qutter le programme.\n");

  //verification
  scanf("%d",&choix);
  /*printf("%d",choix);*/

  if(choix < 0 || choix > 6){
    printf("Choix indisponible\n");
    return 1;
  }


  switch(choix){

    case(0):
    return 0;



    case(1):

    //parcours du tableau de structure
    for(k =0; k <=MAX_PERSONNE; k++){
      printf("%d,%d,%d,%s,%s,%s,%s\n",
      Test[k].id, Test[k].father_id,Test[k].mother_id, Test[k].firstname, Test[k].lastname,  Test[k].birthdate, Test[k].birthzipcode);
    }
    break;



    case(2):
    printf("\nEntrez l'id de la personne :\n");
    scanf("%d", &Id_Person_choix);
    //conditions cas d'erreur
    if(Id_Person_choix < -1 || Id_Person_choix >MAX_PERSONNE-1 || Id_Person_choix==0){
      printf("Données limitées de 1 à %d\n", MAX_PERSONNE-1);
      return 1;
    }
    printf("\n");
    print_ID(Test, Id_Person_choix);
    break;



    case(3):
    printf("\nChoisissez l'id de l'individu :\n");
    scanf("%d", &id);
    if(id < -1 || id > MAX_PERSONNE || id == 0){
      printf("\nDonnées limitées de 1 à %d\n", MAX_PERSONNE);
      return 1;
    }
    brotherhood(Test, id);

    break;



    case(4):
    printf("\nEntrez l'id de la personne\n");
    scanf("%d", &Id_Person_choix);
    //conditions cas d'erreur
    if(Id_Person_choix < -1 || Id_Person_choix >MAX_PERSONNE || Id_Person_choix==0){
      printf("Données limitées de 1 à %d\n", MAX_PERSONNE);
      return 1;
    }

    Id_Pere = Test[Id_Person_choix].father_id;
    Id_Mere = Test[Id_Person_choix].mother_id;

    printf("\ninformations sur le père :\n");
    print_ID(Test, Id_Pere);

    printf("informations sur la mère :\n");
    print_ID(Test, Id_Mere);

    break;



    case(5):

     printf("\nEntrez l'id de la personne\n");
     scanf("%d", &Id_Person_choix);
         //conditions cas d'erreur
    if(Id_Person_choix < -1 || Id_Person_choix >MAX_PERSONNE || Id_Person_choix==0){
      printf("Données limitées de 1 à %d\n", MAX_PERSONNE);
      return 1;
    }
     printf("\n\n=======Individu=======\n\n");
     printf("Nom de la personne : %s %s\nid : %d\t", Test[Id_Person_choix].firstname, Test[Id_Person_choix].lastname, Test[Id_Person_choix].id);
     ancetre(Test, tab_ancetre, Test[Id_Person_choix].id);


      printf("\n\n=======Parents========\n\n");
      print_court(Test, tab_ancetre[2]);
      printf("\n");
      print_court(Test, tab_ancetre[1]);


      printf("\n====Grand-parents=====\n\n");
      printf("Paternels :\n\n");
      // grand-parents paternelle
      print_court(Test,tab_ancetre[3]);
      print_court(Test,tab_ancetre[4]);
      printf("Maternels :\n\n");
      // grand-parents maternelle
      print_court(Test,tab_ancetre[5]);
      print_court(Test,tab_ancetre[6]);


    break;
    case(6):
    break;
  }
  fclose(fic);
  return 0;
}
//fonctions pour lier les parents.
void link_populations(struct Person *Tab, int Longueur){
  int j;
  int idP;
  int idM;
  //Boucle for pour parcourir le tableau, conditions if, else if et else pour chaque cas.
  for(int j = 1; j < Longueur; j++){ // tab[0] est le prototype de la structure des données. On commence à 1.
    if( Tab[j].mother_id > Longueur || Tab[j].father_id > Longueur){//
      Tab[j].p_father = &(Tab[j]);
      Tab[j].p_mother = &(Tab[j]);
    }else if( Tab[j].mother_id == 0){
      Tab[j].p_mother = &(Tab[j]);
    }else if( Tab[j].father_id == 0){
      Tab[j].p_father = &(Tab[j]);
    }else{
      idM=Tab[j].mother_id;
      idP=Tab[j].father_id;
      Tab[j].p_mother = &(Tab[idM]);
      Tab[j].p_father = &(Tab[idP]);
    }
  }
}
void ancetre(struct Person *Tab_Struct, int *Tab_Anc, int Id_Person){
  int i =0;
  int indicePere = 2*i +1;
  int indiceMere = 2*i +2;
  Tab_Anc[i] = Tab_Struct[Id_Person].id;
  //pere
  Tab_Anc[indicePere] =Tab_Struct[Id_Person].father_id;
  //mere
  Tab_Anc[indiceMere]= Tab_Struct[Id_Person].mother_id;
  //Grand-Parents Maternels
  //grand mere
  Tab_Anc[2*indiceMere +2] = Tab_Struct[Tab_Anc[indiceMere]].mother_id;
  //grand pere
  Tab_Anc[2*indiceMere +1] = Tab_Struct[Tab_Anc[indicePere]].father_id;
  //Grand-Parents Paternels
  //grande mere
  Tab_Anc[2*indiceMere +2] = Tab_Struct[Tab_Anc[indicePere]].mother_id;
  //grand pere
  Tab_Anc[2*indicePere +1]= Tab_Struct[Tab_Anc[indicePere]].father_id;
}
//fonction qui permet d'afficher les informations d'une personne
void print_ID(struct Person *Tab, int Id_Person){
  if(Tab[Id_Person].id == 0 || Tab[Id_Person].id == MAX_PERSONNE  || Tab[Id_Person].id < 0){
    printf("Individu inconnu\n\n");
  }else{
  printf(" Id: %d \n Id du Père : %d \n id de la mère : %d \n Prenom : %s\n Nom : %s\n Jour de Naissance : %s\n Ville de Naissance : %s\n",
  Tab[Id_Person].id, Tab[Id_Person].father_id, Tab[Id_Person].mother_id, Tab[Id_Person].firstname, Tab[Id_Person].lastname, Tab[Id_Person].birthdate, Tab[Id_Person].birthzipcode);
  }
}
person ** brotherhood(struct Person *Tab, int id){
  int nb_freres = 0;
  int i;
  int tab_provisoire[GRAND_TAB];
  // parcours liste
  for(i = 0; i <= MAX_ID; i++){
    //si aucun parent n'est inconnu
    if(Tab[i].father_id != 0 || Tab[i].mother_id != 0){
      // si le père et la mère sont les mêmes, et que la personne n'est pas comparée à elle-même alors ...
      if(Tab[id].father_id == Tab[i].father_id && Tab[id].mother_id == Tab[i].mother_id && id != Tab[i].id){
        //on place les id dans un tableau provisoire en attendant de connaitre le nombre de frères
        tab_provisoire[nb_freres] = Tab[i].id;
        nb_freres++; // compte le nombre de frères
      }
    }
  }
  printf("\nL'individu a %d frère(s)/soeur(s)\n\n", nb_freres);
  // création du tableau de la taille du nombre de frères
  int *tab;
  tab = malloc(nb_freres * sizeof(int));
  for(int j=0; j < nb_freres; j++){
    // on remplace le tableau provisoire par un plus petit
    tab[j] = tab_provisoire[j];
    printf("id du frère/soeur numéro %d : %d\n", j+1, tab[j]);
  }
  return tab;
}

// version court de print_ID seulement id et le nom entier
void print_court(struct Person *Tab, int Id_Person){

  if(Tab[Id_Person].id == 0 || Tab[Id_Person].id == MAX_PERSONNE  || Tab[Id_Person].id < 0){
    printf("Individu inconnu\n\n");
  }else{
    printf("Prenom : %s\nNom : %s\nId : %d\n",
    Tab[Id_Person].firstname, Tab[Id_Person].lastname, Tab[Id_Person].id);
  }
}
