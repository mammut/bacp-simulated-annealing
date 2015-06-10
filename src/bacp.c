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
 * @return    ::  struct bacp_instance:  
 *                instancia del problema con todas sus variables
 *                definidas
 */
struct bacp_instance * load_instance(char file_path[])
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

  instance->period = (unsigned short int *)malloc(sizeof(unsigned short int) * instance->n_courses);
  instance->credits = (unsigned short int *)malloc(sizeof(unsigned short int) * instance->n_courses);
  for (i = 0; i < instance->n_courses; i++) {
    fscanf(file, "%hu ", &instance->credits[i]);
  }
  instance->prereq = (struct prereq *)malloc(sizeof(struct prereq) * instance->n_prereq);
  for (i = 0; i < instance->n_prereq; i++) {
    fscanf(file, "%hu %hu", &instance->prereq[i].a, &instance->prereq[i].b);
  }

  fclose(file);

  return instance;
}

/**           
 * Entrega un arreglo con los prerequisitos del curso a.
 *
 * @i      :: instancia del problema
 * @a      :: indice del curso al cual se le buscan los prerequisitos
 * @return :: struct prereq_list *: arreglo dinamico de prerequisitos. liberar!
 */
struct prereq_list *prereqs_of(struct bacp_instance *instance, unsigned short int a)
{
  struct prereq_list *prereqs;
  unsigned short int i;

  prereqs = (struct prereq_list *)malloc(sizeof(struct prereq_list));
  prereqs->n = 0;
  prereqs->items = NULL;
  for (i = 0; i < instance->n_prereq; i++) {
    if (instance->prereq[i].a == a) {                                            
      prereqs->items = (unsigned short int *)realloc(prereqs->items, sizeof(unsigned short int) * (prereqs->n+1));
      prereqs->items[prereqs->n] = instance->prereq[i].b;
      prereqs->n++;
    }
  }
  return prereqs;
}

/**
 * Retorna si a es prerequisito de b
 *
 * instance :: Instancia del problema BACP
 * a        :: Primer curso
 * b        :: Segundo curso
 */
int is_prereq_of(struct bacp_instance *instance, unsigned short int a, unsigned short int b) 
{
  unsigned short int i;

  for (i = 0; i < instance->n_prereq; i++) {
    if (instance->prereq[i].a == b && instance->prereq[i].b == a){
      return 1;
    }
  }
  return 0;
}

/**
 * Funcion de carga academica del periodo j
 *
 * @instance :: instancia del BACP
 * @j        :: periodo j sobre el que se calcula la carga academica
 */
int credits(struct bacp_instance *instance, unsigned short int j)
{
  int total_credits = 0;
  int i;

  for (i = 0; i < instance->n_courses; i++) {
    if (instance->period[i] == j) {
      total_credits += instance->credits[i];
    }
  }
  return total_credits;
}

/**
 * Calcula el maximo de los costos dada una instancia de BACP
 *
 * @instance :: Instancia del BACP
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

int cost(struct bacp_instance *instance)
{                                
  /* Calcular penalizaciones por incumplimiento de requicitos */
  int i;
  int total_penalty = 0;

  for (i = 0; i < instance->n_prereq; i++) {
    
    /*printf("a(%2hu): %2hu, b(%2hu): %2hu", 
        instance->prereq[i].a,
        instance->period[instance->prereq[i].a] ,
        instance->prereq[i].b,
        instance->period[instance->prereq[i].b]);
        */
    if (instance->period[instance->prereq[i].a] <= instance->period[instance->prereq[i].b]){
      //total_penalty += pow(instance->credits[instance->prereq[i].a], 2);
      total_penalty += 1;
      /*printf(" *");*/
    }
    //printf("\n");
  }


  return max_credits(instance) + total_penalty;
}


