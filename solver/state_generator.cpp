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
  map_vector.resize( current_state.width , vector<char>( current_state.height , 'Q' ) );
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
  int new_row, new_col, new_row_push, new_col_push;
  string update_moves = "";

  // For forward
  switch (movement_type) {
    case 'f':
      new_row = row-1;
      new_col = col;
      new_row_push = row-2;
      new_col_push = col;
      update_moves = "f";
      break;
    case 'b':
      new_row = row+1;
      new_col = col;
      new_row_push = row+2;
      new_col_push = col;
      update_moves = "b";
      break;
    case 'l':
      new_row = row;
      new_col = col-1;
      new_row_push = row;
      new_col_push = col-2;
      update_moves = "l";
      break;
    case 'r':
      new_row = row;
      new_col = col+1;
      new_row_push = row;
      new_col_push = col+2;
      update_moves = "r";
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
      new_state.moves.append(update_moves);

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
      new_state.moves.append(update_moves);

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
      if (!no_move) {
        // Update moves list with forward move
        new_state.moves.append(update_moves);

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
      if (!no_move) {
        // Update moves list with forward move
        new_state.moves.append(update_moves);

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
