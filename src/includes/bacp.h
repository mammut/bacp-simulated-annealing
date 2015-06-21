#ifndef _BACP_H_INCLUDED_
#define _BACP_H_INCLUDED_

struct prereq {
  unsigned short int a;
  unsigned short int b;
};

struct bacp_instance {
  unsigned short int n_courses;
  unsigned short int n_periods;
  unsigned short int min_load;
  unsigned short int max_load;
  unsigned short int min_courses;
  unsigned short int max_courses;
  unsigned short int n_prereq;
  unsigned short int *credits;
  struct prereq *prereq; /* arreglo de prerequicitos */
  unsigned short int *period; /* Variable x: Periodo del ramo i*/
};

struct bacp_instance * load_instance(char[]);
unsigned int credits(struct bacp_instance *, unsigned short int);
unsigned int max_credits(struct bacp_instance *);
unsigned int courses_per_period(struct bacp_instance *, unsigned short int);
int is_prereq_of(struct bacp_instance *, unsigned short int, unsigned short int);

#endif
