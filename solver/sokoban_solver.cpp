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
#include "common.h"
#include "breadth_first.h"

using namespace std;

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
  init_state.height = map_hight;
  init_state.width = map_width;
  // Consider adding number of moves...

  breadth_first(init_state);
  make_states(init_state);

  is_goal_state(init_state);

  cout << "[info]   program done" << endl;

  return 0;
}
