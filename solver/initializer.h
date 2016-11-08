#ifndef INITILIZER
#define INITILIZER
// Includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Declerations
struct Soko_state
{
  string map_state;
  void set( int row, int col, char value ){ map_state[(row*(height+1))+col] = value; }
  char get( int row, int col ){ return map_state[(row*(height+1))+col]; }
  string moves;
  int player_row;
  int player_col;
  int height;
  int width;
  int cost_to_node;
  int cost_to_goal;
  int f_score;
};

#include"heuristics.h"

void make_init_state(int argc, char** argv, Soko_state &init_state);
void deadlock_tester_static(Soko_state &init_state);

#endif
