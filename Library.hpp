#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

class book {
public:
  int id = 0;
  string name;
  string author;
  int pages = 0;
};

class Command {
public:
  bool worked = false;
  // find book = 1
  // create = 2
  // find_everything = 3
  // update book = 4
  // delete everything = 5
  // delete book = 6
  int command_type = 0;
  string command;
  bool id_gon;
  bool name_gon;
  bool author_gon;
  bool page_gon;
  int id = 0;
  string name;
  string author;
  int pages = 0;
  // Only for update
  bool name2;
  bool author2;
  bool pages2;
};

class UserInput {
public:
  Command GetInput(vector<book> books);

private:
  string SpaceRemover_for_update(string once);
  int last_id = 0;
  void Remove_All_Spaces();
  string input_store;
};

// Main class for the Library
class Library {
public:
  void library_intro();
  UserInput input;
  Command command;
  void create(); // need to take a library
  void delete_();
  void update();
  void delete_everything();
  void find_everything();
  void find();
  vector<book> books;
};

class Library_Application {
  UserInput user_input;
  Library library;

public:
  void PrintOutput();
};
