#include "breadth_first.h"
// https://msdn.microsoft.com/en-us/library/bb982522.aspx
Soko_state breadth_first(Soko_state &init_state)
{
  cout << "[info]   executing breadth first search!" << endl;
  deque<Soko_state> open;
	vector<Soko_state> closed;
	Soko_state current_state;
  Mymap hash_map;
  cout << "max_size() == " << hash_map.max_size() << endl;
  hash_map.insert(Mymap::value_type(init_state.map_state, 22));
  hash_map.insert(Mymap::value_type("kit", 99));
  hash_map.insert(Mymap::value_type("kat", 3));

  for (Mymap::const_iterator it = hash_map.begin();
    it != hash_map.end(); ++it)
    std::cout << " [" << it->first << ", " << it->second << "]";
  std::cout << std::endl;

  std::cout << "count(\"state\") == " << hash_map.count(init_state.map_state) << std::endl;

  //push first state into queue
  open.push_back(init_state);
  while (!open.empty())
  {
    //take N from OPEN
    current_state = open.front();
    open.pop_front();
    //push N onto CLOSED
    closed.push_back(current_state);

    //print out in case a long time is taken and wondering if it froze
    if ((closed.size() % 5000) == 0)
    {
      cout << "Searched "<< closed.size() <<" nodes"<<endl;
    }

    //if found, set report node to current node, set explored count to closed list size
    if (is_goal_state(current_state))
    {
      open.pop_front();
      return current_state;
    }

    //generate valid states
    queue<Soko_state> valid_states = make_states(current_state);
    deque<Soko_state>::iterator it;
    vector<Soko_state>::iterator itr;

    //while queue is not empty of states
    while (!valid_states.empty())
    {
      bool already_seen = false;
      Soko_state temp_state = valid_states.front();
      //check if state has already been seen on open list
      for (it = open.begin(); it != open.end(); it++)
      {
        if (it->map_state == temp_state.map_state)
        {
          already_seen = true;
          break;
        }
      }
      //check if state has already been seen on closed list
      for (itr = closed.begin(); itr != closed.end(); itr++)
      {
        if (itr->map_state == temp_state.map_state)
        {
          already_seen = true;
          break;
        }
      }
      //if not duplicate, then add state to open queue
      if (!already_seen)
      {
        //add to back of open
        open.push_back(temp_state);
      }
      else
      valid_states.pop();
    }
  }
  return current_state;
}
