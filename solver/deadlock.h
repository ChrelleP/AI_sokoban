#ifndef DEADLOCK
#define DEADLOCK
// Includes
#include "soko_state.h"

using namespace std;

bool deadlock_test_dynamic(Soko_state cur_state, int x, int y);
void deadlock_tester_static(Soko_state &init_state);

#endif
