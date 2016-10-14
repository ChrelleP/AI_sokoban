/*
* Mathias og Chrisians: SOKOBAN SOLVER
*
* Information:
* X = Wall            (#)
* J = box on free     ($)
* I = box on goal     (*)
* G = Empty Goal      (.)
* . = free ground     ( )
* M = robot on free   (@)
* W = robot on goal   (+)
*
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

struct Soko_state
{
  string moves;
  string map_state;
};

#include "breadth_first.h"

bool is_goal_state(Soko_state &state_current)
{
  bool is_goal = false;
  size_t found_goal = state_current.map_state.find("G");
  size_t found_robot_on_goal = state_current.map_state.find("W");
  size_t found_free_box = state_current.map_state.find("J");

  if(found_goal == string::npos){
    if(found_robot_on_goal == string::npos){
      if(found_free_box == string::npos){
        is_goal = true;
      }
      else cout << "free box detected!" << endl;
    }
    else cout << "robot on goal detected!" << endl;
  }
  else cout << "free goal detected!" << endl;

  return is_goal;
}

queue<Soko_state> make_states(const Soko_state &cur_state)
{
  queue<Soko_state> states;
  return states;
}

int main(int argc, char** argv)
{
  ifstream sokoban_map_file;

  // Check is input is valid
  if (argc != 2)
  {
    cerr << "[error]  use like this: " << argv[0] << " <sokoban_map>.txt"<< endl;
    return 0;
  }
  else
  {
    sokoban_map_file.open (argv[1]);
    if (!sokoban_map_file)
    {
      cerr << "[error]  can't open " << argv[1] << endl;
      return 0;
    }
  }

  // Extract map metadata
  string line;
	getline(sokoban_map_file, line, ' ');
	int map_width = atoi(line.c_str()); // atoi -> string2int
  getline(sokoban_map_file, line, ' ');
  int map_hight = atoi(line.c_str());
  getline(sokoban_map_file, line, '\n');
  int num_of_goals = atoi(line.c_str());

  // Extract map
  string sokoban_map = "";
  while (getline(sokoban_map_file, line))
  {
    sokoban_map.append(line) += "\n";
  }

  cout << "\nSokoban map loaded:\n" << endl;
  cout << sokoban_map << endl;
  cout << "Map dimensions:  "<< map_hight << " x " << map_width << endl;
  cout << "Number of goals: "<< num_of_goals << endl << endl;

  Soko_state init_state;
  init_state.moves = "";
  init_state.map_state = sokoban_map;
  // Consider adding number of moves...

  breadth_first(init_state);

  is_goal_state(init_state);

  cout << "[info]   program done" << endl;

  return 0;
}
