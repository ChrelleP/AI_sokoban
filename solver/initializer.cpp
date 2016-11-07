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

  // Extract map
  string sokoban_map = "";
  while (getline(sokoban_map_file, line))
  {
    sokoban_map.append(line) += "\n";
  }

  init_state.map_state = sokoban_map;
  deadlock_tester_static(init_state);

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

    for (int j = 0; j < init_state.width ; j++){
      if (!found){
        if (line[j] == 'M' || line[j] == 'W' || line[j] == 'N'){
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

//http://www.lamsade.dauphine.fr/~cazenave/papers/sokoban.pdf
void deadlock_tester_static(Soko_state &init_state)
{
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

      // DEADLOCK CORNER TESTS:
      row_tmp = row;
      col_tmp = col;

      if (p8 == 'X' && p2 == 'X') {

        if (map_vector[row][col] == '.' || map_vector[row][col] == 'M') {
          if ( map_vector[row][col] == 'M') {
            map_vector[row][col] = 'N';
          } else map_vector[row][col] = 'D';
          // HORISONTAL RIGHT TOP CORNER
          bool clean_wall = false;
          while ( map_vector[row_tmp-1][col_tmp] == 'X' &&
                ( map_vector[row_tmp][col_tmp] == '.' || map_vector[row_tmp][col_tmp] == 'D' || map_vector[row_tmp][col_tmp] == 'M' || map_vector[row_tmp][col_tmp] == 'N') ) {
            if (map_vector[row_tmp][col_tmp-1] == 'X') {
              row_tmp = row;
              col_tmp = col;
              clean_wall = true;
              break;
            } else col_tmp--; }

          while ( map_vector[row_tmp-1][col_tmp] == 'X' &&
                ( map_vector[row_tmp][col_tmp] == '.' || map_vector[row_tmp][col_tmp] == 'D' || map_vector[row_tmp][col_tmp] == 'M' || map_vector[row_tmp][col_tmp] == 'N') ) {
            if ( map_vector[row_tmp][col_tmp] == 'M') {
              map_vector[row_tmp][col_tmp] = 'N';
            } else if ( map_vector[row_tmp][col_tmp] == '.')
              map_vector[row_tmp][col_tmp] = 'D';
            col_tmp--; }

          // VERTICAL LEFT TOP CORNER
          row_tmp = row;
          col_tmp = col;
          clean_wall = false;
          while ( map_vector[row_tmp][col_tmp+1] == 'X' &&
                ( map_vector[row_tmp][col_tmp] == '.' || map_vector[row_tmp][col_tmp] == 'D' || map_vector[row_tmp][col_tmp] == 'M' || map_vector[row_tmp][col_tmp] == 'N') ) {
            if (map_vector[row_tmp+1][col_tmp] == 'X') {
              row_tmp = row;
              col_tmp = col;
              clean_wall = true;
              break;
            } else row_tmp++; }

          while ( map_vector[row_tmp][col_tmp+1] == 'X' &&
                ( map_vector[row_tmp][col_tmp] == '.' || map_vector[row_tmp][col_tmp] == 'D' || map_vector[row_tmp][col_tmp] == 'M' || map_vector[row_tmp][col_tmp] == 'N') ) {
            if ( map_vector[row_tmp][col_tmp] == 'M') {
              map_vector[row_tmp][col_tmp] = 'N';
            } else if ( map_vector[row_tmp][col_tmp] == '.')
              map_vector[row_tmp][col_tmp] = 'D';
            row_tmp++; }
        }

      } else if (p2 == 'X' && p4 == 'X') {
        if (map_vector[row][col] == '.' || map_vector[row][col] == 'M') {
          if ( map_vector[row][col] == 'M') {
            map_vector[row][col] = 'N';
          } else map_vector[row][col] = 'D';
          // HORISONTAL RIGHT BOTTOM CORNER
          bool clean_wall = false;
          while ( map_vector[row_tmp+1][col_tmp] == 'X' &&
                ( map_vector[row_tmp][col_tmp] == '.' || map_vector[row_tmp][col_tmp] == 'D' || map_vector[row_tmp][col_tmp] == 'M' || map_vector[row_tmp][col_tmp] == 'N') ) {
            if (map_vector[row_tmp][col_tmp-1] == 'X') {
              row_tmp = row;
              col_tmp = col;
              clean_wall = true;
              break;
            } else col_tmp--; }

          while ( map_vector[row_tmp+1][col_tmp] == 'X' &&
                ( map_vector[row_tmp][col_tmp] == '.' || map_vector[row_tmp][col_tmp] == 'D' || map_vector[row_tmp][col_tmp] == 'M' || map_vector[row_tmp][col_tmp] == 'N') ) {
            if ( map_vector[row_tmp][col_tmp] == 'M') {
              map_vector[row_tmp][col_tmp] = 'N';
            } else if ( map_vector[row_tmp][col_tmp] == '.')
              map_vector[row_tmp][col_tmp] = 'D';
            col_tmp--; }

          // VERTICAL LEFT BOTTOM CORNER
          row_tmp = row;
          col_tmp = col;
          clean_wall = false;
          while ( map_vector[row_tmp][col_tmp+1] == 'X' &&
                ( map_vector[row_tmp][col_tmp] == '.' || map_vector[row_tmp][col_tmp] == 'D' || map_vector[row_tmp][col_tmp] == 'M' || map_vector[row_tmp][col_tmp] == 'N') ) {
            if (map_vector[row_tmp-1][col_tmp] == 'X') {
              row_tmp = row;
              col_tmp = col;
              clean_wall = true;
              break;
            } else row_tmp--; }

          while ( map_vector[row_tmp][col_tmp+1] == 'X' &&
                ( map_vector[row_tmp][col_tmp] == '.' || map_vector[row_tmp][col_tmp] == 'D' || map_vector[row_tmp][col_tmp] == 'M' || map_vector[row_tmp][col_tmp] == 'N') ) {
            if ( map_vector[row_tmp][col_tmp] == 'M') {
              map_vector[row_tmp][col_tmp] = 'N';
            } else if ( map_vector[row_tmp][col_tmp] == '.')
              map_vector[row_tmp][col_tmp] = 'D';
            row_tmp--; }
        }
      } else if (p4 == 'X' && p6 == 'X') {
        if (map_vector[row][col] == '.' || map_vector[row][col] == 'M') {
          if ( map_vector[row][col] == 'M') {
            map_vector[row][col] = 'N';
          } else map_vector[row][col] = 'D';
          // HORISONTAL LEFT BOTTOM CORNER
          bool clean_wall = false;
          while ( map_vector[row_tmp+1][col_tmp] == 'X' &&
                ( map_vector[row_tmp][col_tmp] == '.' || map_vector[row_tmp][col_tmp] == 'D' || map_vector[row_tmp][col_tmp] == 'M' || map_vector[row_tmp][col_tmp] == 'N') ) {
            if (map_vector[row_tmp][col_tmp+1] == 'X') {
              row_tmp = row;
              col_tmp = col;
              clean_wall = true;
              break;
            } else col_tmp++; }

          while ( map_vector[row_tmp+1][col_tmp] == 'X' &&
                ( map_vector[row_tmp][col_tmp] == '.' || map_vector[row_tmp][col_tmp] == 'D' || map_vector[row_tmp][col_tmp] == 'M' || map_vector[row_tmp][col_tmp] == 'N') ) {
            if ( map_vector[row_tmp][col_tmp] == 'M') {
              map_vector[row_tmp][col_tmp] = 'N';
            } else if ( map_vector[row_tmp][col_tmp] == '.')
              map_vector[row_tmp][col_tmp] = 'D';
            col_tmp++; }

          // VERTICAL LEFT BOTTOM CORNER
          row_tmp = row;
          col_tmp = col;
          clean_wall = false;
          while ( map_vector[row_tmp][col_tmp-1] == 'X' &&
                ( map_vector[row_tmp][col_tmp] == '.' || map_vector[row_tmp][col_tmp] == 'D' || map_vector[row_tmp][col_tmp] == 'M' || map_vector[row_tmp][col_tmp] == 'N') ) {
            if (map_vector[row_tmp-1][col_tmp] == 'X') {
              row_tmp = row;
              col_tmp = col;
              clean_wall = true;
              break;
            } else row_tmp--; }

          while ( map_vector[row_tmp][col_tmp-1] == 'X' &&
                ( map_vector[row_tmp][col_tmp] == '.' || map_vector[row_tmp][col_tmp] == 'D' || map_vector[row_tmp][col_tmp] == 'M' || map_vector[row_tmp][col_tmp] == 'N') ) {
            if ( map_vector[row_tmp][col_tmp] == 'M') {
              map_vector[row_tmp][col_tmp] = 'N';
            } else if ( map_vector[row_tmp][col_tmp] == '.')
              map_vector[row_tmp][col_tmp] = 'D';
            row_tmp--; }
        }
      } else if (p6 == 'X' && p8 == 'X') {
        if (map_vector[row][col] == '.' || map_vector[row][col] == 'M') {
          if ( map_vector[row][col] == 'M') {
            map_vector[row][col] = 'N';
          } else map_vector[row][col] = 'D';

          // HORISONTAL LEFT TOP CORNER
          bool clean_wall = false;
          while ( map_vector[row_tmp-1][col_tmp] == 'X' &&
                ( map_vector[row_tmp][col_tmp] == '.' || map_vector[row_tmp][col_tmp] == 'D' || map_vector[row_tmp][col_tmp] == 'M' || map_vector[row_tmp][col_tmp] == 'N') ) {
            if (map_vector[row_tmp][col_tmp+1] == 'X') {
              row_tmp = row;
              col_tmp = col;
              clean_wall = true;
              break;
            } else col_tmp++; }

          while ( map_vector[row_tmp-1][col_tmp] == 'X' &&
                ( map_vector[row_tmp][col_tmp] == '.' || map_vector[row_tmp][col_tmp] == 'D' || map_vector[row_tmp][col_tmp] == 'M' || map_vector[row_tmp][col_tmp] == 'N') ) {
            if ( map_vector[row_tmp][col_tmp] == 'M') {
              map_vector[row_tmp][col_tmp] = 'N';
            } else if ( map_vector[row_tmp][col_tmp] == '.')
              map_vector[row_tmp][col_tmp] = 'D';
            col_tmp++; }

          // VERTICAL LEFT TOP CORNER
          row_tmp = row;
          col_tmp = col;
          clean_wall = false;
          while ( map_vector[row_tmp][col_tmp-1] == 'X' &&
                ( map_vector[row_tmp][col_tmp] == '.' || map_vector[row_tmp][col_tmp] == 'D' || map_vector[row_tmp][col_tmp] == 'M' || map_vector[row_tmp][col_tmp] == 'N') ) {
            if (map_vector[row_tmp+1][col_tmp] == 'X') {
              row_tmp = row;
              col_tmp = col;
              clean_wall = true;
              break;
            } else row_tmp++; }

          while ( map_vector[row_tmp][col_tmp-1] == 'X' &&
                ( map_vector[row_tmp][col_tmp] == '.' || map_vector[row_tmp][col_tmp] == 'D' || map_vector[row_tmp][col_tmp] == 'M' || map_vector[row_tmp][col_tmp] == 'N') ) {
            if ( map_vector[row_tmp][col_tmp] == 'M') {
              map_vector[row_tmp][col_tmp] = 'N';
            } else if ( map_vector[row_tmp][col_tmp] == '.')
              map_vector[row_tmp][col_tmp] = 'D';
            row_tmp++; }

        }
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
