#include "includes/bacp.h"
#include "includes/simulated-annealing.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

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
    instance->period[j] = i; /* Heuristica para Greedy */
    // instance->period[j] = rand() % instance->n_periods;  /* Iniciacio random del problema, para SA original */
    if ( (j + 1)%n == 0) {
      i++;

    }
  }
}



/**
 * Funcion de costo, incluye penalizacion por prerequisitos erroneos
 * y por cantidad de cursos maximos y minimos por periodo.
 *
 * @instance :: instancia del BACP
 */
int cost(struct bacp_instance *instance)
{
  unsigned int i;
  unsigned int total_penalty = 0;
  unsigned int cpp;

  /* Penalizacion por incumplimiento de prerequisito */
  for (i = 0; i < instance->n_prereq; i++) {
    /* periodo de a <= periodo de b */
    if (instance->period[instance->prereq[i].a] <= instance->period[instance->prereq[i].b]) {
      total_penalty += PENALTY_PREREQ;
    }
  }

  for (i = 0; i < instance->n_periods; i++) {

    /* Penalizacion por cantidad de cursos por periodo */
    cpp = courses_per_period(instance, i);
    if ( cpp < instance->min_courses || instance->max_courses < cpp )
      total_penalty += PENALTY_CREDITS;

    /* Penalizacion por cantidad de creditos por periodo */
    cpp = credits(instance, i);
    if ( cpp < instance->min_load || instance->max_load < cpp )
      total_penalty += PENALTY_COURSES;

  }

  return max_credits(instance) + total_penalty;
}

/**
 * Genera una nueva solucion vecina, cambiando el periodo de un curso
 * al azar, a un periodo al azar
 *
 * @instance :: Instancia del BACP
 *
 * @return   :: nueva solucion (arreglo de unsigned short int)
 */
unsigned short int *neighbour(struct bacp_instance *instance)
{
  unsigned short int *new_solution;
  unsigned short int new_period;
  unsigned short int course;

  /* 0. Duplicar solucion actual */
  new_solution = copy_solution(instance->period, instance->n_courses);

  /* 1. Tomar un curso al azar */
  course = rand()%instance->n_courses;

  /* 2. Asignarlo a un periodo al azar,
   *    si es el mismo que el actual
   *    sumarle 1 % n_periodos */
  new_period = rand()%instance->n_periods;
  if (new_period == instance->period[course])
    new_period = (new_period + 1)%instance->n_periods;

  new_solution[course] = new_period;

  return new_solution;
}

/**
 * Loop principal del algoritmo Simulated Annealing.
 *
 * @instance  :: Instancia del BACP
 * @iter      :: Numero maximo de iteraciones para una temperatura fija t_current
 * @t_current :: Temperatura inicial
 * @t_min     :: Temperatura minima (eps)
 * @alpha     :: Velocidad de decaimiento de la temperatura
 */
void run(struct bacp_instance *instance, int iter, float t_current, float t_min, float alpha)
{
  unsigned short int *s_best   = copy_solution(instance->period, instance->n_courses);
  unsigned short int *s_c      = instance->period;
  unsigned short int old_cost  = cost(instance);
  unsigned short int best_cost = old_cost;
  unsigned short int new_cost;
  unsigned short int i;

  instance->period = NULL;
  while (t_current > t_min) {
    i = 0;
    while (++i <= iter) {
      if (instance->period) free(instance->period);

      instance->period = s_c;
      instance->period = neighbour(instance);
      new_cost         = cost(instance);

      if (new_cost < old_cost) {
        free(s_c);
        s_c              = instance->period;
        old_cost         = new_cost;
        instance->period = NULL;
      }else if (exp(-abs(new_cost - old_cost)/t_current) > aceptar()) {
        free(s_c);
        s_c              = instance->period;
        old_cost         = new_cost;
        instance->period = NULL;
      }

      if ( best_cost > new_cost ) {
        if (s_best) free(s_best);
        s_best    = copy_solution(s_c, instance->n_courses);
        best_cost = new_cost;
      }
    }
    t_current = t_current * alpha;
  }

  if (instance->period) free(instance->period);
  if (s_c) free(s_c);

  instance->period = s_best;
}

/**
 * Probabilidad de aceptar una respuesta peor
 *
 * @return :: valor aleatoreo entre 0.0 y 1.0
 */
float aceptar()
{
  return ((double)rand()/(double)RAND_MAX);
}

/**
 * Crea una copia de una solucion de tamaño size
 *
 * @old     :: Solucion a copiar (arreglo dinamico de enteros)
 * @size    :: Tamaño del arreglo dinamico
 *
 * @return  :: Arreglo dinamico con la copia del original
 */
unsigned short int *copy_solution(unsigned short int *old, unsigned short int size)
{
  int i;
  unsigned short int *copy = (unsigned short int *)malloc(sizeof(unsigned short int) * size);

  for (i = 0; i < size; i++)
    copy[i] = old[i];

  return copy;
}
