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
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include "initializer.h"
#include "graph_search.h"


using namespace std;

int main(int argc, char** argv)
{
  struct timeval start, end;
  long mtime, seconds, useconds;
  queue<Soko_state> new_states;
  Soko_state solution_state;

  Soko_state init_state;
  make_init_state(argc, argv, init_state);

  cout << "1) breadth first\n2) A*\nEnter search type: ";
  int choise = 0;
  cin >> choise;
  string search_type = "";
  if (choise == 1) {
    search_type = "breadth_first";
  }
  else if (choise == 2) {
    search_type = "a_star";
  }
  else {
    cerr << "[error]  " << choise << ") is not a valid search_type"<< endl;
    return 0;
  }

  gettimeofday(&start, NULL);
  solution_state = graph_search(init_state, search_type);
  gettimeofday(&end, NULL);

  seconds  = end.tv_sec  - start.tv_sec;
  useconds = end.tv_usec - start.tv_usec;

  mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

  cout << "[info] solution is:\n" << solution_state.moves << endl;
  cout << "[info] solved map is:\n" << solution_state.map_state << endl;
  if (seconds > 60)
    cout << "[info] elapsed search time: " << seconds/60 << "min" << endl;
  else if (seconds != 0)
    cout << "[info] elapsed search time: " << seconds << "s" << endl;
  else
    cout << "[info] elapsed search time: " << mtime << "ms" << endl;

  cout << "[info] program done" << endl;
  return 0;
}
