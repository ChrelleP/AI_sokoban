#include"heuristics.h"

// TODO: Make function that only asigns a goal once to the box closest to it

// TODO: Make function that extracts box, and goal locations
// This is called: Simple lower bound!
int h1(const Soko_state &state_current)
{
	vector< point > box_vector;
	vector< point > goal_vector;
	vector< point > boxgoal_vector;

	int hscore = 0, player2box_shortest = 500, closest_box2goal = 500;

	get_box_goal_positions( box_vector, goal_vector, boxgoal_vector, state_current.map_state );
	hscore -= boxgoal_vector.size()*500;

	for (int i = 0; i < box_vector.size(); i++)
	{
		closest_box2goal = 500;
		for (int j = 0; j < goal_vector.size(); j++)
		{
			int col_dist = box_vector[i].col - goal_vector[j].col;
			int row_dist = box_vector[i].row - goal_vector[j].row;
			if (col_dist < 0)
				col_dist *= -1;
			if (row_dist < 0)
				row_dist *= -1;
			if (closest_box2goal > ( col_dist + row_dist ))
				closest_box2goal = (col_dist + row_dist);
		}
		hscore += closest_box2goal;
		int player2box_col = box_vector[i].col - state_current.player_row;
		int player2box_row = box_vector[i].row - state_current.player_col;
		if (player2box_col < 0)
			player2box_col *= -1;
		if (player2box_row < 0)
			player2box_row *= -1;
		if (player2box_shortest > (player2box_row + player2box_col))
			player2box_shortest = (player2box_row + player2box_col);
	}
	hscore += player2box_shortest;
	return hscore;
}

// Manhattan distance between player and nearest box, and between the boxes and the goals.
int h2(const Soko_state &state_current)
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
		{
			int col_dist = box_vector[i].col - goal_vector[j].col;
			int row_dist = box_vector[i].row - goal_vector[j].row;
			if (col_dist < 0)
				col_dist *= -1;
			if (row_dist < 0)
				row_dist *= -1;
			hscore += col_dist;
			hscore += row_dist;
		}
		int player2box_col = box_vector[i].col - state_current.player_row;
		int player2box_row = box_vector[i].row - state_current.player_col;
		if (player2box_col < 0)
			player2box_col *= -1;
		if (player2box_row < 0)
			player2box_row *= -1;
		if (player2box_shortest > (player2box_row + player2box_col))
			player2box_shortest = (player2box_row + player2box_col);
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

// dDDRluurrruulDrddddlluluurRurDDDuullluRdlddlluuuRRdrrrddLLLLdlUUdrruurrruulDrdddllluuuRdlddrrruuLLulDDurrrddllLLdlUdrRurrruuuulDrdLLulDDurrrddllLdlluRRRluurrrddLdLruruulllddR H2A*
// dDDRluurrruulDrddddlluluurRurDDDuullluRdlddlluuuRRdrrrddLLLLdlUUdrruurrruulDrdddllluuuRdlddrrruuLLulDDurrrddllLLdlUdrRurrruuuulDrdLLulDDurrrddllLdlluRRRluurrrddLdLruruulllddR H1A*
// dDDRluurrruulDrddddlluluurRurDDDuullluRdlddlluuuRRdrrrddLLLLdlUUdrruurrruulDrdddllluuuRdlddrrruuLLulDDurrrddllLLdlUdrRurrruuuulDrdLLulDDurrrddllLdlluRRRluurrrddLdLruruulllddR

// drddlllUdLdlluRRRRRdrUUruulldRRdldlllllURuulDDrddlluRRRRRdrUUruurrdLulDulldRddlluLdlluurDldRRRRdrUUUluRdddlllluuurDDldRRRdrUU H2A*
// drddlllLdlluRRRRRdrUUruulldRRdldlllUdllURuulDDrddlluRRRRRdrUUruurrdLulDulldRddlluLdlluurDldRRRRdrUUUluRdddlllluuurDDldRRRdrUU H1A*
// drddlllLUddlluRRRRRdrUUruulldRRdldlluLuulldRurDDullDRdRRRdrUUruurrdLulDulldRddlllluurDldRRRdrUUUluRdddlllldlluRRRRRdrUU
