#ifndef SOKO_STATE
#define SOKO_STATE
// Includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "deadlock.h"

using namespace std;

// Declerations
struct Soko_state
{
  string map_state;
  void set( int row, int col, char value ){ map_state[(row*(width+1))+col] = value; }
  char get( int row, int col ){ return map_state[(row*(width+1))+col]; }
  string moves;
  int num_of_goals;
  int player_row;
  int player_col;
  int height;
  int width;
  int cost_to_node;
  int cost_to_goal;
  int f_score;
};

struct compare
{
  bool operator()(const Soko_state& state1, const Soko_state& state2)
  {
      return state1.f_score > state2.f_score;
  }
};

#endif
