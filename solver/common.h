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

// Declerations
struct Soko_state
{
  string moves;
  string map_state;
  int height;
  int width;
};

bool is_goal_state(Soko_state &state_current);
void make_init_state(int argc, char** argv, Soko_state &init_state);


#endif
