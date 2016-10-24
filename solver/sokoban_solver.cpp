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
#include "state_generator.h"
#include "breadth_first.h"

using namespace std;

int main(int argc, char** argv)
{
  queue<Soko_state> new_states;
  Soko_state solution_state;

  // Check is input is valid
  if (argc != 2)
  {
    cerr << "[error]  use like this: " << argv[0] << " <sokoban_map>.txt"<< endl;
    return 0;
  }
  else
  {
    Soko_state init_state;
    make_init_state(argc, argv, init_state);
    solution_state = breadth_first(init_state);

    cout << solution_state.moves << endl;
    cout << "\n" << solution_state.map_state << endl;
    /*
    new_states = make_states(init_state);

    cout << endl;
    while (!new_states.empty())
    {
       cout << new_states.front().map_state << endl;
       new_states.pop();
    }
    is_goal_state(init_state);
    */
  }

  cout << "[info]   program done" << endl;
  return 0;
}
