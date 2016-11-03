#include "state_generator.h"

queue<Soko_state> make_states(const Soko_state &state_current)
{
  vector< vector<char> > map_vector;
  map_vector.resize( state_current.height , vector<char>( state_current.width , 'Q' ) );

  // Make string to vector<vector<char>> map
  int row_tmp = 0, col_tmp = 0;
  for (int i = 0; i < state_current.map_state.size(); i++) {
    if (state_current.map_state[i]=='\n') {
      row_tmp += 1;
      col_tmp = 0;
    }
    else {
      map_vector[row_tmp][col_tmp] = state_current.map_state[i];
      col_tmp +=1;
    }
  }

  /// Make moves
  queue<Soko_state> new_states;
  Soko_state move_state;
  // forward
  move_state = move( state_current, map_vector, 'u' );
  if (move_state.map_state != "NO_MOVE") {
    new_states.push( move_state );
  }
  // backward
  move_state = move( state_current, map_vector, 'd' );
  if (move_state.map_state != "NO_MOVE") {
    new_states.push( move_state );
  }
  // right
  move_state = move( state_current, map_vector, 'r' );
  if (move_state.map_state != "NO_MOVE") {
    new_states.push( move_state );
  }
  // left
  move_state = move( state_current, map_vector, 'l' );
  if (move_state.map_state != "NO_MOVE") {
    new_states.push( move_state );
  }
  return new_states;
}

Soko_state move(const Soko_state &state_current, vector< vector<char> > map_vector, char movement_type)
{
  Soko_state new_state = state_current;
  bool no_move = false;
  const int COST_MOVE = 1, COST_PUSH = 1;
  int new_row, new_col, new_row_push, new_col_push;
  int row = state_current.player_row, col = state_current.player_col;
  string update_move = "", update_move_push = "";

  switch (movement_type) {
    case 'u':
      new_row = row-1;
      new_col = col;
      new_row_push = row-2;
      new_col_push = col;
      update_move = "u";
      update_move_push = "U";
      break;
    case 'd':
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

      // Update Sokoban Struct With New Values
      new_state.moves.append(update_move);
      new_state.cost_to_node += COST_MOVE;
      new_state.cost_to_goal = h1(new_state);
      new_state.f_score = new_state.cost_to_node + new_state.cost_to_goal;
      new_state.player_col = new_col;
      new_state.player_row = new_row;
      // Go back to string
      vecmap2string(new_state, map_vector);
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

      // Update Sokoban Struct With New Values
      new_state.moves.append(update_move);
      new_state.cost_to_node += COST_MOVE;
      new_state.cost_to_goal = h1(new_state);
      new_state.f_score = new_state.cost_to_node + new_state.cost_to_goal;
      new_state.player_col = new_col;
      new_state.player_row = new_row;
      // Go back to string
      vecmap2string(new_state, map_vector);
      break;
    case 'J':
      // Move play to the new spot
      if ( map_vector[row][col] == 'M' ) {
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
      if ( !no_move )
      {
        // Update Sokoban Struct With New Values
        new_state.moves.append(update_move_push);
        new_state.cost_to_node += COST_PUSH;
        new_state.cost_to_goal = h1(new_state);
        new_state.f_score = new_state.cost_to_node + new_state.cost_to_goal;
        new_state.player_col = new_col;
        new_state.player_row = new_row;
        // Go back to string
        vecmap2string(new_state, map_vector);
      }
      else
        new_state.map_state = "NO_MOVE";
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
            no_move = true;
          else
            map_vector[new_row_push][new_col_push] = 'J';
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
      if ( !no_move ) {
        // Update Sokoban Struct With New Values
        new_state.moves.append( update_move_push );
        new_state.cost_to_node += COST_PUSH;
        new_state.cost_to_goal = h1(new_state);
        new_state.f_score = new_state.cost_to_node + new_state.cost_to_goal;
        new_state.player_col = new_col;
        new_state.player_row = new_row;
        // Go back to string
        vecmap2string(new_state, map_vector);
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

void vecmap2string (Soko_state &input_state, vector<vector<char>> &map_vector)
{
  input_state.map_state = "";
  for (int i = 0; i < input_state.height; i++) {
    for (int j = 0; j < input_state.width; j++)
      input_state.map_state.push_back( map_vector[i][j] );
    input_state.map_state.push_back('\n');
  }
}
