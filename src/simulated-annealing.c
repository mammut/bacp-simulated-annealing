#include "includes/bacp.h"
#include "includes/simulated-annealing.h"
#include <stdlib.h>
#include <math.h>

/**
 * Genera una solucion inicial, asignando parejamente los cursos
 * a periodos. Todos mus cercanos a num_cursos / num_periodos excepto
 * el ultimo al que se le asigna lo que sobre
 *
 * @bacp_instance :: instancia del problema bacp
 */
void initial_solution(struct bacp_instance *instance) 
{
  int n = ceil(1.0 * instance->n_courses / instance->n_periods );
  int i, j;

  for (i = 0, j = 0; j < instance->n_courses; j++) {
    //instance->period[j] = i; /* Usar este metodo para dist. uniforme */
    instance->period[j] = rand() % instance->n_periods;
    if ((j+1)%n == 0) i++;
  }
}

