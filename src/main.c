#include "includes/main.h"
#include "includes/bacp.h"
#include "includes/simulated-annealing.h"
#include <stdlib.h>
#include <unistd.h>
#include <argp.h>
#include <time.h>
#include <stdio.h>

/**
 * Parseo de argumentos desde la linea de comandos usando la libreria
 * ARGP. No es estandar de C, por lo que puede que en Mac no compile
 * correctamente
 */
const char *argp_program_version     = "bacp 1.0.1";
const char *argp_program_bug_address = "<juan.escalona@alumnos.inf.utfsm.cl>";
static char doc[] = "BACP Solver using Greedy heuristic for the initial solution and Simulated Annealing for local search";
static char args_doc[] = "INPUT_FILE";
static struct argp_option options[] = {
  {"iter",       'i', "100",     0,  "Number of iterations for each temperature of the SA algorithm" },
  {"t-min",      't', "0.00001", 0,  "Minimal stopping temperature of SA algorithm" },
  {"t-init",     'T', "1.0",     0,  "Initial temperature of SA algorithm" },
  {"alpha",      'a', "0.9",     0,  "Alpha" },
  {"red-output", 'r', 0,         0,  "Reduced output" },
  { 0 }
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = (struct arguments *)state->input;

  switch (key) {
    case 'i': sscanf(arg, "%d", &arguments->iter); break;
    case 't': sscanf(arg, "%f", &arguments->t_min); break;
    case 'T': sscanf(arg, "%f", &arguments->t_current); break;
    case 'a': sscanf(arg, "%f", &arguments->alpha); break;
    case 'r': arguments->min_output = 1; break;

    case ARGP_KEY_ARG:
      if (state->arg_num >= 1)
        argp_usage(state);
      arguments->args[state->arg_num] = arg;
      break;

    case ARGP_KEY_END:
      if (state->arg_num < 1)
        argp_usage(state);
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };



/**
 * Main BACP Solver, Greedy + Simulated annealing
 */
int main(int argc, char *argv[])
{
  int i, j;
  int found; /* Flag para imprimir 1 - 2 - 3 - 4 saltandose el primer `-` */
  clock_t begin, end;
  struct bacp_instance *instance;
  struct arguments arguments;

  /* Valores de argumentos por defecto y parseo de parametros. */
  arguments.iter       = 100;
  arguments.min_output = 0;
  arguments.t_min      = 0.00001;
  arguments.t_current  = 1.0;
  arguments.alpha      = 0.9;
  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  srand((unsigned)time(NULL));
  instance = load_instance(arguments.args[0]);

  begin = clock();
  initial_solution(instance); /* 1. Greedy init */
  run(instance, arguments.iter, arguments.t_current, arguments.t_min, arguments.alpha); /* 2. Simulated annealing :: Comentar esta linea para ver asignacion original del greedy */
  end = clock();

  if (arguments.min_output) { /* Minimum output, usado por evaluate.py */
    printf("%d %d %f %d", max_credits(instance), cost(instance), (double)(end - begin) / CLOCKS_PER_SEC, optimum(instance));
  } else {
    for (i = 0; i < instance->n_periods; i++, found = 0) {
      printf("Periodo %d\n", i + 1);

      for (j = 0; j < instance->n_courses; j++)
        if (instance->period[j] == i)
          printf("%s%2d", found++ ? " - " : "", j);

      printf(" : %d\n", credits(instance, i));
    }
    printf("\nMaxima carga academica: %d\n", max_credits(instance));
    printf("\nCosto: %d\n", cost(instance));
    printf("Tiempo de ejecucion: %f s\n", (double)(end - begin) / CLOCKS_PER_SEC);
  }

  free(instance->period);
  free(instance->credits);
  free(instance->prereq);
  free(instance);

  return 0;
}
