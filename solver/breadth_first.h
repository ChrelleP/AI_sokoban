
#ifndef BREADTH_F
#define BREADTH_F

// Includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include "common.h"
#include "state_generator.h"
#include <unordered_map>
using namespace std;

typedef std::unordered_map<string, Soko_state> Mymap;

// Decleration
Soko_state breadth_first(Soko_state &init_state);

#endif
