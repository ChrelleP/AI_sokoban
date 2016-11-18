#ifndef HURIS
#define HURIS
// Includes
#include "initializer.h"
#include <math.h>

struct point
{
  int row;
  int col;
};

using namespace std;

void get_box_goal_positions(vector< point > &box_vector, vector< point > &goal_vector, vector< point > &boxgoal_vector, string map_state);
int h1(const Soko_state &cur_state);
int h2(const Soko_state &cur_state);
int h3(const Soko_state &cur_state);

#endif
