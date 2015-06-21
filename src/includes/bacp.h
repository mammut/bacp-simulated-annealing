#ifndef _BACP_INCLUDED_
#define _BACP_INCLUDED_

struct prereq_list {
  unsigned short int n;
  unsigned short int *items;
};

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
  struct prereq *prereq;

  unsigned short int *period; /* Periodo del ramo i*/
};

struct bacp_instance * load_instance(char[]);
struct prereq_list *prereqs_of(struct bacp_instance *, unsigned short int);
int is_prereq_of(struct bacp_instance *, unsigned short int, unsigned short int);
int credits(struct bacp_instance *, unsigned short int);
int max_credits(struct bacp_instance *);
int cost(struct bacp_instance *);
int courses_per_period(struct bacp_instance *, unsigned short int);
int has_collitions(struct bacp_instance *instance, unsigned short int);

#endif
