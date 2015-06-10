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
  int row;
  
  srand(time(NULL));
  sprintf(input, "%s", "None");

  while ((ch = getopt(argc, argv, "f:")) != EOF) {
    switch (ch) {
      case 'f':
        sprintf(input, "%s", optarg);
        break;
    }
  }

  struct bacp_instance *i = load_instance(input);
  struct prereq_list *prereqs = prereqs_of(i, 7);
  initial_solution(i);
  for(row = 0; row < i->n_periods; row++) {
    printf("%d: %d\n", row, credits(i, row));
  }
  printf("Max: %d\n", max_credits(i));
  printf("Cost: %d\n", cost(i));
  free(prereqs->items);
  free(prereqs);
  free(i->period);
  free(i->credits);
  free(i->prereq);
  free(i);
  return 0;
}

