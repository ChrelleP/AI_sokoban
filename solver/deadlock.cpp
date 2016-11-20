#include "deadlock.h"

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

  // Check against wall and besides box deadlock
  if (((p1 == 'X' && p2 == 'X' && p3 == 'X') && ( (p4 == 'J' || p4 == 'I') || (p8 == 'J' || p8 == 'I') )) ||
      ((p3 == 'X' && p4 == 'X' && p5 == 'X') && ( (p2 == 'J' || p2 == 'I') || (p6 == 'J' || p6 == 'I') )) ||
      ((p5 == 'X' && p6 == 'X' && p7 == 'X') && ( (p4 == 'J' || p4 == 'I') || (p8 == 'J' || p8 == 'I') )) ||
      ((p7 == 'X' && p8 == 'X' && p1 == 'X') && ( (p2 == 'J' || p2 == 'I') || (p6 == 'J' || p6 == 'I') )))
    return true;

  return false;
}

//http://www.lamsade.dauphine.fr/~cazenave/papers/sokoban.pdf
void deadlock_tester_static(Soko_state &init_state)
{
  char p1,p2,p3,p4,p5,p6,p7,p8;
  int row_tmp = 0, col_tmp = 0;

  for (int row = 1; row < init_state.height-1; row++) {
    for (int col = 1; col < init_state.width-1; col++) {
      p1 = init_state.get(row-1,col+1);
      p2 = init_state.get(row,col+1);
      p3 = init_state.get(row+1,col+1);
      p4 = init_state.get(row+1,col);
      p5 = init_state.get(row+1,col-1);
      p6 = init_state.get(row,col-1);
      p7 = init_state.get(row-1,col-1);
      p8 = init_state.get(row-1,col);

      // DEADLOCK CORNER TESTS:
      row_tmp = row;
      col_tmp = col;

      if (p8 == 'X' && p2 == 'X') {

        if (init_state.get(row,col) == '.' || init_state.get(row,col) == 'M') {
          if ( init_state.get(row,col) == 'M') {
            init_state.set(row,col,'N');
          } else init_state.set(row,col,'D');
          // HORISONTAL RIGHT TOP CORNER
          bool clean_wall = false;
          while ( init_state.get(row_tmp-1,col_tmp) == 'X' &&
                ( init_state.get(row_tmp,col_tmp) == '.' || init_state.get(row_tmp,col_tmp) == 'D' || init_state.get(row_tmp,col_tmp) == 'M' || init_state.get(row_tmp,col_tmp) == 'N') ) {
            if (init_state.get(row_tmp,col_tmp-1) == 'X') {
              row_tmp = row;
              col_tmp = col;
              clean_wall = true;
              break;
            } else col_tmp--; }

          while ( init_state.get(row_tmp-1,col_tmp) == 'X' &&
                ( init_state.get(row_tmp,col_tmp) == '.' || init_state.get(row_tmp,col_tmp) == 'D' || init_state.get(row_tmp,col_tmp) == 'M' || init_state.get(row_tmp,col_tmp) == 'N') ) {
            if ( init_state.get(row_tmp,col_tmp) == 'M') {
              init_state.set(row_tmp,col_tmp,'N');
            } else if ( init_state.get(row_tmp,col_tmp) == '.')
              init_state.set(row_tmp,col_tmp,'D');
            col_tmp--; }

          // VERTICAL LEFT TOP CORNER
          row_tmp = row;
          col_tmp = col;
          clean_wall = false;
          while ( init_state.get(row_tmp,col_tmp+1) == 'X' &&
                ( init_state.get(row_tmp,col_tmp) == '.' || init_state.get(row_tmp,col_tmp) == 'D' || init_state.get(row_tmp,col_tmp) == 'M' || init_state.get(row_tmp,col_tmp) == 'N') ) {
            if (init_state.get(row_tmp+1,col_tmp) == 'X') {
              row_tmp = row;
              col_tmp = col;
              clean_wall = true;
              break;
            } else row_tmp++; }

          while ( init_state.get(row_tmp,col_tmp+1) == 'X' &&
                ( init_state.get(row_tmp,col_tmp) == '.' || init_state.get(row_tmp,col_tmp) == 'D' || init_state.get(row_tmp,col_tmp) == 'M' || init_state.get(row_tmp,col_tmp) == 'N') ) {
            if ( init_state.get(row_tmp,col_tmp) == 'M') {
              init_state.set(row_tmp,col_tmp,'N');
            } else if ( init_state.get(row_tmp,col_tmp) == '.')
              init_state.set(row_tmp,col_tmp,'D');
            row_tmp++; }
        }

      } else if (p2 == 'X' && p4 == 'X') {
        if (init_state.get(row,col) == '.' || init_state.get(row,col) == 'M') {
          if ( init_state.get(row,col) == 'M') {
            init_state.set(row,col,'N');
          } else init_state.set(row,col,'D');
          // HORISONTAL RIGHT BOTTOM CORNER
          bool clean_wall = false;
          while ( init_state.get(row_tmp+1,col_tmp) == 'X' &&
                ( init_state.get(row_tmp,col_tmp) == '.' || init_state.get(row_tmp,col_tmp) == 'D' || init_state.get(row_tmp,col_tmp) == 'M' || init_state.get(row_tmp,col_tmp) == 'N') ) {
            if (init_state.get(row_tmp,col_tmp-1) == 'X') {
              row_tmp = row;
              col_tmp = col;
              clean_wall = true;
              break;
            } else col_tmp--; }

          while ( init_state.get(row_tmp+1,col_tmp) == 'X' &&
                ( init_state.get(row_tmp,col_tmp) == '.' || init_state.get(row_tmp,col_tmp) == 'D' || init_state.get(row_tmp,col_tmp) == 'M' || init_state.get(row_tmp,col_tmp) == 'N') ) {
            if ( init_state.get(row_tmp,col_tmp) == 'M') {
              init_state.set(row_tmp,col_tmp,'N');
            } else if ( init_state.get(row_tmp,col_tmp) == '.')
              init_state.set(row_tmp,col_tmp,'D');
            col_tmp--; }

          // VERTICAL LEFT BOTTOM CORNER
          row_tmp = row;
          col_tmp = col;
          clean_wall = false;
          while ( init_state.get(row_tmp,col_tmp+1) == 'X' &&
                ( init_state.get(row_tmp,col_tmp) == '.' || init_state.get(row_tmp,col_tmp) == 'D' || init_state.get(row_tmp,col_tmp) == 'M' || init_state.get(row_tmp,col_tmp) == 'N') ) {
            if (init_state.get(row_tmp-1,col_tmp) == 'X') {
              row_tmp = row;
              col_tmp = col;
              clean_wall = true;
              break;
            } else row_tmp--; }

          while ( init_state.get(row_tmp,col_tmp+1) == 'X' &&
                ( init_state.get(row_tmp,col_tmp) == '.' || init_state.get(row_tmp,col_tmp) == 'D' || init_state.get(row_tmp,col_tmp) == 'M' || init_state.get(row_tmp,col_tmp) == 'N') ) {
            if ( init_state.get(row_tmp,col_tmp) == 'M') {
              init_state.set(row_tmp,col_tmp,'N');
            } else if ( init_state.get(row_tmp,col_tmp) == '.')
              init_state.set(row_tmp,col_tmp,'D');
            row_tmp--; }
        }
      } else if (p4 == 'X' && p6 == 'X') {
        if (init_state.get(row,col) == '.' || init_state.get(row,col) == 'M') {
          if ( init_state.get(row,col) == 'M') {
            init_state.set(row,col,'N');
          } else init_state.set(row,col,'D');
          // HORISONTAL LEFT BOTTOM CORNER
          bool clean_wall = false;
          while ( init_state.get(row_tmp+1,col_tmp) == 'X' &&
                ( init_state.get(row_tmp,col_tmp) == '.' || init_state.get(row_tmp,col_tmp) == 'D' || init_state.get(row_tmp,col_tmp) == 'M' || init_state.get(row_tmp,col_tmp) == 'N') ) {
            if (init_state.get(row_tmp,col_tmp+1) == 'X') {
              row_tmp = row;
              col_tmp = col;
              clean_wall = true;
              break;
            } else col_tmp++; }

          while ( init_state.get(row_tmp+1,col_tmp) == 'X' &&
                ( init_state.get(row_tmp,col_tmp) == '.' || init_state.get(row_tmp,col_tmp) == 'D' || init_state.get(row_tmp,col_tmp) == 'M' || init_state.get(row_tmp,col_tmp) == 'N') ) {
            if ( init_state.get(row_tmp,col_tmp) == 'M') {
              init_state.set(row_tmp,col_tmp,'N');
            } else if ( init_state.get(row_tmp,col_tmp) == '.')
              init_state.set(row_tmp,col_tmp,'D');
            col_tmp++; }

          // VERTICAL LEFT BOTTOM CORNER
          row_tmp = row;
          col_tmp = col;
          clean_wall = false;
          while ( init_state.get(row_tmp,col_tmp-1) == 'X' &&
                ( init_state.get(row_tmp,col_tmp) == '.' || init_state.get(row_tmp,col_tmp) == 'D' || init_state.get(row_tmp,col_tmp) == 'M' || init_state.get(row_tmp,col_tmp) == 'N') ) {
            if (init_state.get(row_tmp-1,col_tmp) == 'X') {
              row_tmp = row;
              col_tmp = col;
              clean_wall = true;
              break;
            } else row_tmp--; }

          while ( init_state.get(row_tmp,col_tmp-1) == 'X' &&
                ( init_state.get(row_tmp,col_tmp) == '.' || init_state.get(row_tmp,col_tmp) == 'D' || init_state.get(row_tmp,col_tmp) == 'M' || init_state.get(row_tmp,col_tmp) == 'N') ) {
            if ( init_state.get(row_tmp,col_tmp) == 'M') {
              init_state.set(row_tmp,col_tmp,'N');
            } else if ( init_state.get(row_tmp,col_tmp) == '.')
              init_state.set(row_tmp,col_tmp,'D');
            row_tmp--; }
        }
      } else if (p6 == 'X' && p8 == 'X') {
        if (init_state.get(row,col) == '.' || init_state.get(row,col) == 'M') {
          if ( init_state.get(row,col) == 'M') {
            init_state.set(row,col,'N');
          } else init_state.set(row,col,'D');

          // HORISONTAL LEFT TOP CORNER
          bool clean_wall = false;
          while ( init_state.get(row_tmp-1,col_tmp) == 'X' &&
                ( init_state.get(row_tmp,col_tmp) == '.' || init_state.get(row_tmp,col_tmp) == 'D' || init_state.get(row_tmp,col_tmp) == 'M' || init_state.get(row_tmp,col_tmp) == 'N') ) {
            if (init_state.get(row_tmp,col_tmp+1) == 'X') {
              row_tmp = row;
              col_tmp = col;
              clean_wall = true;
              break;
            } else col_tmp++; }

          while ( init_state.get(row_tmp-1,col_tmp) == 'X' &&
                ( init_state.get(row_tmp,col_tmp) == '.' || init_state.get(row_tmp,col_tmp) == 'D' || init_state.get(row_tmp,col_tmp) == 'M' || init_state.get(row_tmp,col_tmp) == 'N') ) {
            if ( init_state.get(row_tmp,col_tmp) == 'M') {
              init_state.set(row_tmp,col_tmp,'N');
            } else if ( init_state.get(row_tmp,col_tmp) == '.')
              init_state.set(row_tmp,col_tmp,'D');
            col_tmp++; }

          // VERTICAL LEFT TOP CORNER
          row_tmp = row;
          col_tmp = col;
          clean_wall = false;
          while ( init_state.get(row_tmp,col_tmp-1) == 'X' &&
                ( init_state.get(row_tmp,col_tmp) == '.' || init_state.get(row_tmp,col_tmp) == 'D' || init_state.get(row_tmp,col_tmp) == 'M' || init_state.get(row_tmp,col_tmp) == 'N') ) {
            if (init_state.get(row_tmp+1,col_tmp) == 'X') {
              row_tmp = row;
              col_tmp = col;
              clean_wall = true;
              break;
            } else row_tmp++; }

          while ( init_state.get(row_tmp,col_tmp-1) == 'X' &&
                ( init_state.get(row_tmp,col_tmp) == '.' || init_state.get(row_tmp,col_tmp) == 'D' || init_state.get(row_tmp,col_tmp) == 'M' || init_state.get(row_tmp,col_tmp) == 'N') ) {
            if ( init_state.get(row_tmp,col_tmp) == 'M') {
              init_state.set(row_tmp,col_tmp,'N');
            } else if ( init_state.get(row_tmp,col_tmp) == '.')
              init_state.set(row_tmp,col_tmp,'D');
            row_tmp++; }

        }
      }
    }
  }
}
