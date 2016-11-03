#include "common.h"

bool is_goal_state(Soko_state &state_current)
{
  size_t legal_chars = state_current.map_state.find_first_not_of("XI.M\n");
  if(legal_chars != string::npos)
    return false;
  else
    return true;
}

void make_init_state(int argc, char** argv, Soko_state &init_state)
{
  ifstream sokoban_map_file;
  sokoban_map_file.open (argv[1]);
  if (!sokoban_map_file)
  {
    cerr << "[error]  can't open " << argv[1] << endl;
  }

  // Extract map metadata
  // http://www.cplusplus.com/forum/general/13135/
  string line;
	getline(sokoban_map_file, line, ' ');
	int map_width = atoi(line.c_str());
  getline(sokoban_map_file, line, ' ');
  int map_hight = atoi(line.c_str());
  getline(sokoban_map_file, line, '\n');
  int num_of_goals = atoi(line.c_str());

  init_state.height = map_hight;
  init_state.width = map_width;

  // Extract map
  string sokoban_map = "";
  while (getline(sokoban_map_file, line))
  {
    sokoban_map.append(line) += "\n";
  }

  init_state.map_state = sokoban_map;

  // Find player
  bool found = false;
  int row=-1, col=0;
  stringstream string_iterator(init_state.map_state);

  for(int i = 0; i < init_state.height; i++)
  {
    getline( string_iterator, line, '\n' );
    if(!found)
      row++;

    for (int j = 0; j < init_state.width ; j++)
    {
      if (!found)
      {
        if (line[j] == 'M' || line[j] == 'W' )
        {
          col = j;
          found = true;
        }
      }
    }
  }

  if(!found)
    cout << "[error]  player not found" << endl;

  init_state.player_row = row;
  init_state.player_col = col;

  cout << "[map]  map dimensions:  "<< map_hight << " x " << map_width << endl;
  cout << "[map]  number of goals: "<< num_of_goals << endl;
  cout << "[map]  player position: "<< row << " x " << col << endl << endl;
  cout << "[map]  sokoban map loaded:" << endl;
  cout << sokoban_map << endl;

  init_state.moves = "";
  init_state.cost_to_node = 0;
  init_state.cost_to_goal = h1(init_state);
  init_state.f_score = init_state.cost_to_node + init_state.cost_to_goal;
}

/* Heuristics function uses Manhattan distance between player and
 *  nearest box, and between the boxes and the goals.
 *  Assumes only 1 player on level.
 *
 * Preconditions: State object
 * Postcoditions: int return representing heuristics score
 */
int h1(const Soko_state &cur_state)
{
	std::stringstream ss(cur_state.map_state);
	std::string line;
	int x, y, counter = 0;
	std::vector< std::vector<int> > box_list;
	std::vector< std::vector<int> > goal_list;
	int score = 0;
	int playerdist = 1000;

	while (getline(ss,line, '\n'))
	{
		for (int i = 0; i <line.length() ; i++)
		{
			//assumes only 1 player exists in any given state
			//if found user, set x, y positions
			if (line[i] == 'M')
			{
				x = i;
				y = counter;
			}
			//if player is on an empty goal, pos of player
			//is the same as an empty goal
			else if (line[i] == 'W' )
			{
				x = i;
				y = counter;
				std::vector<int> goal_loc;
				goal_loc.push_back(i);
				goal_loc.push_back(counter);
				goal_list.push_back(goal_loc);
			}
			//if box on floor, add to box list
			else if (line[i] == 'J' )
			{
				std::vector<int> box_loc;
				box_loc.push_back(i);
				box_loc.push_back(counter);
				box_list.push_back(box_loc);
			}
			//if empty goal, add to goal list
			else if (line[i] == 'G' )
			{
				std::vector<int> goal_loc;
				goal_loc.push_back(i);
				goal_loc.push_back(counter);
				goal_list.push_back(goal_loc);
			}
			//if there is a box on a goal, then it should take
			//precidence over non fill goals in case there are multiple
			//boxes and goals.  we want the program to let the box remain
			//on the goal.  to this end, -1000 is added to the score
			else if(line[i] == 'I')
			{
				score -= 1000;
			}
		}
		counter++;
	}

	//for each box on the floor, calculate the distance to each empty goal
	for (int i = 0; i < box_list.size(); i++)
	{
		for (int j = 0; j < goal_list.size(); j++)
		{
			//calculate distance of x and y cords
			int xdist = box_list[i][0] - goal_list[j][0];
			int ydist = box_list[i][1] - goal_list[j][1];
			//take absolute value of distance
			if (xdist < 0)
				xdist *= -1;
			if (ydist < 0)
				ydist *= -1;
			//add distance to score, lower score = better
			score += xdist;
			score += ydist;
		}
		//calculate player to box distances
		int p_to_box_x = box_list[i][0] - x;
		int p_to_box_y = box_list[i][1] - y;
		//take absolute value of distance
		if (p_to_box_x < 0)
			p_to_box_x *= -1;
		if (p_to_box_y < 0)
			p_to_box_y *= -1;
		//stores shortest distance to any box
		//NOTE: This only works if shortest distance is within 1000 tiles
		if (playerdist > (p_to_box_y + p_to_box_x))
			playerdist = (p_to_box_y + p_to_box_x);
	}
	score += playerdist;
	return score;
}
