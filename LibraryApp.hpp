#include "LibraryManager.hpp"
#include "Userinput.hpp"
class LibraryApp {
public:
  void runLibrary();

private:
  UserInput userinput;
  LibraryService services;
};
