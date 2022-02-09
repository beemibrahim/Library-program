#include "LibraryApp.hpp"
#include <sqlite/connection.hpp>
#include <sqlite/execute.hpp>
#include <sqlite/query.hpp>

int main(int argc, char *argv[]) {
  LibraryApp LibrarySim;
  LibrarySim.runLibrary(config);
}
