#include<iostream>


int main(int argc, char** argv)
{
  std::string usr_input;
  std::ifstream fs;
  std::string line;
  std::string input_level = "";

  //checks if argument exists, can't input level if no txt file
  if (argc != 2)
  {
    std::cerr << "  usage: " << argv[0] << "<sokoban_level>.txt"
      << std::endl;
    return 0;
  }

  //opens sokoban level txt file and store as string
  fs.open (argv[1]);
  if (!fs)
  {
    std::cerr << "  error opening file " << argv[1]
      << std::endl;
    return 0;
  }

  return 0;
}
