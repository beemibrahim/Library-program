#include "LibraryApp.hpp"
#include <sqlite/connection.hpp>
#include <sqlite/execute.hpp>
#include <sqlite/query.hpp>

int main(int argc, char *argv[]) {
  string config;
  if (argc == 1) {
    config = "m";
    std::cout << "Your now using the in-memory library\n\n";

    LibraryApp LibrarySim;
    LibrarySim.runLibrary(config);
  }
  if (argc > 2) {
    std::cout << "You cant have more than one argument\n\r";
    return -1;
  }
  if (argc == 2) {
    std::string files = "files";
    std::string data = "data";
    if (argv[1] == files) {
      config = "f";
      std::cout << "Your now using the in-files library\n\n";
    }
    if (argv[1] == data) {
      sqlite::connection con("data/library.db");
      sqlite::execute(
          con,
          "CREATE TABLE IF NOT EXISTS library(id INTEGER PRIMARY KEY, "
          "name varchar(255) , author varchar(255) , pages int);",
          true);

      config = "d";
      std::cout << "Your now using the in-databases library\n\n";
    }
  }
  LibraryApp LibrarySim;
  LibrarySim.runLibrary(config);
}
