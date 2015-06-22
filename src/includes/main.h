#ifndef _MAIN_H_INCLUDED_
#define _MAIN_H_INCLUDED_

struct arguments {
  char *args[1];                /* arg1 & arg2 */
  int min_output;
  int iter;
  float t_min;
  float t_current;
  float alpha;
};

#endif
