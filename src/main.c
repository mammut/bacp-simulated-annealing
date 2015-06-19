#include "includes/main.h"
#include "includes/bacp.h"
#include "includes/simulated-annealing.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  char ch;
  char input[MAX_INPUT_BUFFER];
  int i, j;
  int found; /* Flag para imprimir 1 - 2 - 3 - 4 saltandose el primer `-` */
  int min_output = 0;
  clock_t begin, end;

  struct bacp_instance *instance;
  int iter        = 400;
  float t_min     = 0.00001;
  float t_current = 1.0;
  float alpha     = 0.9;

  srand((unsigned)time(NULL));

  sprintf(input, "%s", "No Input file specified");

  /* Parsear entrada usando libreria unistd */
  while ((ch = getopt(argc, argv, "da:T:t:i:f:")) != EOF) {
    switch (ch) {
      case 'f':
        sprintf(input, "%s", optarg);
        break;
      case 'i':
        sscanf(optarg, "%d", &iter);
        break;
      case 'T':
        sscanf(optarg, "%f", &t_current);
        break;
      case 't':
        sscanf(optarg, "%f", &t_min);
        break;
      case 'a':
        sscanf(optarg, "%f", &alpha);
        break;
       case 'd':
        min_output = 1;
        break;
    }
  }
  //printf("Iter: %d\nT: %f\nt_min: %f\nalpha: %f\n\n", iter, t_current, t_min, alpha);

  instance = load_instance(input);
  initial_solution(instance);
  for (i = 0; i < instance->n_periods; ++i) {
    printf("%d: %d %d\n", i, credits(instance, i), courses_per_period(instance, i));
  }
  printf("%d\n", cost(instance));
  return 0;

  begin = clock();
  run(instance, iter, t_current, t_min, alpha);
  end = clock();

  if (min_output) {
    /* Minimum output, usado por evaluate.py */
    printf("%d %d %f", max_credits(instance), cost(instance), (double)(end - begin) / CLOCKS_PER_SEC);
  } else {
    for (i = 0; i < instance->n_periods; i++) {
      printf("Periodo %d\n", i + 1);
      found = 0;
      for (j = 0; j < instance->n_courses; j++) {
        if (instance->period[j] == i) {
          if ( ! found) {
            printf("%2d", j);
            found = 1;
          } else {
            printf(" - %2d", j);
          }
        }
      }
      printf(" : %d\n", credits(instance, i));
    }
    printf("\nMaxima carga academica: %d\n", max_credits(instance));
    printf("Costo final: %d\n", cost(instance));
    printf("Tiempo de ejecucion %f s\n", (double)(end - begin) / CLOCKS_PER_SEC);
  }

  free(instance->period);
  free(instance->credits);
  free(instance->prereq);
  free(instance);

  return 0;
}

