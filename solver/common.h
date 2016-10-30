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
  int cost_to_node;
  int cost_to_goal;
  int f_score;
  size_t hash_key;
};

bool is_goal_state(Soko_state &state_current);
void make_init_state(int argc, char** argv, Soko_state &init_state);
int h1(const Soko_state &cur_state);

#endif
