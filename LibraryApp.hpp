#include "LibraryManager.hpp"
#include "Userinput.hpp"
#include <exception>

class LibraryApp {
public:
  void runLibrary();

private:
  UserInput userinput;
  LibraryService services;
};
