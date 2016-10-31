
#ifndef A_STAR
#define A_STAR

// Includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include "common.h"
#include "state_generator.h"
#include <assert.h>
#include <unordered_map>

using namespace std;
typedef std::unordered_map<string, Soko_state> Mymap;

// Decleration
Soko_state a_star(Soko_state &state_init);

#endif
