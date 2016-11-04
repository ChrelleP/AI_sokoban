// ************ Interface between solver and robot ****************
// Solver solutions include:  u: up     |   U: up while pushing
//                            d: down   |   D: down while pushing
//                            l: left   |   L: Left while pushing
//                            r: right  |   R: Right while pushing
//
// Robot commands include:    F = Forward
//                            R = Right
//                            L = Left
//                            D = Deploy in front of the robot
// ****************************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <deque>

#define UP      1
#define RIGHT   2
#define DOWN    3
#define LEFT    4


using namespace std;

int main(int argc, char* argv[]) {

   if (argc > 3 || argc < 2){
     cout << "Please input a string of commands" << endl;
     cout << "Terminating..." << endl;
     return 1;
   }

   // Orientation of the robot | 1 = up, 2 = right, 3 = down, 4 = left;
   int rob_ori;
   string solver_plan = argv[1];
   string robot_plan = "";
   char current_command = ' ';
   char next_command = ' ';

   bool pushing = false;
   bool plan_complete = false;

   solver_plan += "s"; // s for stop
   cout << "Input solver plan: " << solver_plan << endl;

   switch(solver_plan.at(0)){
     case 'u': case 'U':
        rob_ori = UP;
        cout << "PLACE ROBOT IN AN UPWARDS DIRECTION" << endl;
        break;
     case 'r': case 'R':
        rob_ori = RIGHT;
        cout << "PLACE ROBOT IN A RIGHT DIRECTION" << endl;
        break;
     case 'd': case 'D':
        rob_ori = DOWN;
        cout << "PLACE ROBOT IN A DOWNWARDS DIRECTION" << endl;
        break;
     case 'l': case 'L':
        rob_ori = LEFT;
        cout << "PLACE ROBOT IN A LEFT DIRECTION" << endl;
        break;
   }

   while(!plan_complete){
      if(solver_plan.at(0) == 's'){
        plan_complete = true;
      }
      else{
        current_command = solver_plan.at(0);

        switch(current_command){
          case 'u': case 'U':
            switch(rob_ori){
              case UP:
                robot_plan.append("F");
                break;
              case RIGHT:
                robot_plan.append("L");
                break;
              case LEFT:
                robot_plan.append("R");
                break;
              case DOWN: // ILLEGAL STATE - SHOULD NEVER HAPPEN
                //robot_plan.append("");
                break;
              default:
                break;
            }
            rob_ori = UP;
            break;
          case 'r': case 'R':
            switch(rob_ori){
              case UP:
                robot_plan.append("R");
                break;
              case RIGHT:
                robot_plan.append("F");
                break;
              case LEFT: // ILLEGAL STATE - SHOULD NEVER HAPPEN
                //robot_plan.append("");
                break;
              case DOWN:
                robot_plan.append("L");
                break;
              default:
                break;
            }
            rob_ori = RIGHT;
            break;
          case 'd': case 'D':
            switch(rob_ori){
              case UP: // ILLEGAL STATE - SHOULD NEVER HAPPEN
                // robot_plan.append("");
                break;
              case RIGHT:
                robot_plan.append("R");
                break;
              case LEFT:
                robot_plan.append("L");
                break;
              case DOWN:
                robot_plan.append("F");
                break;
              default:
                break;
            }
            rob_ori = DOWN;
            break;
          case 'l': case 'L':
            switch(rob_ori){
              case UP:
                robot_plan.append("L");
                break;
              case RIGHT: // ILLEGAL STATE - SHOULD NEVER HAPPEN
                // robot_plan.append("");
                break;
              case LEFT:
                robot_plan.append("F");
                break;
              case DOWN:
                robot_plan.append("R");
                break;
              default:
                break;
            }
            rob_ori = LEFT;
            break;
        }

        next_command = solver_plan.at(1);
        if(isupper(current_command) && islower(next_command)){
          robot_plan.append("D");
          switch(rob_ori){
            case UP:
              rob_ori = DOWN;
              break;
            case RIGHT:
              rob_ori = LEFT;
              break;
            case DOWN:
              rob_ori = UP;
              break;
            case LEFT:
              rob_ori = RIGHT;
              break;
          }
        }

        solver_plan.erase(solver_plan.begin());
      }
   }

    cout << "Output robot plan: " << robot_plan << endl;

   return 0;
}
