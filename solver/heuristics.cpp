#include"heuristics.h"

// TODO: Make function that only asigns a goal once to the box closest to it

// Manhatten distance from each box to its closest goal
// Simple lower bound from rolling stone - underestimates the grossly in most cases
// The reason for this is that only one box can be on one goal
// Notice that this is a lower bound for the distance, we cannot solve the level faster
int h1(const Soko_state &state_current)
{
	vector< point > box_vector;
	vector< point > goal_vector;
	vector< point > boxgoal_vector;

	int hscore = 0, player2box_shortest = 500, closest_box2goal = 500;

	get_box_goal_positions( box_vector, goal_vector, boxgoal_vector, state_current.map_state );
	//hscore -= boxgoal_vector.size()*500;

	for (int i = 0; i < box_vector.size(); i++)
	{
		closest_box2goal = 500;
		for (int j = 0; j < goal_vector.size(); j++)
		{
			int manhatten_dist = abs(box_vector[i].col - goal_vector[j].col) + abs(box_vector[i].row - goal_vector[j].row);
			if (closest_box2goal > manhatten_dist)
				closest_box2goal = manhatten_dist;
		}
	}
	return hscore;
}

// Manhattan from each goal to each box
int h2(const Soko_state &state_current)
{
	vector< point > box_vector;
	vector< point > goal_vector;
	vector< point > boxgoal_vector;

	int hscore = 0, player2box_shortest = 500;

	get_box_goal_positions( box_vector, goal_vector, boxgoal_vector, state_current.map_state );
	//hscore -= boxgoal_vector.size()*500;

	for (int i = 0; i < box_vector.size(); i++)
		for (int j = 0; j < goal_vector.size(); j++)
			hscore += abs(box_vector[i].col - goal_vector[j].col) + abs(box_vector[i].row - goal_vector[j].row);

	return hscore;
}

// Manhattan distance between player and nearest box, and between the boxes and the goals.
// http://fragfrog.nl/papers/solving_the_sokoban_problem.pdf
int h3(const Soko_state &state_current)
{
	vector< point > box_vector;
	vector< point > goal_vector;
	vector< point > boxgoal_vector;

	int hscore = 0, player2box_shortest = 500;

	get_box_goal_positions( box_vector, goal_vector, boxgoal_vector, state_current.map_state );
	hscore -= boxgoal_vector.size()*500;

	for (int i = 0; i < box_vector.size(); i++)
	{
		for (int j = 0; j < goal_vector.size(); j++)
			hscore += abs(box_vector[i].col - goal_vector[j].col) + abs(box_vector[i].row - goal_vector[j].row);

		int player2box_manhatten_dist = abs(box_vector[i].col - state_current.player_row) + abs(box_vector[i].row - state_current.player_col);
		if (player2box_shortest > player2box_manhatten_dist)
			player2box_shortest = player2box_manhatten_dist;
	}
	hscore += player2box_shortest;
	return hscore;
}

void get_box_goal_positions(vector< point > &box_vector, vector< point > &goal_vector, vector< point > &boxgoal_vector, string map_state){
	stringstream string_iterator(map_state);
	string current_line;
	int cur_row = 0;

	while (getline(string_iterator, current_line, '\n'))
	{
		for (int cur_col = 0; cur_col < current_line.size() ; cur_col++)
		{
			if (current_line[cur_col] == 'W' || current_line[cur_col] == 'G') {
				point goal_point;
				goal_point.col = cur_col;
				goal_point.row = cur_row;
				goal_vector.push_back(goal_point);
			}
			else if (current_line[cur_col] == 'J' ) {
				point box_point;
				box_point.col = cur_col;
				box_point.row = cur_row;
				box_vector.push_back(box_point);
			}
			else if(current_line[cur_col] == 'I') {
				point goalbox_point;
				goalbox_point.col = cur_col;
				goalbox_point.row = cur_row;
				boxgoal_vector.push_back(goalbox_point);
			}
		}
		cur_row++;
	}
}
