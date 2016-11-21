#include "graph_search.h"
// https://msdn.microsoft.com/en-us/library/bb982522.aspx

Soko_state graph_search(Soko_state &state_init, string search_type, string heuristics_type)
{
  cout << "\n[info] executing " << search_type << " search!" << endl;

  // Make variable for current state
  Soko_state state_current;

  // Initialize open and closed set
  deque<Soko_state> open_set;
  priority_queue<Soko_state,vector<Soko_state>, compare > open_set_pq;
  Mymap hash_map_closed;
  Mymap hash_map_open;

  // Put start state in the open set.
  if (search_type == "a_star")
    open_set_pq.push(state_init);
  else
    open_set.push_back(state_init);

  hash_map_open.insert(Mymap::value_type(state_init.map_state, state_init));

  while ( (search_type == "a_star" ? !open_set_pq.empty() : !open_set.empty()) )
  {
    // Maintain open set
    if (search_type == "a_star"){
      state_current = open_set_pq.top();
      open_set_pq.pop();
    }
    else{
      state_current = open_set.front();
      open_set.pop_front();
    }
    hash_map_open.erase(state_current.map_state);

    // maintain closed set
    hash_map_closed.insert(Mymap::value_type(state_current.map_state, state_current));

    // If current state is the goal state, then terminate
    if (is_goal_state(state_current)){
      cout << "[info] visited a total of "<< hash_map_closed.size() <<" nodes"<<endl;
      return state_current;
    }

    // State generation
    queue<Soko_state> state_successors = make_states(state_current, heuristics_type);

    // For each state state successors of state current do
    while (!state_successors.empty())
    {
      Soko_state state_current_successors = state_successors.front();

      // Is the current state successors in the open or closed set?
      if (hash_map_open.count(state_current_successors.map_state) || hash_map_closed.count(state_current_successors.map_state)){
        state_successors.pop();
        continue; }

      if (search_type == "breadth_first"){
        open_set.push_back(state_current_successors);
        hash_map_open.insert(Mymap::value_type(state_current_successors.map_state, state_current_successors));
      }
      else if (search_type == "a_star")
        open_set_pq.push(state_current_successors);

      state_successors.pop();
    }
    if ((hash_map_closed.size() % 10000) == 0)
      cout << "[info] visited "<< hash_map_closed.size()/1000 <<"K nodes"<<endl;
  }
  state_current.map_state = "SOLUTION NOT FOUND!\n";
  return state_current;
}

bool is_goal_state(Soko_state &state_current)
{
  size_t legal_chars = state_current.map_state.find_first_not_of("XI.MND\n");
  if(legal_chars != string::npos)
    return false;
  else
    return true;
}
