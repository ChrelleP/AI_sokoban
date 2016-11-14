#ifndef GRAPH_S
#define GRAPH_S

// Includes
#include "state_generator.h"
#include <unordered_map>
using namespace std;

typedef std::unordered_map<string, Soko_state> Mymap;

// Decleration
Soko_state graph_search(Soko_state &init_state, string search_type);
void breadth_first_queuing(Mymap &hash_map_open, Soko_state &state_current_successors, deque<Soko_state> &open_set);
void a_star_queuing(Mymap &hash_map_open, Soko_state &state_current_successors, deque<Soko_state> &open_set);
bool is_goal_state(Soko_state &state_current);

#endif
