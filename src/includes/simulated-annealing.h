#ifndef _SIMULATED_ANNEALING_INCLUDED_
#define _SIMULATED_ANNEALING_INCLUDED_

#define PENALTY_PREREQ 200
#define PENALTY_CREDITS 20
#define PENALTY_COURSES 20

void initial_solution(struct bacp_instance *);
unsigned short int *neighbour(struct bacp_instance *);
void run(struct bacp_instance *, int iter, float, float, float);
float aceptar();
unsigned short int *copy_solution(unsigned short int *, unsigned short int);

#endif
