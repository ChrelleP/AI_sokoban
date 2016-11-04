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
  int map_height = atoi(line.c_str());
  getline(sokoban_map_file, line, '\n');
  int num_of_goals = atoi(line.c_str());

  init_state.height = map_height;
  init_state.width = map_width;

  // Extract map
  string sokoban_map = "";
  while (getline(sokoban_map_file, line))
  {
    sokoban_map.append(line) += "\n";
  }

  init_state.map_state = sokoban_map;
  // deadlock_tester(init_state); // TODO: Make player model for "on deadlock" 'N'

  // Find player
  // http://stackoverflow.com/questions/5757721/use-getline-and-while-loop-to-split-a-string
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

  cout << "[map]  map dimensions:  "<< map_height << " x " << map_width << endl;
  cout << "[map]  number of goals: "<< num_of_goals << endl;
  cout << "[map]  player position: "<< row << " x " << col << endl << endl;
  cout << "[map]  sokoban map loaded:" << endl;
  cout << init_state.map_state << endl;

  init_state.moves = "";
  init_state.cost_to_node = 0;
  init_state.cost_to_goal = h1(init_state);
  init_state.f_score = init_state.cost_to_node + init_state.cost_to_goal;
}

void deadlock_tester(Soko_state &init_state)
{
  cout << "test";
  vector< vector<char>> map_vector;
  map_vector.resize( init_state.height , vector<char>( init_state.width , 'Q' ) );

  // Make string to vector<vector<char>> map
  int row_tmp = 0, col_tmp = 0;
  for (int i = 0; i < init_state.map_state.size(); i++) {
    if (init_state.map_state[i]=='\n') {
      row_tmp += 1;
      col_tmp = 0;
    }
    else {
      map_vector[row_tmp][col_tmp] = init_state.map_state[i];
      col_tmp +=1;
    }
  }

  char p1,p2,p3,p4,p5,p6,p7,p8;

  for (int row = 1; row < init_state.height-1; row++) {
    for (int col = 1; col < init_state.width-1; col++) {
      p1 = map_vector[row-1][col+1];
      p2 = map_vector[row][col+1];
      p3 = map_vector[row+1][col+1];
      p4 = map_vector[row+1][col];
      p5 = map_vector[row+1][col-1];
      p6 = map_vector[row][col-1];
      p7 = map_vector[row-1][col-1];
      p8 = map_vector[row-1][col];

      // Check for corner deadlock
      if ((p8 == 'X' && p1 == 'X' && p2 == 'X') ||
          (p2 == 'X' && p3 == 'X' && p4 == 'X') ||
          (p4 == 'X' && p5 == 'X' && p6 == 'X') ||
          (p6 == 'X' && p7 == 'X' && p8 == 'X'))
      {
        if (map_vector[row][col] == '.') {
          map_vector[row][col] = 'D';
        }
      }

      // Chek for empty goal wall deadlock (Make one for eack wall direction)
      if (false) {
        // Check if we meed a wall or box before a goal
      }
    }
  }
  init_state.map_state = "";
  for (int i = 0; i < init_state.height; i++) {
    for (int j = 0; j < init_state.width; j++)
      init_state.map_state.push_back( map_vector[i][j] );
    init_state.map_state.push_back('\n');
  }
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
