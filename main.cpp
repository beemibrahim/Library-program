#include "Library.hpp"

#include <string>
#include <vector>

void Library_MainPart() {
  Library library;
  library.library_intro();
  for (;;) {
    printf("\n");
    library.command = library.input.GetInput(library.books);
    if (library.command.worked == false) {
      continue;
    }
    if (library.command.command_type == 1) {
      library.find();
      continue;
    }
    if (library.command.command_type == 2) {
      library.create();
      continue;
    }
    if (library.command.command_type == 3) {
      library.find_everything();
      continue;
    }
    if (library.command.command_type == 4) {
      library.update();
      continue;
    }
    if (library.command.command_type == 5) {
      library.delete_everything();
      continue;
    }
    if (library.command.command_type == 6) {
      library.delete_();
      continue;
    }
  }
}

int main() { Library_MainPart(); }
