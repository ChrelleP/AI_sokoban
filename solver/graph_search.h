#ifndef GRAPH_S
#define GRAPH_S

// Includes
#include "state_generator.h"
#include <unordered_map>
using namespace std;

typedef std::unordered_map<string, Soko_state> MyOpen;
typedef std::unordered_map<string, char> MyClosed;

// Decleration
Soko_state graph_search(Soko_state &init_state, string search_type, string heuristics_type);
bool is_goal_state(Soko_state &state_current);

#endif
