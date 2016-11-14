#ifndef STATE_GEN
#define STATE_GEN
// Includes
#include <queue>
#include <deque>
#include "initializer.h"

using namespace std;

// Decleration
queue<Soko_state> make_states(const Soko_state &current_state);
Soko_state move(const Soko_state &cur_state, char movement_type);
bool deadlock_test_dynamic(Soko_state cur_state, int x, int y);

#endif
