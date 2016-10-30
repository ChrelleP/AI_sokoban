#include "a_star.h"
// https://en.wikipedia.org/wiki/A*_search_algorithm
// http://mat.uab.cat/~alseda/MasterOpt/AStar-Algorithm.pdf
Soko_state a_star(Soko_state &state_init)
{
  cout << "[info]   executing A* search!" << endl;
  // Make variable for current state
  Soko_state state_current;
  // Initialize open set
  deque<Soko_state> open_set;
  // Initialize closed set
	vector<Soko_state> closed_set;
	// Put start state in the open set.
	open_set.push_back(state_init);

	while (!open_set.empty())
	{
		// Take top element from open set
    // Also put it on the closed list (we are going to process it)
		state_current = open_set.front();
		open_set.pop_front();

    if ((closed_set.size() % 5000) == 0 && closed_set.size() > 5000-1)
    {
      cout << "[info]   searched "<< closed_set.size() <<" nodes"<<endl;
    }

		// If current state is the goal state, then terminate
		if (is_goal_state(state_current))
		{
      cout << "[info]   "<< closed_set.size() <<" nodes in the closed set" << endl;
			return state_current;
		}

		// State generation
		queue<Soko_state> state_successors;
		state_successors = make_states(state_current);
    // Make bools for the next loop
    bool dublicated_state = false, inserted = false;

		// For each state state successors of state current do
		while (!state_successors.empty())
		{
			dublicated_state = false;
			inserted = false;
			Soko_state current_state_successors = state_successors.front();

      // Is the current state successors in the closed set?
      for (auto itr = closed_set.begin(); itr != closed_set.end(); itr++)
      {
        if (itr->map_state == current_state_successors.map_state)
        {
          dublicated_state = true;
          break;
        }
      }

			// Is the current state successors in the open set?
			for (auto it = open_set.begin(); it != open_set.end(); it++)
			{
				if (it->map_state == current_state_successors.map_state)
				{
					dublicated_state = true;
					break;
				}
			}

			// If not seen
			if (dublicated_state)
			{
        state_successors.pop();
			}
			else
      {
        // Keep a sorted list with regards to cost to goal
        // This makes it easy to just pop of the top element
        for (auto it = open_set.begin(); it != open_set.end(); it++)
        {
          // Insert with respect to cost_to_goal + cost_to_node (f=g+h)
          if ((it->f_score) > (current_state_successors.f_score))
          {
            open_set.insert(it, current_state_successors);
            inserted = true;
            break;
          }
        }
        // If the current_state_successors has the highest score insert at back
        if (!inserted)
          open_set.push_back(current_state_successors);
      }
		}
    closed_set.push_back(state_current);
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
