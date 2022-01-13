#include "Command.hpp"
#include <fstream>
#include <gtest/gtest.h>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
class UserInput {
public:
  Command ParseInput();
  void GetInput(string testing = "");

private:
  string readFileIntoString(const string &path);
  string input;
  void Remove_Spaces();
};
