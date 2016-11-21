/*
* Mathias og Chrisians: SOKOBAN SOLVER
* Information:
* X = Wall
* J = box on free
* I = box on goal
* G = Empty Goal
* . = free ground
* M = robot on free
* W = robot on goal
* N = robot on deadlock
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

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

using namespace std;

int main(int argc, char** argv)
{
  queue<Soko_state> new_states;
  Soko_state solution_state;
  Soko_state init_state;

  make_init_state(argc, argv, init_state);

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
    cout << "\n1) heuristic 1 - Box dist to closest goal + dublicate\n2) heuristic 2 - Box dist to each goal\n3) heuristic 3 - Player dist to closest box + H2\n4) heuristic 4 - Player dist to closest box + H1 - dublicate\n5) heuristic 5 - Player dist to closest box + H1\n6) heuristic 6 - Hungarian\nEnter search type: ";
    int choise2 = 0;
    cin >> choise2;
    if (choise2 == 1)
      heuristics_type="h1";
    else if (choise2 == 2)
      heuristics_type="h2";
    else if (choise2 == 3)
      heuristics_type="h3";
    else if (choise2 == 4)
      heuristics_type="h4";
    else if (choise2 == 5)
      heuristics_type="h5";
    else if (choise2 == 6)
      heuristics_type="h6";
    else{
      cerr << "[error]  " << choise << ") is not a valid search_type"<< endl;
      return 0;
    }

  }
  else {
    cerr << "[error]  " << choise << ") is not a valid search_type"<< endl;
    return 0;
  }

  auto start = Time::now();
  solution_state = graph_search(init_state, search_type, heuristics_type);
  auto end = Time::now();

  cout << "[info] solution is:\n" << solution_state.moves << endl;
  cout << "[info] solution is: " << solution_state.moves.size() << " long" << endl;
  cout << "[info] solved map is:\n" << solution_state.map_state << endl;

  fsec fs = end - start;
  ms d = std::chrono::duration_cast<ms>(fs);

  int dmm=0, dms=0, dss=0;
  float milliseconds =  d.count();
  dms = fmod(milliseconds,1000);
  float seconds= milliseconds/1000;
  dss = fmod(seconds,60); // the remainder is seconds to be displayed
  float minutes= seconds/60;  // the total minutes in float
  dmm= fmod(minutes,60);  // the remainder are minutes to be displayed

  cout << "[info] elapsed search time: " << dmm << "min " << dss << "s " << dms << "ms " <<endl;


  cout << "[info] program done" << endl;
  return 0;
}
