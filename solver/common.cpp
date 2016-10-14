#include "common.h"

bool is_goal_state(Soko_state &state_current)
{
  bool is_goal = false;
  size_t found_goal = state_current.map_state.find("G");
  size_t found_robot_on_goal = state_current.map_state.find("W");
  size_t found_free_box = state_current.map_state.find("J");

  if(found_goal == string::npos){
    if(found_robot_on_goal == string::npos){
      if(found_free_box == string::npos){
        is_goal = true;
      }
      //else cout << "free box detected!" << endl;
    }
    //else cout << "robot on goal detected!" << endl;
  }
  //else cout << "free goal detected!" << endl;
  return is_goal;
}

queue<Soko_state> make_states(const Soko_state &cur_state)
{
  int x=0, y=-1;
  char player;
  bool found = false;

  //http://stackoverflow.com/questions/5757721/use-getline-and-while-loop-to-split-a-string
  stringstream string_iterator(cur_state.map_state);
  string line;

  for(int i = 0; i < cur_state.height; i++)
	{
    getline(string_iterator, line, '\n');
    if(!found)
      y++;

    for (int i = 0; i <line.length() ; i++)
    {
    	if (!found)
    	{
    		if (line[i] == 'M' | line[i] == 'W' )
    		{
    			player = line[i];
    			x = i;
    			found = true;
    		}
    	}
    }
  }
  cout << "[into]   Player: " << "(" << x << "," << y << ")" << endl;

  if(!found)
  {
    cout << "[error]  player not found" << endl;
  }

  queue<Soko_state> states;
  return states;
}
