#include "LibraryApp.hpp"

void LibraryApp::runLibrary() {
  bool tru = false;
  Book *retr;
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
    /*
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

    if (command.type == 4) {
      string input = string();
      // Prompting user if they are sure about the consequenses
      cout << "Are You Sure About This ( " << services.m_books.size()
           << " books are being deleted ) [Y/n]";
      bool em = false;
      if (services.m_books.size() == 0) {
        em = true;
      }
      getline(cin, input);
      cout << "\n\r";
      if (input == "Y") {
        services.delete_condition(command.command["name"],
                                  command.command["author"],
                                  command.command["pages"]);
        cout << "\n             Log :             \n\r";
        cout << "-----------------------------------\n\r";
        cout << services.m_books.size() << " Books Successfully Deleted\n\r";
        if (em) {
          cout << "(There was nothing to delete)\n\r";
        }
        cout << "\n\r";
      } else {
        cout << "\n             Log :             \n\r";
        cout << "-----------------------------------\n\r";
        cout << "Delete Aborted\n\n\r";
        continue;
      }
    }

    cout << "\n             Log :             \n\r";
    cout << "-----------------------------------\n\r";

    if (command.type == 9) {
      Book book = Book();
      if (command.command.contains("name")) {
        book.name = command.command["name"];
      }
      if (command.command.contains("author")) {
        book.author = command.command["author"];
      }
      if (command.command.contains("pages")) {
        book.pages = command.command["pages"];
      }

      try {
        services.patch_book(command.id, book);
      } catch (vector<string> errors) {

        for (int i = 0; i < errors.size(); i++) {
          cout << ". ";
          cout << errors[i] << "\n\r";
        }
        cout << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n";
        continue;
      }
      cout << "Book Successfully Patched\n\n\r";
    }

    if (command.type == 8) {
      Book book = Book();

      book.name = command.command["name"];
      book.author = command.command["author"];
      book.pages = command.command["pages"];
      try {
        const Book *bookr = services.update_book(command.id, book);
      } catch (vector<string> errors) {

        for (int i = 0; i < errors.size(); i++) {
          cout << ". ";
          cout << errors[i] << "\n\r";
        }
        cout << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n\r";
        continue;
      }
      cout << "Book Successfully Updated\n\n\r";

      continue;
    }

    if (command.type == 3) {
      if (command.warning_log.size() == 1) {
        cout << "Delete Aborted\n\n\r";
        continue;
      }
      services.delete_all_books();
      cout << "All Books Successfully Deleted\n\r";
      if (services.m_books.size() == 0) {
        cout << "(There was nothing to delete)\n\n\r";
      } else {
        cout << "\n\r";
      }

      continue;
    }

    if (command.type == 1) {
      // Creating book according to the json
      Book createe;
      createe.name = command.command["name"];
      createe.author = command.command["author"];
      createe.pages = command.command["pages"];
      Book *retu;
      try {
        services.create_book(createe);
      } catch (vector<string> errors) {

        for (int i = 0; i < errors.size(); i++) {
          cout << ". ";
          cout << errors[i] << "\n\r";
        }
        cout << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n\r";
        continue;
      }
      cout << "Book Successfully Created\n\n\r";
    }

    if (command.type == 2) {
      bool work = services.delete_book(command.id);
      // ID didnt exist
      if (work == false) {
        cout << ". ";
        cout << "Id doesnt exist\n\r";
        cout << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n";
        continue;
      }
      cout << "Book Successfully Deleted \n\n\r";
    }
    */
  }
}
