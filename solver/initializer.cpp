#include "initializer.h"

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
  init_state.num_of_goals = num_of_goals;

  // Extract map
  string sokoban_map = "";
  while (getline(sokoban_map_file, line))
  {
    sokoban_map.append(line) += "\n";
  }

  init_state.map_state = sokoban_map;
  deadlock_tester_static(init_state);

  // Find player
  int row=0, col=0;

  while (true) {
    if (init_state.get(row, col) == 'M' || init_state.get(row, col) == 'N' || init_state.get(row, col) == 'W')
      break;
    if (col == init_state.height){
      col = 0;
      if (row == init_state.width){
        cout << "[error]  player not found" << endl;
        break;
      }
      else
        row++;
    }
    else
      col++;
  }

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
