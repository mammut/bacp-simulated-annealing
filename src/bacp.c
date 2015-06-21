#include "includes/bacp.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/**
 * Lee los datos de una instancia en especifico a partir de un archivo
 * de entrada.
 *
 * @file_path ::  ruta al archivo de entrada que utiliza el formatio entregado
 *                en el enunciado del problema.
 *
 * @return    ::  instancia del problema con todas sus variables
 *                definidas
 */
struct bacp_instance *load_instance(char file_path[])
{
  FILE *file;
  struct bacp_instance *instance = (struct bacp_instance *)malloc(sizeof(struct bacp_instance));
  unsigned short int i;

  if ((file = fopen(file_path, "r")) == 0) {
    fprintf(stderr, "No se pudo abrir el archivo %s. Por favor revise su existencia y permisos.", file_path);
    exit(EXIT_FAILURE);
  }

  fscanf(file, "%hu %hu %hu %hu %hu %hu %hu",
           &instance->n_courses,
           &instance->n_periods,
           &instance->min_load,
           &instance->max_load,
           &instance->min_courses,
           &instance->max_courses,
           &instance->n_prereq
        );

  instance->period  = (unsigned short int *)malloc(sizeof(unsigned short int) * instance->n_courses);
  instance->credits = (unsigned short int *)malloc(sizeof(unsigned short int) * instance->n_courses);
  for (i = 0; i < instance->n_courses; i++)
    fscanf(file, "%hu ", &instance->credits[i]);

  instance->prereq = (struct prereq *)malloc(sizeof(struct prereq) * instance->n_prereq);
  for (i = 0; i < instance->n_prereq; i++)
    fscanf(file, "%hu %hu", &instance->prereq[i].a, &instance->prereq[i].b);

  fclose(file);

  return instance;
}

/**
 * Calcula la carga academica del periodo j
 *
 * @instance :: instancia del BACP
 * @j        :: periodo j sobre el que se calcula la carga academica
 */
int credits(struct bacp_instance *instance, unsigned short int j)
{
  int total_credits = 0;
  int i;

  for (i = 0; i < instance->n_courses; i++)
    if (instance->period[i] == j)
      total_credits += instance->credits[i];

  return total_credits;
}

/**
 * Calcula la carga maxima de todos los periodos, dada una instancia de BACP
 *
 * @instance :: Instancia del BACP
 *
 * @return   :: carga maxima de creditos
 */
int max_credits(struct bacp_instance *instance)
{
  int max = credits(instance, 0);
  int is_bigger;
  int j;

  for (j = 1; j < instance->n_courses; j++) {
    is_bigger = credits(instance, j);
    if (is_bigger > max) max = is_bigger;
  }

  return max;
}

/**
 * Total de cursos en el periodo j
 *
 * @instance :: instancia del BACP
 * @j        :: periodo j
 *
 * @return   :: total de cursos
 */
int courses_per_period(struct bacp_instance *instance, unsigned short int j)
{
  int total = 0;
  int i;

  for (i = 0; i < instance->n_courses; i++)
    if (instance->period[i] == j) total++;

  return total;
}

int has_collitions(struct bacp_instance *instance, unsigned short int i)
{
  int j;
  int k;

  j = 1;
  k = 0;

  return 0;
}
