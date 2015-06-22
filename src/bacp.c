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
  unsigned short int i;
  FILE *file;
  struct bacp_instance *instance = (struct bacp_instance *)malloc(sizeof(struct bacp_instance));

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
  for (i = 0; i < instance->n_courses; i++){
    instance->period[i] = -1;
    fscanf(file, "%hu ", &instance->credits[i]);
  }

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
 *
 * @return   :: numero total de creditos
 */
unsigned int credits(struct bacp_instance *instance, unsigned short int j)
{
  unsigned short int i;
  unsigned int total_credits = 0;

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
unsigned int max_credits(struct bacp_instance *instance)
{
  unsigned short int j;
  unsigned int is_bigger;
  unsigned int max = credits(instance, 0);

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
 * @i        :: periodo i
 *
 * @return   :: total de cursos
 */
unsigned int courses_per_period(struct bacp_instance *instance, unsigned short int i)
{
  unsigned short int j;
  unsigned int total = 0;

  for (j = 0; j < instance->n_courses; j++)
    if (instance->period[j] == i) total++;

  return total;
}

/**
 * Retorna si a es prerequisito de b o vicecersa
 *
 * instance :: Instancia del problema BACP
 * a        :: Primer curso
 * b        :: Segundo curso
 */
int is_prereq_of(struct bacp_instance *instance, unsigned short int a, unsigned short int b)
{
  unsigned short int i;

  for (i = 0; i < instance->n_prereq; i++) {
    if ((instance->prereq[i].a == b && instance->prereq[i].b == a) ||
        (instance->prereq[i].a == a && instance->prereq[i].b == b)) {
      return 1;
    }
  }
  return 0;
}

/**
 * Calcula el optimo de creditos de una instancia del BACP dada
 * la cantidad de creditos totales y el numero de periodos
 *
 * @instance :: Instancia del BACP
 *
 * @return   :: optimo
 */
unsigned short int optimum(struct bacp_instance *instance)
{
  unsigned short int j;
  unsigned short int total = 0;

  for(j = 0; j < instance->n_courses; j++)
    total += instance->credits[j];

  return ceil(1.0 * total/instance->n_periods + 0.0001);
}
