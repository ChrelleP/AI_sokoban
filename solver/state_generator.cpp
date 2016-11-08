#include "state_generator.h"

queue<Soko_state> make_states(const Soko_state &state_current)
{
  /// Make moves
  queue<Soko_state> new_states;
  Soko_state move_state;
  // forward
  move_state = move( state_current, 'u' );
  if (move_state.map_state != "NO_MOVE") {
    new_states.push( move_state );
  }
  // backward
  move_state = move( state_current, 'd' );
  if (move_state.map_state != "NO_MOVE") {
    new_states.push( move_state );
  }
  // right
  move_state = move( state_current, 'r' );
  if (move_state.map_state != "NO_MOVE") {
    new_states.push( move_state );
  }
  // left
  move_state = move( state_current, 'l' );
  if (move_state.map_state != "NO_MOVE") {
    new_states.push( move_state );
  }
  return new_states;
}

Soko_state move(const Soko_state &state_current, char movement_type)
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

  switch (new_state.get(new_row, new_col)) {
    case 'D':
      // Move play to the new spot
      if (new_state.get(row, col) == 'M') {
        new_state.set(new_row, new_col, 'N');
        new_state.set(row, col, '.');
      } else if (new_state.get(row, col) == 'N') {
        new_state.set(new_row, new_col, 'N');
        new_state.set(row, col, 'D');
      } else {
        new_state.set(new_row, new_col, 'N');
        new_state.set(row, col, 'G');
      }

      // Update Sokoban Struct With New Values
      new_state.moves.append(update_move);
      new_state.cost_to_node += COST_MOVE;
      new_state.cost_to_goal = h1(new_state);
      new_state.f_score = new_state.cost_to_node + new_state.cost_to_goal;
      new_state.player_col = new_col;
      new_state.player_row = new_row;
      // Go back to string
      break;
    case '.':
      // Move play to the new spot
      if (new_state.get(row, col) == 'M') {
        new_state.set(new_row, new_col, 'M');
        new_state.set(row, col, '.');
      } else if (new_state.get(row, col) == 'N') {
        new_state.set(new_row, new_col, 'M');
        new_state.set(row, col, 'D');
      } else {
        new_state.set(new_row, new_col, 'M');
        new_state.set(row, col, 'G');
      }

      // Update Sokoban Struct With New Values
      new_state.moves.append(update_move);
      new_state.cost_to_node += COST_MOVE;
      new_state.cost_to_goal = h1(new_state);
      new_state.f_score = new_state.cost_to_node + new_state.cost_to_goal;
      new_state.player_col = new_col;
      new_state.player_row = new_row;
      break;
    case 'G':
      // Move play to the new spot
      if (new_state.get(row, col) == 'M') {
        new_state.set(new_row, new_col, 'W');
        new_state.set(row, col, '.');
      } else if (new_state.get(row, col) == 'N') {
        new_state.set(new_row, new_col, 'W');
        new_state.set(row, col, 'D');
      } else {
        new_state.set(new_row, new_col, 'W');
        new_state.set(row, col, 'G');
      }

      // Update Sokoban Struct With New Values
      new_state.moves.append(update_move);
      new_state.cost_to_node += COST_MOVE;
      new_state.cost_to_goal = h1(new_state);
      new_state.f_score = new_state.cost_to_node + new_state.cost_to_goal;
      new_state.player_col = new_col;
      new_state.player_row = new_row;
      break;
    case 'J':
      // Move play to the new spot
      if ( new_state.get(row, col) == 'M' ) {
        new_state.set(new_row, new_col, 'M');
        new_state.set(row, col, '.');
      } else if (new_state.get(row, col) == 'N') {
        new_state.set(new_row, new_col, 'M');
        new_state.set(row, col, 'D');
      } else {
        new_state.set(new_row, new_col, 'M');
        new_state.set(row, col, 'G');
      }

      switch ( new_state.get(new_row_push, new_col_push) ) {
        case '.':
          if (deadlock_test_dynamic(new_state,new_col_push,new_row_push))
            no_move = true;
          else
            new_state.set(new_row_push, new_col_push, 'J');
          break;
        case 'G':
          new_state.set(new_row_push, new_col_push, 'I');
          break;
        case 'X':
        case 'J':
        case 'I':
        case 'D':
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
      }
      else
        new_state.map_state = "NO_MOVE";
  		break;
    case 'I':
      // Move play to the new spot
      if (new_state.get(row, col) == 'M') {
        new_state.set(new_row, new_col, 'W');
        new_state.set(row, col, '.');
      } else if (new_state.get(row, col) == 'N') {
        new_state.set(new_row, new_col, 'W');
        new_state.set(row, col, 'D');
      } else {
        new_state.set(new_row, new_col, 'W');
        new_state.set(row, col, 'G');
      }

      switch ( new_state.get(new_row_push, new_col_push) ) {
        case '.':
          if (deadlock_test_dynamic(new_state, new_col_push, new_row_push))
            no_move = true;
          else
            new_state.set(new_row_push, new_col_push, 'J');
          break;
        case 'G':
          new_state.set(new_row_push, new_col_push, 'I');
          break;
        case 'X':
        case 'J':
        case 'I':
        case 'D':
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
      } else {
        new_state.map_state = "NO_MOVE";
      }
      break;
    case 'X':
      new_state.map_state = "NO_MOVE";
      break;
    default:
      cout << "[error]  " << new_state.get(new_row, new_col) << " is a unknown puzzle type" << endl;
      break;
  }
  return new_state;
}

bool deadlock_test_dynamic(Soko_state state_current, int col, int row)
{
  char p1 = state_current.get(row-1,col+1);
  char p2 = state_current.get(row,col+1);
  char p3 = state_current.get(row+1,col+1);
  char p4 = state_current.get(row+1,col);
  char p5 = state_current.get(row+1,col-1);
  char p6 = state_current.get(row,col-1);
  char p7 = state_current.get(row-1,col-1);
  char p8 = state_current.get(row-1,col);

  // Check for against wall deadlock
  if (((p1 == 'X' && p2 == 'X' && p3 == 'X') && ( (p4 == 'J' || p4 == 'I') || (p8 == 'J' || p8 == 'I') )) ||
      ((p3 == 'X' && p4 == 'X' && p5 == 'X') && ( (p2 == 'J' || p2 == 'I') || (p6 == 'J' || p6 == 'I') )) ||
      ((p5 == 'X' && p6 == 'X' && p7 == 'X') && ( (p4 == 'J' || p4 == 'I') || (p8 == 'J' || p8 == 'I') )) ||
      ((p7 == 'X' && p8 == 'X' && p1 == 'X') && ( (p2 == 'J' || p2 == 'I') || (p6 == 'J' || p6 == 'I') )))
    return true;

  return false;
}

bool is_goal_state(Soko_state &state_current)
{
  size_t legal_chars = state_current.map_state.find_first_not_of("XI.MND\n");
  if(legal_chars != string::npos)
    return false;
  else
    return true;
}
