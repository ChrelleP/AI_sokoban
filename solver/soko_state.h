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
  int player_row;
  int player_col;
  int height;
  int width;
  int cost_to_node;
  int cost_to_goal;
  int f_score;
};

#endif
