#ifndef STATE_GEN
#define STATE_GEN
// Includes
#include "common.h"
#include <boost/functional/hash.hpp>

using namespace std;

// Decleration
queue<Soko_state> make_states(const Soko_state &current_state);
Soko_state move(const Soko_state &cur_state, vector< vector<char> > map_vector, char movement_type);
bool deadlock_test(vector< vector<char> > map_vector, int x, int y);
vector<vector<char>> string2vecmap(Soko_state input_state);
void vecmap2string (Soko_state &input_state, vector<vector<char>> &input_vecvec);
#endif
