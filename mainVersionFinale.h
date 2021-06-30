typedef struct Person{
  int id;
  int father_id;
  int mother_id;
  char lastname[20];
  char firstname[20];
  char birthdate[20];
  char birthzipcode[20];
  struct Person *p_father;
  struct Person *p_mother;

}person;

//prototypess
void link_populations(struct Person *, int);
void ancetre(struct Person *, int *, int);
void print_ID(struct Person *, int);
person ** brotherhood(struct Person *, int);
void print_court(struct Person *, int );
