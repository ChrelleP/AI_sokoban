#ifndef COMMON
#define COMMON
// Includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <sstream>

using namespace std;

struct Soko_state
{
  string moves;
  string map_state;
  int height;
  int width;
};

// Decleration
bool is_goal_state(Soko_state &state_current);
queue<Soko_state> make_states(const Soko_state &cur_state);


#endif
