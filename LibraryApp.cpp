#include "LibraryApp.hpp"

void LibraryApp::runLibrary() {
  bool tru = false;
  Book *retr;
  for (;;) {
    this->userinput = UserInput();
    std::cout.flush();

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

    if (command.type == 6) {
      unordered_map<int, Book *>::iterator it = services.m_books.begin();
      if (services.m_books.size() == 0) {
        cout << "\n             Log :             \n\r";
        cout << "-----------------------------------\n\r";

        cout << ". ";
        cout << "No Books are created\n\r";
        cout << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n\r";
        continue;
      }
      cout << "\n             Books :             \n\r";
      cout << "-----------------------------------\n\n\r";
      int num = 1;
      for (; it != services.m_books.end(); it++) {
        cout << num << "."
             << "\n\n\r";
        Book *book = services.m_books[it->first];
        cout << "name : " << book->name << "\n\n";
        cout << "author : " << book->author << "\n\n";
        cout << "pages : " << book->pages << "\n\n";
        cout << "id : " << it->first << "\n\n\n\r";

        num += 1;
      }
      continue;
    }

    if (command.type == 5) {
      if (services.find_book(command.id) == nullptr) {
        cout << "\n             Log :             \n\r";
        cout << "-----------------------------------\n\r";

        cout << ". ";
        cout << "That Id doesnt Exist\n\r";
        cout << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n\r";
        continue;
      }
      cout << "\n             Book :             \n\r";
      cout << "-----------------------------------\n\n\r";
      Book *book = services.m_books[1];
      Book *found = (Book *)services.find_book(command.id);
      cout << "name : " << found->name << "\n\n";
      cout << "author : " << found->author << "\n\n";
      cout << "pages : " << found->pages << "\n\n";
      cout << "id : " << command.id << "\n\n\n\r";
      continue;
    }
    if (command.type == 7) {
      unordered_map<int, Book *> arra = services.find_all_books(
          command.command["name"], command.command["author"],
          command.command["pages"]);
      if (arra.size() == 0) {
        cout << "\n             Log :             \n\r";
        cout << "-----------------------------------\n\r";

        cout << ". ";
        cout << "No Book meets those conditions\n\r";
        cout << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n\r";
        continue;
      }

      unordered_map<int, Book *>::iterator it = arra.begin();
      cout << "\n             Books :             \n\r";
      cout << "-----------------------------------\n\n\r";

      int num = 1;
      for (; it != arra.end(); it++) {
        cout << num << "."
             << "\n\n\r";
        Book *book = arra[it->first];
        cout << "name : " << book->name << "\n\n";
        cout << "author : " << book->author << "\n\n";
        cout << "pages : " << book->pages << "\n\n";
        cout << "id : " << it->first << "\n\n\n\r";

        num += 1;
      }
      continue;
    }

    if (command.type == 8) {
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
      retr = (Book *)services.create_book(createe);
      if (retr == nullptr) {
        cout << ". "
             << "Book is either a duplicate or invalid\n\r";
        cout << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n";
        continue;
      }
      cout << "Book Successfully Created \n\n\r";
      tru = true;
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
  }
}
