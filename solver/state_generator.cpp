#include "state_generator.h"

queue<Soko_state> make_states(const Soko_state &current_state)
{
  int col=0, row=-1;
  char player;
  bool found = false;

  // Find position of the player
  // http://stackoverflow.com/questions/5757721/use-getline-and-while-loop-to-split-a-string
  stringstream string_iterator(current_state.map_state);
  vector< vector<char> > map_vector;
  map_vector.resize( current_state.height , vector<char>( current_state.width , 'Q' ) );
  string line;

  // Find player
  for(int i = 0; i < current_state.height; i++)
	{
    getline( string_iterator, line, '\n' );
    if(!found)
      row++;

    for (int j = 0; j < current_state.width ; j++)
    {
      map_vector[i][j] = line[j];

    	if (!found)
    	{
    		if (line[j] == 'M' || line[j] == 'W' )
    		{
    			player = line[j];
    			col = j;
    			found = true;
    		}
    	}
    }
  }
  //cout << "[info]   Player: " << "(" << col << "," << row << ")" << endl;
  //cout << "[info]   Player symbol: " << map_vector[row][col] << endl;

  if(!found)
  {
    cout << "[error]  player not found" << endl;
  }


  //new_states.push( move( current_state, map_vector, col, row, 'b' ) );
  //cout << "\n" << new_state.map_state << endl;
  /// Make moves
  queue<Soko_state> new_states;
  Soko_state tmp_state;
  // forward
  tmp_state = move( current_state, map_vector, col, row, 'f' );
  if (tmp_state.map_state != "NO_MOVE") {
    new_states.push( tmp_state );
  }
  // backward
  tmp_state = move( current_state, map_vector, col, row, 'b' );
  if (tmp_state.map_state != "NO_MOVE") {
    new_states.push( tmp_state );
  }
  // right
  tmp_state = move( current_state, map_vector, col, row, 'r' );
  if (tmp_state.map_state != "NO_MOVE") {
    new_states.push( tmp_state );
  }
  // left
  tmp_state = move( current_state, map_vector, col, row, 'l' );
  if (tmp_state.map_state != "NO_MOVE") {
    new_states.push( tmp_state );
  }
  return new_states;
}

Soko_state move(const Soko_state &current_state, vector< vector<char> > map_vector, int col , int row, char movement_type)
{
  Soko_state new_state = current_state;
  bool no_move = false;
  const int COST_MOVE = 1;
  const int COST_PUSH = 1;
  int new_row, new_col, new_row_push, new_col_push;
  string update_move = "";
  string update_move_push = "";

  // For forward
  switch (movement_type) {
    case 'f':
      new_row = row-1;
      new_col = col;
      new_row_push = row-2;
      new_col_push = col;
      update_move = "u";
      update_move_push = "U";
      break;
    case 'b':
      new_row = row+1;
      new_col = col;
      new_row_push = row+2;
      new_col_push = col;
      update_move = "d";
      update_move_push = "D";
      break;
    case 'l':
      new_row = row;
      new_col = col-1;
      new_row_push = row;
      new_col_push = col-2;
      update_move = "l";
      update_move_push = "L";
      break;
    case 'r':
      new_row = row;
      new_col = col+1;
      new_row_push = row;
      new_col_push = col+2;
      update_move = "r";
      update_move_push = "R";
      break;
    default:
      cout << "[error]  unknown movement direction" << endl;
      break;
  }

  switch (map_vector[new_row][new_col]) {
    case '.':
      // Move play to the new spot
      if (map_vector[row][col] == 'M') {
        map_vector[new_row][new_col] = 'M';
        map_vector[row][col] = '.';
      } else {
        map_vector[new_row][new_col] = 'M';
        map_vector[row][col] = 'G';
      }

      // Update moves list with forward move
      new_state.moves.append(update_move);
      new_state.cost_to_node += COST_MOVE;
      new_state.cost_to_goal = h1(new_state);
      new_state.f_score = new_state.cost_to_node + new_state.cost_to_goal;

      // Go back to string
      new_state.map_state = "";
      for (int i = 0; i < new_state.height; i++)
      {
        for (int j = 0; j < new_state.width; j++)
          new_state.map_state.push_back( map_vector[i][j] );
        new_state.map_state.push_back('\n');
      }
      break;
    case 'G':
      // Move play to the new spot
      if (map_vector[row][col] == 'M') {
        map_vector[new_row][new_col] = 'W';
        map_vector[row][col] = '.';
      } else {
        map_vector[new_row][new_col] = 'W';
        map_vector[row][col] = 'G';
      }

      // Update moves list with forward move
      new_state.moves.append(update_move);
      new_state.cost_to_node += COST_MOVE;
      new_state.cost_to_goal = h1(new_state);
      new_state.f_score = new_state.cost_to_node + new_state.cost_to_goal;

      // Go back to string
      new_state.map_state = "";
      for (int i = 0; i < new_state.height; i++)
      {
        for (int j = 0; j < new_state.width; j++)
          new_state.map_state.push_back( map_vector[i][j] );
        new_state.map_state.push_back('\n');
      }
      break;
    case 'J':
      // Move play to the new spot
      if (map_vector[row][col] == 'M') {
        map_vector[new_row][new_col] = 'M';
        map_vector[row][col] = '.';
      } else {
        map_vector[new_row][new_col] = 'M';
        map_vector[row][col] = 'G';
      }

      switch ( map_vector[new_row_push][new_col_push] ) {
        case '.':
          if (deadlock_test(map_vector,new_col_push,new_row_push))
          {
            no_move = true;
          }
          else
          {
            map_vector[new_row_push][new_col_push] = 'J';
          }
          break;
        case 'G':
          map_vector[new_row_push][new_col_push] = 'I';
          break;
        case 'X':
        case 'J':
        case 'I':
        default:
          no_move = true;
          break;
      }
      if (!no_move) {
        // Update moves list with forward move
        new_state.moves.append(update_move_push);
        new_state.cost_to_node += COST_PUSH;
        new_state.cost_to_goal = h1(new_state);
        new_state.f_score = new_state.cost_to_node + new_state.cost_to_goal;

        // Go back to string
        new_state.map_state = "";
        for (int i = 0; i < new_state.height; i++)
        {
          for (int j = 0; j < new_state.width; j++)
            new_state.map_state.push_back( map_vector[i][j] );
          new_state.map_state.push_back('\n');
        }
      } else {
        new_state.map_state = "NO_MOVE";
      }
  		break;
    case 'I':
      // Move play to the new spot
      if (map_vector[row][col] == 'M') {
        map_vector[new_row][new_col] = 'W';
        map_vector[row][col] = '.';
      } else {
        map_vector[new_row][new_col] = 'W';
        map_vector[row][col] = 'G';
      }

      switch ( map_vector[new_row_push][new_col_push] ) {
        case '.':
          if (deadlock_test(map_vector,new_col_push,new_row_push))
          {
            no_move = true;
          }
          else
          {
            map_vector[new_row_push][new_col_push] = 'J';
          }
          break;
        case 'G':
          map_vector[new_row_push][new_col_push] = 'I';
          break;
        case 'X':
        case 'J':
        case 'I':
        default:
          no_move = true;
          break;
      }
      if (!no_move) {
        // Update moves list with forward move
        new_state.moves.append(update_move_push);
        new_state.cost_to_node += COST_PUSH;
        new_state.cost_to_goal = h1(new_state);
        new_state.f_score = new_state.cost_to_node + new_state.cost_to_goal;

        // Go back to string
        new_state.map_state = "";
        for (int i = 0; i < new_state.height; i++)
        {
          for (int j = 0; j < new_state.width; j++)
            new_state.map_state.push_back( map_vector[i][j] );
          new_state.map_state.push_back('\n');
        }
      } else {
        new_state.map_state = "NO_MOVE";
      }
      break;
    case 'X':
      new_state.map_state = "NO_MOVE";
      break;
    default:
      cout << "[error]  " << map_vector[new_row][new_col] << " is a unknown puzzle type" << endl;
      break;
  }
  return new_state;
}

/*
* Mathias og Chrisians: SOKOBAN SOLVER
*
* Information:
* X = Wall            (#)
* J = box on free     ($)
* I = box on goal     (*)
* G = Empty Goal      (.)
* . = free ground     ( )
* M = robot on free   (@)
* W = robot on goal   (+)
*
*/

bool deadlock_test(vector< vector<char> > map_vector, int col, int row)
{
  char p1 = map_vector[row-1][col+1];
  char p2 = map_vector[row][col+1];
  char p3 = map_vector[row+1][col+1];
  char p4 = map_vector[row+1][col];
  char p5 = map_vector[row+1][col-1];
  char p6 = map_vector[row][col-1];
  char p7 = map_vector[row-1][col-1];
  char p8 = map_vector[row-1][col];

  // Check for corner deadlock
  if ((p8 == 'X' && p1 == 'X' && p2 == 'X') ||
      (p2 == 'X' && p3 == 'X' && p4 == 'X') ||
      (p4 == 'X' && p5 == 'X' && p6 == 'X') ||
      (p6 == 'X' && p7 == 'X' && p8 == 'X'))
  {
    return true;
  }

  // Check for against wall deadlock
  if (((p1 == 'X' && p2 == 'X' && p3 == 'X') && ( (p4 == 'J' || p4 == 'I') || (p8 == 'J' || p8 == 'I') )) ||
      ((p3 == 'X' && p4 == 'X' && p5 == 'X') && ( (p2 == 'J' || p2 == 'I') || (p6 == 'J' || p6 == 'I') )) ||
      ((p5 == 'X' && p6 == 'X' && p7 == 'X') && ( (p4 == 'J' || p4 == 'I') || (p8 == 'J' || p8 == 'I') )) ||
      ((p7 == 'X' && p8 == 'X' && p1 == 'X') && ( (p2 == 'J' || p2 == 'I') || (p6 == 'J' || p6 == 'I') )))
  {
    return true;
  }

  // Chek for empty goal wall deadlock (Make one for eack wall direction)
  if (false) {
    // Check if we meed a wall or box before a goal
  }

  return false;
}

std::size_t hash(std::vector<std::vector<int>> *vec)
{
    std::size_t hash = 0;
    for (auto &inner_vec : *vec) {
        boost::hash_combine(hash, inner_vec[0]);
        boost::hash_combine(hash, inner_vec[1]);
    }
    return hash;
}
