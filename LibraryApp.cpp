#include "LibraryApp.hpp"

void LibraryApp::runLibrary() {

  for (;;) {

    userinput.GetInput();
    Command command = userinput.ParseInput();

    if (command.fail) {
      cout << "\n             Log :             \n\r";
      cout << "-----------------------------------\n\r";

      // Failed Log
      for (int i = 0; i < command.error_log.size(); i++) {
        cout << ". ";
        cout << command.error_log[i] << "\n\r";
      }
      cout << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n";
      continue;
    }

    if (command.type == 4) {
      string input = string();
      cout << "Are You Sure About This ( " << services.m_books.size()
           << " books are being deleted ) [Y/n]";
      getline(cin, input);
      cout << "\n\r";
      if (input == "Y") {
        services.delete_condition(command.command["name"],
                                  command.command["author"],
                                  command.command["pages"]);
        cout << "\n             Log :             \n\r";
        cout << "-----------------------------------\n\r";
        cout << services.m_books.size() << " Books Successfully Deleted\n\r";
        cout << "\n\r";
        continue;
      } else {
        cout << "\n             Log :             \n\r";
        cout << "-----------------------------------\n\r";
        cout << "Delete Aborted\n\n\r";
        continue;
      }
    }
    if (command.type == 3) {
      string input = string();
      cout << "Are You Sure About This [Y/n]";
      getline(cin, input);
      cout << "\n\r";
      if (input == "Y") {
        services.delete_all_books();
        cout << "\n             Log :             \n\r";
        cout << "-----------------------------------\n\r";
        cout << "All Books Successfully Deleted\n\r";
        if (services.m_books.size() == 0) {
          cout << "(There was nothing to delete)\n\n\r";
          continue;
        }
        cout << "\n\r";
        continue;
      } else {
        cout << "\n             Log :             \n\r";
        cout << "-----------------------------------\n\r";
        cout << "Delete Aborted\n\n\r";
        continue;
      }
    }

    cout << "\n             Log :             \n\r";
    cout << "-----------------------------------\n\r";

    if (command.type == 1) {
      Book createe;
      createe.name = command.command["name"];
      createe.author = command.command["author"];
      createe.pages = command.command["pages"];
      services.create_book(createe);
      cout << "Book Successfully Created \n\n\r";
      continue;
    }

    if (command.type == 2) {
      if (services.m_books.count(command.id) == 0) {
        cout << ". ";
        cout << "That Id doesnt Exist\n\r";
        cout << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n";
        continue;
      }
      services.m_books.erase(command.id);
      cout << "Book Successfully Deleted \n\n\r";
    }

    if (command.type == 5) {
    }
  }
}
