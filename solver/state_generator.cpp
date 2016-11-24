#include "state_generator.h"

queue<Soko_state> make_states(const Soko_state &state_current, string heuristics_type)
{
  /// Make moves
  queue<Soko_state> new_states;
  Soko_state move_state;
  // forward
  move_state = move( state_current, 'u' , heuristics_type);
  if (move_state.map_state != "NO_MOVE") {
    new_states.push( move_state );
  }
  // backward
  move_state = move( state_current, 'd' , heuristics_type);
  if (move_state.map_state != "NO_MOVE") {
    new_states.push( move_state );
  }
  // right
  move_state = move( state_current, 'r' , heuristics_type);
  if (move_state.map_state != "NO_MOVE") {
    new_states.push( move_state );
  }
  // left
  move_state = move( state_current, 'l' , heuristics_type);
  if (move_state.map_state != "NO_MOVE") {
    new_states.push( move_state );
  }
  return new_states;
}

Soko_state move(const Soko_state &state_current, char movement_type, string heuristics_type)
{
  Soko_state new_state = state_current;
  bool no_move = false;
  int new_row, new_col, new_row_push, new_col_push;
  int row = state_current.player_row, col = state_current.player_col;
  string update_move = "", update_move_push = "";

  int COST_MOVE = 1, COST_PUSH = 1;
  bool straight_reward = false;

  switch (movement_type) {
    case 'u':
      if (state_current.moves.back() == 'u' && straight_reward)
        COST_MOVE = 1;

      new_row = row-1;
      new_col = col;
      new_row_push = row-2;
      new_col_push = col;
      update_move = "u";
      update_move_push = "U";
      break;
    case 'd':
      if (state_current.moves.back() == 'd' && straight_reward)
        COST_MOVE = 1;

      new_row = row+1;
      new_col = col;
      new_row_push = row+2;
      new_col_push = col;
      update_move = "d";
      update_move_push = "D";
      break;
    case 'l':
      if (state_current.moves.back() == 'l' && straight_reward)
        COST_MOVE = 1;

      new_row = row;
      new_col = col-1;
      new_row_push = row;
      new_col_push = col-2;
      update_move = "l";
      update_move_push = "L";
      break;
    case 'r':
      if (state_current.moves.back() == 'r' && straight_reward)
        COST_MOVE = 1;

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

      if (heuristics_type == "h1")
        new_state.cost_to_goal = h1(new_state);
      else if (heuristics_type == "h2")
        new_state.cost_to_goal = h2(new_state);
      else if (heuristics_type == "h3")
        new_state.cost_to_goal = h3(new_state);
      else
        new_state.cost_to_goal = 0;

      new_state.f_score = new_state.cost_to_node + new_state.cost_to_goal;
      new_state.player_col = new_col;
      new_state.player_row = new_row;
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

      if (heuristics_type == "h1")
        new_state.cost_to_goal = h1(new_state);
      else if (heuristics_type == "h2")
        new_state.cost_to_goal = h2(new_state);
      else if (heuristics_type == "h3")
        new_state.cost_to_goal = h3(new_state);
      else
        new_state.cost_to_goal = 0;

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

      if (heuristics_type == "h1")
        new_state.cost_to_goal = h1(new_state);
      else if (heuristics_type == "h2")
        new_state.cost_to_goal = h2(new_state);
      else if (heuristics_type == "h3")
        new_state.cost_to_goal = h3(new_state);
      else
        new_state.cost_to_goal = 0;

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

        if (heuristics_type == "h1")
          new_state.cost_to_goal = h1(new_state);
        else if (heuristics_type == "h2")
          new_state.cost_to_goal = h2(new_state);
        else if (heuristics_type == "h3")
          new_state.cost_to_goal = h3(new_state);
        else
          new_state.cost_to_goal = 0;

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

        if (heuristics_type == "h1")
          new_state.cost_to_goal = h1(new_state);
        else if (heuristics_type == "h2")
          new_state.cost_to_goal = h2(new_state);
        else if (heuristics_type == "h3")
          new_state.cost_to_goal = h3(new_state);
        else
          new_state.cost_to_goal = 0;

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
      cout << "[error]  " << new_state.get(new_row, new_col) << " is a unknown puzzle type - Col: " << new_col << " Row: " << new_row << endl;
      break;
  }
  return new_state;
}
