#include "informed_search.h"
// https://msdn.microsoft.com/en-us/library/bb982522.aspx

Soko_state informed_search(Soko_state &state_init, string search_type)
{
  cout << "\n[info] executing " << search_type << " search!" << endl;

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
    // Maintain open set
    state_current = open_set.front();
    open_set.pop_front();
    hash_map_open.erase(state_current.map_state);

    // maintain closed set
    hash_map_closed.insert(Mymap::value_type(state_current.map_state, state_current));

    // Make bools for the next loop
    bool dublicated_state = false;

    if ((hash_map_closed.size() % 10000) == 0)
      cout << "[info] searched "<< hash_map_closed.size() <<" nodes"<<endl;

    // If current state is the goal state, then terminate
    if (is_goal_state(state_current))
      return state_current;

    // State generation
    queue<Soko_state> state_successors = make_states(state_current);

    // For each state state successors of state current do
    while (!state_successors.empty())
    {
      dublicated_state = false;
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
        if (search_type == "breadth_first") {
          breadth_first_queuing(hash_map_open, state_current_successors, open_set);
        } else if (search_type == "a_star") {
          a_star_queuing(hash_map_open, state_current_successors, open_set);
        }
        state_successors.pop();
      }
    }
  }
  state_current.map_state = "SOLUTION NOT FOUND!\n";
  return state_current;
}

void breadth_first_queuing(Mymap &hash_map_open, Soko_state &state_current_successors, deque<Soko_state> &open_set)
{
  open_set.push_back(state_current_successors);
  hash_map_open.insert(Mymap::value_type(state_current_successors.map_state, state_current_successors));
}

void a_star_queuing(Mymap &hash_map_open, Soko_state &state_current_successors, deque<Soko_state> &open_set)
{
  bool inserted = false;

  for (auto it = open_set.begin(); it != open_set.end(); it++)
  {
    if ((it->f_score) > (state_current_successors.f_score))
    {
      open_set.insert(it, state_current_successors);
      hash_map_open.insert(Mymap::value_type(state_current_successors.map_state, state_current_successors));
      inserted = true;
      break;
    }
  }

  if (!inserted)
    open_set.push_back(state_current_successors);
}