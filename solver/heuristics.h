#ifndef HURIS
#define HURIS
// Includes
#include "deadlock.h"
#include "dlib/optimization/max_cost_assignment.h"
#include <math.h>

struct point
{
  int row;
  int col;
};

using namespace std;

void get_box_goal_positions(vector< point > &box_vector, vector< point > &goal_vector, vector< point > &boxgoal_vector, Soko_state state_current);
int h1(const Soko_state &cur_state);
int h2(const Soko_state &cur_state);
int h3(const Soko_state &cur_state);

#endif
