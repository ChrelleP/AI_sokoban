#include "graph_search.h"

Soko_state graph_search(Soko_state &state_init, string search_type, string heuristics_type)
{
  // User feedback
  cout << "\n[info] executing " << search_type << " search!" << endl;

  // Make variable for current state
  Soko_state state_current;

  // Initialize open and closed sets
  deque<Soko_state> open_set;
  priority_queue<Soko_state,vector<Soko_state>, compare > open_set_pq;
  MyClosed hash_map_closed;
  MyOpen hash_map_open;

  // Put start state in the open set.
  if (search_type == "a_star")
    open_set_pq.push(state_init);
  else
    open_set.push_back(state_init);

  hash_map_open.insert(MyOpen::value_type(state_init.map_state, state_init));

  // Start the search until solution is found or until openset is empty
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
    hash_map_closed.insert(MyClosed::value_type(state_current.map_state, 's'));

    // If current state is the goal state, then terminate
    if (is_goal_state(state_current)){
      cout << "[info] visited a total of "<< hash_map_closed.size() <<" nodes"<<endl;
      return state_current;
    }

    // Generate new states
    queue<Soko_state> state_successors = make_states(state_current, heuristics_type);

    // For each state successor of state current do the following
    while (!state_successors.empty())
    {
      Soko_state state_current_successors = state_successors.front();

      // If the state successor is a dublicate then continue
      if (hash_map_open.count(state_current_successors.map_state) || hash_map_closed.count(state_current_successors.map_state)){
        state_successors.pop();
        continue; }

      // If it is not a dublicate then add it to the open set with either the BFS or A* method
      if (search_type == "breadth_first"){
        open_set.push_back(state_current_successors);
        hash_map_open.insert(MyOpen::value_type(state_current_successors.map_state, state_current_successors));
      }
      else if (search_type == "a_star")
        open_set_pq.push(state_current_successors);

      // Pop the state successor from the list of succesors and continue with the rest of the newly generated states
      state_successors.pop();
    }
    // Give user feedback on number of visised notes
    if ((hash_map_closed.size() % 10000) == 0)
      cout << "[info] visited "<< hash_map_closed.size()/1000 <<"K nodes"<<endl;
  }

  // If soluiton is not found then change the map to the following and return
  state_current.map_state = "SOLUTION NOT FOUND!\n";
  return state_current;
}

// Is goal state, checks if the conditions for a solved puzzle is present
bool is_goal_state(Soko_state &state_current)
{
  size_t legal_chars = state_current.map_state.find_first_not_of("XI.MND\n");
  if(legal_chars != string::npos)
    return false;
  else
    return true;
}
