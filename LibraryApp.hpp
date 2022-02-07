#include "LibraryService.hpp"
#include "Userinput.hpp"
#include <exception>

struct ExtractRet {
  std::unordered_map<int, Book *> books;
  int last_id;
};

class LibraryApp {
public:
  void runLibrary(string config);

private:
  UserInput userinput;
  LibraryService *service;
  // for File Service
  ExtractRet extract();
};
