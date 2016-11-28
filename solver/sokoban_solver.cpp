/*
* Mathias og Chrisians: SOKOBAN SOLVER
*/

#include <chrono>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include "initializer.h"
#include "graph_search.h"

// Set of timer - For timing the search
typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

using namespace std;

int main(int argc, char** argv)
{
  // Make new sokoban states
  queue<Soko_state> new_states;
  Soko_state solution_state;
  Soko_state init_state;

  // Setup the initial state
  make_init_state(argc, argv, init_state);

  // Choose search type
  cout << "1) breadth first\n2) A*\nEnter search type: ";
  int choise = 0;
  cin >> choise;
  string search_type = "";
  string heuristics_type = "";

  if (choise == 1) {
    search_type = "breadth_first";
  }
  else if (choise == 2) {
    search_type = "a_star";
    cout << "\n1) heuristic 1 - Box dist to closest goal\n2) heuristic 2 - H1 + player dist to closest box\n3) heuristic 3 - H2 + hungarian\nEnter search type: ";
    int choise2 = 0;
    cin >> choise2;
    if (choise2 == 1)
      heuristics_type="h1";
    else if (choise2 == 2)
      heuristics_type="h2";
    else if (choise2 == 3)
      heuristics_type="h3";
    else {
      cerr << "[error]  " << choise << ") is not a valid search_type"<< endl;
      return 0;
    }

  }
  else {
    cerr << "[error]  " << choise << ") is not a valid search_type"<< endl;
    return 0;
  }

  // Start search function and time it
  auto start = Time::now();
  solution_state = graph_search(init_state, search_type, heuristics_type);
  auto end = Time::now();

  // User feedback - Solution - Execution Time - ect.
  cout << "[info] solution is:\n" << solution_state.moves << endl;
  cout << "[info] solution is: " << solution_state.moves.size() << " long" << endl;
  cout << "[info] solved map is:\n" << solution_state.map_state << endl;
  fsec fs = end - start;
  ms d = std::chrono::duration_cast<ms>(fs);
  int dmm=0, dms=0, dss=0;
  float milliseconds =  d.count();
  dms = fmod(milliseconds,1000);
  float seconds= milliseconds/1000;
  dss = fmod(seconds,60);
  float minutes= seconds/60;
  dmm= fmod(minutes,60);
  cout << "[info] elapsed search time: " << dmm << "min " << dss << "s " << dms << "ms " <<endl;
  cout << "[info] program done" << endl;
  return 0;
}
