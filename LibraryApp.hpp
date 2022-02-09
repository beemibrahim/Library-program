#include "Library_DatabaseService.hpp"
#include "Userinput.hpp"
#include <exception>

struct ExtractRet {
  std::unordered_map<int, Book *> books;
  int last_id;
};

class LibraryApp {
public:
  void runLibrary();

private:
  UserInput userinput;
  LibraryDatabaseService *service;
  // for File Service
  ExtractRet extract();
};
