#ifndef STATE_GEN
#define STATE_GEN
// Includes
#include "common.h"

using namespace std;

// Decleration
queue<Soko_state> make_states(const Soko_state &cur_state);
Soko_state move(const Soko_state &cur_state, vector< vector<char> > map_vector, int x , int y, char movement_type);

#endif
