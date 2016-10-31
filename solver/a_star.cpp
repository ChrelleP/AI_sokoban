#include "a_star.h"
// https://en.wikipedia.org/wiki/A*_search_algorithm
// http://mat.uab.cat/~alseda/MasterOpt/AStar-Algorithm.pdf
Soko_state a_star(Soko_state &state_init)
{
  cout << "[info]   executing A* search!" << endl;
  // Make variable for current state
  Soko_state state_current;
  // Initialize open and closed set
  deque<Soko_state> open_set;
  Mymap hash_map_closed;
  Mymap hash_map_open;

	// Put start state in the open set.
	open_set.push_back(state_init);
  hash_map_open.insert(Mymap::value_type(state_init.map_state, state_init));

	while (!open_set.empty())
	{
    // maintain open set
		state_current = open_set.front();
		open_set.pop_front();
    hash_map_open.erase(state_current.map_state);
    // maintain closed set
    hash_map_closed.insert(Mymap::value_type(state_current.map_state, state_current));

    if ((hash_map_closed.size() % 5000) == 0)
      cout << "Searched "<< hash_map_closed.size() <<" nodes"<<endl;

		// If current state is the goal state, then terminate
		if (is_goal_state(state_current))
			return state_current;

		// State generation
		queue<Soko_state> state_successors = make_states(state_current);

    // Make bools for the next loop
    bool dublicated_state = false, inserted = false;

		// For each state state successors of state current do
		while (!state_successors.empty())
		{
			dublicated_state = false;
			inserted = false;
			Soko_state state_current_successors = state_successors.front();

      // Is the current state successors in the open set?
      if (hash_map_open.count(state_current_successors.map_state))
        dublicated_state = true;

      // Is the current state successors in the closed set?
      if (hash_map_closed.count(state_current_successors.map_state))
        dublicated_state = true;

			// If seen
			if (dublicated_state)
        state_successors.pop();
			else
      {
        // Keep a sorted list with regards to cost to goal
        // This makes it easy to just pop of the top element
        for (auto it = open_set.begin(); it != open_set.end(); it++)
        {
          // Insert with respect to cost_to_goal + cost_to_node (f=g+h)
          if ((it->f_score) > (state_current_successors.f_score))
          {
            open_set.insert(it, state_current_successors);
            hash_map_open.insert(Mymap::value_type(state_current_successors.map_state, state_current_successors));
            inserted = true;
            break;
          }
        }
        // If the state_current_successors has the highest score insert at back
        if (!inserted)
          open_set.push_back(state_current_successors);
        state_successors.pop();
      }
		}
	}
  state_current.map_state = "SOLUTION NOT FOUND!\n";
  return state_current;
}


// With cost_to_goal
// bBBRluurrruulBrbbbblluluurRurBBBuullluRblbblluuuRRbrrrbbLLLLblUUbrruurrruulBrbbbllluuuRblbbrrruuLLulBBurrrbbllLLblUbrRuuurrruulBrbLLulBBurrrbbllLblluRRRluurrrbbLbLruruulllbbR
// With f_score
// bBBRluurrruulBrbLrbbblluluuRRurBBBuullluRblbblluuuRRbrrruulBrbLrbbLLLLblUrruuRluRblbbrrruuLLrruulBllBurrrbbblllllUbrrrrruuLullbBuurrbLulBrrrbbllLLblUbrRurrruulllBurrrbbllLblluRRRluurrrbbLbLruruulllbbR
// Stolen (same result)
// dddrluurrruuldrddddlluluurrurddduulllurldddlluuurrdrrrddlllldluudrruurrruuldrdddllluuurdlddrrruullulddurrrddlllldlurdruuurrruuldrdllulddurrrddllldllurrrluurrrddldlruruulllddr


// Stolen h2
//
