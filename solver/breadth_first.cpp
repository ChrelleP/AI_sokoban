#include "breadth_first.h"

Soko_state breadth_first(Soko_state &init_state)
{
  cout << "[info]   executing breadth first search!" << endl;
  deque<Soko_state> open;
	vector<Soko_state> closed;
	Soko_state current_state;

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
      std::cout << "Searched "<< closed.size() <<" nodes"<<std::endl;

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
        if (it->moves == temp_state.moves)
        {
          already_seen = true;
          break;
        }
      }
      //check if state has already been seen on closed list
      for (itr = closed.begin(); itr != closed.end(); itr++)
      {
        if (itr->moves == temp_state.moves)
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
