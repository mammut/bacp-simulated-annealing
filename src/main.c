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
  clock_t begin, end;

  struct bacp_instance *instance;
  int min_output  = 0;
  int iter        = 100;
  float t_min     = 0.00001;
  float t_current = 1.0;
  float alpha     = 0.9;
  sprintf(input, "%s", "No Input file specified");

  srand((unsigned)time(NULL));

  /* Parsear entrada usando libreria unistd */
  while ((ch = getopt(argc, argv, "da:T:t:i:f:")) != EOF) {
    switch (ch) {
      case 'f': sprintf(input, "%s", optarg);     break;
      case 'i': sscanf(optarg, "%d", &iter);      break;
      case 'T': sscanf(optarg, "%f", &t_current); break;
      case 't': sscanf(optarg, "%f", &t_min);     break;
      case 'a': sscanf(optarg, "%f", &alpha);     break;
      case 'd': min_output = 1;                   break;
    }
  }

  instance = load_instance(input);

  begin = clock();
  initial_solution(instance); /* 1. Greedy init */
  run(instance, iter, t_current, t_min, alpha); /* 2. Simulated annealing */
  end = clock();

  if (min_output) { /* Minimum output, usado por evaluate.py */
    printf("%d %d %f", max_credits(instance), cost(instance), (double)(end - begin) / CLOCKS_PER_SEC);
  } else {
    for (i = 0; i < instance->n_periods; i++) {
      printf("Periodo %d\n", i + 1);
      found = 0;
      for (j = 0; j < instance->n_courses; j++)
        if (instance->period[j] == i)
          printf("%s%2d", found++ ? " - " : "", j);

      printf(" : %d\n", credits(instance, i));
    }
    printf("\nMaxima carga academica: %d\n", max_credits(instance));
    printf("Tiempo de ejecucion: %f s\n", (double)(end - begin) / CLOCKS_PER_SEC);
  }

  free(instance->period);
  free(instance->credits);
  free(instance->prereq);
  free(instance);

  return 0;
}

