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

	int closest_box2goal, hscore = 0;

	get_box_goal_positions( box_vector, goal_vector, boxgoal_vector, state_current );
	//hscore -= boxgoal_vector.size()*500;

	for (int i = 0; i < box_vector.size(); i++)
	{
		closest_box2goal = 5000;
		for (int j = 0; j < goal_vector.size(); j++)
		{
			int manhatten_dist = abs(box_vector[i].col - goal_vector[j].col) + abs(box_vector[i].row - goal_vector[j].row);
			if (closest_box2goal > manhatten_dist)
				closest_box2goal = manhatten_dist;
		}
		hscore += closest_box2goal;
	}
	return hscore;
}

// Manhattan from each goal to each box
int h2(const Soko_state &state_current)
{
	vector< point > box_vector;
	vector< point > goal_vector;
	vector< point > boxgoal_vector;

	int hscore = 0;

	get_box_goal_positions( box_vector, goal_vector, boxgoal_vector, state_current );

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

	get_box_goal_positions( box_vector, goal_vector, boxgoal_vector, state_current );
	//hscore -= boxgoal_vector.size()*500;

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

// Manhattan distance between player and nearest box, and between the boxes and the closest goal.
// Goal can only be assigned once
int h4(const Soko_state &state_current)
{
	vector< point > box_vector;
	vector< point > goal_vector;
	vector< point > boxgoal_vector;

	int hscore = 0, player2box_shortest = 500;

	get_box_goal_positions( box_vector, goal_vector, boxgoal_vector, state_current );
	//hscore -= boxgoal_vector.size()*500;

	for (int i = 0; i < box_vector.size(); i++)
	{
		int player2box_manhatten_dist = abs(box_vector[i].col - state_current.player_row) + abs(box_vector[i].row - state_current.player_col);
		if (player2box_shortest > player2box_manhatten_dist)
			player2box_shortest = player2box_manhatten_dist;
	}
	hscore += player2box_shortest;

	int closest_box2goal;
	for (int i = 0; i < box_vector.size(); i++)
	{
		closest_box2goal = 1000;
		for (int j = 0; j < goal_vector.size(); j++)
		{
			int manhatten_dist = abs(box_vector[i].col - goal_vector[j].col) + abs(box_vector[i].row - goal_vector[j].row);
			if (closest_box2goal > manhatten_dist)
			{
				closest_box2goal = manhatten_dist;
				goal_vector[j].col = 10000;
				goal_vector[j].row = 10000;
			}
		}
		hscore += closest_box2goal;
	}

	return hscore;
}

int h5(const Soko_state &state_current)
{
	vector< point > box_vector;
	vector< point > goal_vector;
	vector< point > boxgoal_vector;

	int hscore = 0, player2box_shortest = 500, closest_box2goal = 5000;

	get_box_goal_positions( box_vector, goal_vector, boxgoal_vector, state_current );

	for (int i = 0; i < box_vector.size(); i++)
	{
		closest_box2goal = 5000;
		for (int j = 0; j < goal_vector.size(); j++)
		{
			int manhatten_dist = abs(box_vector[i].col - goal_vector[j].col) + abs(box_vector[i].row - goal_vector[j].row);
			if (closest_box2goal > manhatten_dist)
				closest_box2goal = manhatten_dist;
		}
		hscore += closest_box2goal;

		int player2box_manhatten_dist = abs(box_vector[i].col - state_current.player_row) + abs(box_vector[i].row - state_current.player_col);
		if (player2box_shortest > player2box_manhatten_dist)
			player2box_shortest = player2box_manhatten_dist;
	}
	hscore += player2box_shortest;
	return hscore;
}

int h6(const Soko_state &state_current)
{
	vector< point > box_vector;
	vector< point > goal_vector;
	vector< point > boxgoal_vector;

	int hscore = 0, player2box_shortest = 500, closest_box2goal = 5000;

	get_box_goal_positions( box_vector, goal_vector, boxgoal_vector, state_current );
	dlib::matrix<int> cost( state_current.num_of_goals-boxgoal_vector.size(), state_current.num_of_goals-boxgoal_vector.size() );

	//hscore -= boxgoal_vector.size()*500;

	for (int i = 0; i < box_vector.size(); i++)
	{
		closest_box2goal = 5000;
		for (int j = 0; j < goal_vector.size(); j++)
			cost(i,j) = -1*(abs(box_vector[i].col - goal_vector[j].col) + abs(box_vector[i].row - goal_vector[j].row));

		int player2box_manhatten_dist = abs(box_vector[i].col - state_current.player_row) + abs(box_vector[i].row - state_current.player_col);
		if (player2box_shortest > player2box_manhatten_dist)
			player2box_shortest = player2box_manhatten_dist;
	}
	//cout << cost << endl;
	std::vector<long> assignment = max_cost_assignment(cost);
	hscore += (-1*dlib::assignment_cost(cost,assignment));
	hscore += player2box_shortest;
	return hscore;
}


void get_box_goal_positions(vector< point > &box_vector, vector< point > &goal_vector, vector< point > &boxgoal_vector, Soko_state state_current){
	for (int col = 0; col < state_current.width; col++) {
		for (int row = 0; row < state_current.height; row++) {
			char tmp = state_current.get(row,col);
			switch ( tmp ) {
				case 'W':
				case 'G':
					point goal_point;
					goal_point.col = col;
					goal_point.row = row;
					goal_vector.push_back(goal_point);
					break;
				case 'J':
					point box_point;
					box_point.col = col;
					box_point.row = row;
					box_vector.push_back(box_point);
					break;
				case 'I':
					point goalbox_point;
					goalbox_point.col = col;
					goalbox_point.row = row;
					boxgoal_vector.push_back(goalbox_point);
					break;
			}
		}
	}
}
