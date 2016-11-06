#include"heuristics.h"


// TODO: Make function that extracts box, and goal locations
// Manhattan distance between player and nearest box, and between the boxes and the goals.
int h1(const Soko_state &state_current)
{
	stringstream string_iterator(state_current.map_state);
	string current_line;
	vector< point > box_vector;
	vector< point > goal_vector;
	int hscore = 0, player2box_shortest = 1000, cur_row = 0;

	while (getline(string_iterator, current_line, '\n'))
	{
		for (int cur_col = 0; cur_col < state_current.width ; cur_col++)
		{
			if (current_line[cur_col] == 'W' || current_line[cur_col] == 'G')
			{
				point goal_point;
				goal_point.col = cur_col;
				goal_point.row = cur_row;
				goal_vector.push_back(goal_point);
			}
			//if box on floor, add to box list
			else if (current_line[cur_col] == 'J' )
			{
				point box_point;
				box_point.col = cur_col;
				box_point.row = cur_row;
				box_vector.push_back(box_point);
			}
			else if(current_line[cur_col] == 'I') // Keep boxes allready on a goal
				hscore -= 1000;
		}
		cur_row++;
	}

	//for each box on the floor, calculate the distance to each empty goal
	for (int i = 0; i < box_vector.size(); i++)
	{
		for (int j = 0; j < goal_vector.size(); j++)
		{
			//calculate distance of x and y cords
			int col_dist = box_vector[i].col - goal_vector[j].col;
			int row_dist = box_vector[i].row - goal_vector[j].row;
			//take absolute value of distance
			if (col_dist < 0)
				col_dist *= -1;
			if (row_dist < 0)
				row_dist *= -1;
			//add distance to score, lower hscore = better
			hscore += col_dist;
			hscore += row_dist;
		}
		//calculate player to box distances
		int player2box_col = box_vector[i].col - state_current.player_row;
		int player2box_row = box_vector[i].row - state_current.player_col;
		//take absolute value of distance
		if (player2box_col < 0)
			player2box_col *= -1;
		if (player2box_row < 0)
			player2box_row *= -1;
		//stores shortest distance to any box
		if (player2box_shortest > (player2box_row + player2box_col))
			player2box_shortest = (player2box_row + player2box_col);
	}
	hscore += player2box_shortest;
	return hscore;
}
