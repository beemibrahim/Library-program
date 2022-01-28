#include "LibraryApp.hpp"

void LibraryApp::runLibrary() {
  bool tru = false;
  Book *retr;
  services = LibraryService();
  services.extract();

  for (;;) {
    this->userinput = UserInput();
    std::cout.flush();
    Command command;
    userinput.GetInput();
    try {
      command = userinput.ParseInput();
    } catch (vector<string> errors) {
      cout << "\n             Log :             \n\r";
      cout << "-----------------------------------\n\r";

      for (int i = 0; i < errors.size(); i++) {
        cout << ". ";
        cout << errors[i] << "\n\r";
      }
      cout << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n";
      continue;
    }

    services.execute_command(command);
  }
}
