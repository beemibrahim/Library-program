#include "Library_DatabaseService.hpp"

const Book *LibraryDatabaseService::create_book(const Book &book) {
  std::vector<std::string> errors;
  if (!validate(book)) {
    errors.push_back("Book is invalid");
    throw errors;
  }
  if (dupchk(book)) {
    errors.push_back("Book is a duplicate");
    throw errors;
  }
  sqlite::connection con("data/library.db");
  sqlite::execute ins(con, "INSERT INTO library VALUES(? , ? , ? , ?);");

  ins % sqlite::nil % book.name % book.author % (int)book.pages;

  ins();
  Book *ptr = new Book;
  ptr->name = book.name;
  ptr->author = book.author;
  ptr->pages = book.pages;
  return ptr;
}

const Book *LibraryDatabaseService::find_book(unsigned const int &id) {

  Book *boor = new Book;
  char *err = 0;
  sqlite::connection con("data/library.db");
  sqlite::query q(con, "SELECT * FROM library WHERE id = ?;");
  int d = (int)id;
  q % d;
  q();
  boost::shared_ptr<sqlite::result> result = q.get_result();

  int row_count = 0;
  if (result->get_string(1) == "NULL") {
    return nullptr;
  }

  boor->name = result->get_string(1);
  boor->author = result->get_string(2);
  boor->pages = result->get_int(3);

  return boor;
}

const std::unordered_map<int, Book *>
LibraryDatabaseService::find_all_books(const std::string &name,
                                       const std::string &author,
                                       unsigned const int &pages) {
  std::unordered_map<int, Book *> answer;
  char *err = 0;
  boost::shared_ptr<sqlite::result> result;
  sqlite::connection con("data/library.db");
  int type = 0;
  // 1 = author && pages
  // 2 = name && pages
  // 3 = name && author
  // 4 = pages
  // 5 = name
  // 6 = author
  // 7
  // 8 = name && author && pages
  std::string mystery;
  if (name == "" && author != "" && pages != 0) {
    mystery = "SELECT * FROM library WHERE author = ? AND pages = ?;";
    type = 1;
  }
  if (name != "" && author == "" && pages != 0) {
    mystery = "SELECT * FROM library WHERE name = ? AND pages = ?;";
    type = 2;
  }
  if (name != "" && author != "" && pages == 0) {
    mystery = "SELECT * FROM library WHERE name = ? AND author = ?;";
    type = 3;
  }

  if (name == "" && author == "" && pages != 0) {
    mystery = "SELECT * FROM library WHERE pages = ?;";
    type = 4;
  }
  if (name != "" && author == "" && pages == 0) {
    mystery = "SELECT * FROM library WHERE name = ?;";
    type = 5;
  }
  if (name == "" && author != "" && pages == 0) {
    mystery = "SELECT * FROM library WHERE author = ?;";
    type = 6;
  }

  if (name == "" && author == "" && pages == 0) {
    mystery = "SELECT * FROM library;";
    type = 7;
  }
  if (name != "" && author != "" && pages != 0) {
    mystery =
        "SELECT * FROM library WHERE name = ? AND author = ? AND pages = ?;";
    type = 8;
  }

  sqlite::query q(con, mystery);

  if (type == 1)
    q % author % (int)pages;
  if (type == 2)
    q % name % (int)pages;
  if (type == 3)
    q % name % author;
  if (type == 4)
    q % (int)pages;
  if (type == 5)
    q % name;
  if (type == 6)
    q % author;
  if (type == 8)
    q % name % author % (int)pages;
  if (type != 7)
    q();

  result = q.get_result();
  while (result->next_row()) {
    Book *exa = new Book;
    exa->name = result->get_string(1);
    exa->author = result->get_string(2);
    exa->pages = result->get_int(3);

    answer[result->get_int(0)] = exa;
  }
  return answer;
}

const Book *LibraryDatabaseService::patch_book(unsigned const int &id,
                                               const Book &book) {
  std::vector<std::string> errors;
  Book extr;
  sqlite::connection con("data/library.db");
  sqlite::query q(con, "SELECT * FROM library where id = ?;");
  q % (int)id;
  q();
  boost::shared_ptr<sqlite::result> result = q.get_result();
  extr.name = result->get_string(1);
  extr.author = result->get_string(2);
  extr.pages = result->get_int(3);

  if (book.name != "") {
    extr.name = book.name;
  }
  if (book.author != "") {
    extr.author = book.author;
  }
  if (book.pages > 0) {
    extr.pages = book.pages;
  }

  if (!validate(extr)) {
    errors.push_back("Book is invalid");
    throw errors;
  }
  if (dupchk_upd(extr, id)) {
    errors.push_back("Book is a duplicate");
    throw errors;
  }

  sqlite::execute ins(
      con,
      "UPDATE library SET name = ? AND author = ? AND pages = ? WHERE id = ?;");
  ins % extr.name % extr.author % (int)extr.pages % (int)id;
  ins();
  Book *ret = new Book;
  ret->name = extr.name;
  ret->author = extr.author;
  ret->pages = extr.pages;
  return ret;
}

const Book *LibraryDatabaseService::update_book(unsigned const int &id,
                                                const Book &book) {
  sqlite::connection con("data/library.db");

  sqlite::execute ins(
      con,
      "UPDATE library SET name = ? AND author = ? AND pages = ? WHERE id = ?;");
  ins % book.name % book.author % (int)book.pages % (int)id;
  ins();
  Book *ret = new Book;
  ret->name = book.name;
  ret->author = book.author;
  ret->pages = book.pages;
  return ret;
}

bool LibraryDatabaseService::validate(const Book &book) {
  if (book.name.size() == 0) {
    return false;
  }
  if (book.author.size() == 0) {
    return false;
  }
  int count = 0;
  bool letchk = false;
  for (int i = 0; i < book.author.size(); i++) {
    if (book.author[i] == ' ') {
      continue;
    }
    if (book.author[i] > 47 && book.author[i] < 58) {
      ++count;
    }
    if ((book.author[i] >= 97 && book.author[i] <= 122) ||
        (book.author[i] >= 65 && book.author[i] <= 90)) {
      letchk = true;
    }
  }
  if (count == book.author.size() || letchk == false) {
    return false;
  }

  if (book.pages == 0) {
    return false;
  }
  return true;
}

bool LibraryDatabaseService::delete_book(unsigned const int &id) {
  if (find_book(id) == nullptr) {
    return false;
  }
  sqlite::connection con("data/library.db");
  sqlite::execute ins(con, "DELETE FROM library WHERE id = ?;");
  ins % (int)id;
  ins();
  return true;
}
void LibraryDatabaseService::delete_all_books() {
  sqlite::connection con("data/library.db");
  sqlite::execute ins(con, "DELETE FROM library;");
  ins();
}

bool LibraryDatabaseService::dupchk(const Book &book) {
  sqlite::connection con("data/library.db");

  sqlite::query q(con, "SELECT * FROM library where name = ? AND author = ?;");
  int al = 0;
  q % book.name % book.author;
  q();
  boost::shared_ptr<sqlite::result> result = q.get_result();
  if (result->get_string(1) != "NULL") {
    return true;
  }
  return false;
}

void LibraryDatabaseService::delete_condition(const std::string &name,
                                              const std::string &author,
                                              unsigned const int &pages) {
  sqlite::connection con("data/library.db");
  boost::shared_ptr<sqlite::result> result;
  if (name == "" && author != "" && pages != 0) {
    sqlite::execute ins(con,
                        "DELETE FROM library WHERE author = ? AND pages = ?;");
    ins % author % (int)pages;
    ins();
  }
  if (name != "" && author == "" && pages != 0) {
    sqlite::execute ins(con,
                        "DELETE FROM library WHERE name = ? AND pages = ?;");
    ins % name % (int)pages;
    ins();
  }
  if (name != "" && author != "" && pages == 0) {
    sqlite::execute ins(con,
                        "DELETE FROM library WHERE name = ? AND author = ?;");
    ins % name % author;
    ins();
  }

  if (name == "" && author == "" && pages != 0) {
    sqlite::execute ins(con, "DELETE FROM library WHERE pages = ?;");
    ins % (int)pages;
    ins();
  }
  if (name != "" && author == "" && pages == 0) {
    sqlite::execute ins(con, "DELETE FROM library WHERE name = ?;");
    ins % name;
    ins();
  }
  if (name == "" && author != "" && pages == 0) {
    sqlite::execute ins(con, "DELETE FROM library WHERE author = ?;");
    ins % author;
    ins();
  }

  if (name == "" && author == "" && pages == 0) {
    sqlite::execute ins(con, "DELETE FROM library;");
  }
  if (name != "" && author != "" && pages != 0) {
    sqlite::execute ins(
        con,
        "DELETE FROM library WHERE name = ? AND author = ? AND pages = ?;");
    ins % name % author % (int)pages;
    ins();
  }
}

bool LibraryDatabaseService::dupchk_upd(const Book &book, int id) {
  if (find_book(id) == nullptr) {
    return false;
  }

  sqlite::connection con("data/library.db");
  sqlite::query q(con, "SELECT * FROM library where name = ? AND author = ?;");
  int al = 0;
  q % book.name % book.author % (int)book.pages;
  q();
  boost::shared_ptr<sqlite::result> result = q.get_result();
  if (result->get_row_count() != 1) {
    return false;
  }

  return true;
}

std::stringstream LibraryDatabaseService::execute_command(Command &command) {
  std::stringstream stream;
  if (command.type == 6) {
    sqlite::connection con("data/library.db");
    sqlite::query q(con, "SELECT * FROM library;");
    boost::shared_ptr<sqlite::result> result = q.get_result();
    boost::shared_ptr<sqlite::result> result2 = q.get_result();
    std::unordered_map<int, Book *> m_books = find_all_books("", "", 0);

    if (m_books.size() == 0) {
      std::cout << "\n             Log :             \n\r";
      std::cout << "-----------------------------------\n\r";

      std::cout << ". ";
      std::cout << "No Books are created\n\r";
      std::cout << "Command Failed , read my REAMDE.md on github : "
                   "https://github.com/beemibrahim/Library-program\n\n\r";
      stream << "\n             Log :             \n\r";
      stream << "-----------------------------------\n\r";

      stream << ". ";
      stream << "No Books are created\n\r";
      stream << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n\r";

      return stream;
    }
    std::cout << "\n             Books :             \n\r";
    std::cout << "-----------------------------------\n\n\r";

    stream << "\n             Books :             \n\r";
    stream << "-----------------------------------\n\n\r";

    int num = 1;
    std::unordered_map<int, Book *>::iterator it = m_books.begin();
    for (; it != m_books.end(); it++) {
      std::cout << num << "."
                << "\n\n\r";
      Book *book = m_books[it->first];
      std::cout << "name : " << book->name << "\n\n";
      std::cout << "author : " << book->author << "\n\n";
      std::cout << "pages : " << book->pages << "\n\n";
      std::cout << "id : " << it->first << "\n\n\n\r";
      stream << num << "."
             << "\n\n\r";
      stream << "name : " << book->name << "\n\n";
      stream << "author : " << book->author << "\n\n";
      stream << "pages : " << book->pages << "\n\n";
      stream << "id : " << it->first << "\n\n\n\r";

      num += 1;
      delete m_books[it->first];
    }
    return stream;
  }

  if (command.type == 5) {
    if (find_book(command.id) == nullptr) {
      std::cout << "\n             Log :             \n\r";
      std::cout << "-----------------------------------\n\r";

      std::cout << ". ";
      std::cout << "That Id doesnt Exist\n\r";
      std::cout << "Command Failed , read my REAMDE.md on github : "
                   "https://github.com/beemibrahim/Library-program\n\n\r";

      stream << "\n             Log :             \n\r";
      stream << "-----------------------------------\n\r";

      stream << ". ";
      stream << "That Id doesnt Exist\n\r";
      stream << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n\r";

      return stream;
    }
    std::cout << "\n             Book :             \n\r";
    std::cout << "-----------------------------------\n\n\r";
    Book *found = (Book *)find_book(command.id);
    std::cout << "name : " << found->name << "\n\n";
    std::cout << "author : " << found->author << "\n\n";
    std::cout << "pages : " << found->pages << "\n\n";
    std::cout << "id : " << command.id << "\n\n\n\r";

    stream << "\n             Book :             \n\r";
    stream << "-----------------------------------\n\n\r";
    stream << "name : " << found->name << "\n\n";
    stream << "author : " << found->author << "\n\n";
    stream << "pages : " << found->pages << "\n\n";
    stream << "id : " << command.id << "\n\n\n\r";

    return stream;
    delete found;
  }
  if (command.type == 7) {
    std::unordered_map<int, Book *> arra =
        find_all_books(command.command["name"], command.command["author"],
                       command.command["pages"]);
    if (arra.size() == 0) {
      std::cout << "\n             Log :             \n\r";
      std::cout << "-----------------------------------\n\r";

      std::cout << ". ";
      std::cout << "No Book meets those conditions\n\r";
      std::cout << "Command Failed , read my REAMDE.md on github : "
                   "https://github.com/beemibrahim/Library-program\n\n\r";

      stream << "\n             Log :             \n\r";
      stream << "-----------------------------------\n\r";

      stream << ". ";
      stream << "No Book meets those conditions\n\r";
      stream << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n\r";

      return stream;
    }

    std::unordered_map<int, Book *>::iterator it = arra.begin();
    std::cout << "\n             Books :             \n\r";
    std::cout << "-----------------------------------\n\n\r";

    stream << "\n             Books :             \n\r";
    stream << "-----------------------------------\n\n\r";

    int num = 1;
    for (; it != arra.end(); it++) {
      std::cout << num << "."
                << "\n\n\r";
      Book *book = arra[it->first];
      std::cout << "name : " << book->name << "\n\n";
      std::cout << "author : " << book->author << "\n\n";
      std::cout << "pages : " << book->pages << "\n\n";
      std::cout << "id : " << it->first << "\n\n\n\r";

      stream << num << "."
             << "\n\n\r";
      stream << "name : " << book->name << "\n\n";
      stream << "author : " << book->author << "\n\n";
      stream << "pages : " << book->pages << "\n\n";
      stream << "id : " << it->first << "\n\n\n\r";

      num += 1;
      delete arra[it->first];
    }
    return stream;
  }

  if (command.type == 4) {
    sqlite::connection con("data/library.db");
    std::unordered_map<int, Book *> size =
        find_all_books(command.command["name"], command.command["author"],
                       command.command["pages"]);
    std::string input = std::string();
    // Prompting user if they are sure about the consequenses
    std::cout << "Are You Sure About This ( " << size.size()
              << " books are being deleted ) [Y/n]";

    stream << "Are You Sure About This ( " << size.size()
           << " books are being deleted ) [Y/n]";

    bool em = false;
    if (size.size() == 0) {
      em = true;
    }
    getline(std::cin, input);
    std::cout << "\n\r";
    stream << "\n\r";
    std::unordered_map<int, Book *>::iterator it = size.begin();
    for (; it != size.end(); it++) {
      delete size[it->first];
    }
    if (input == "Y") {
      delete_condition(command.command["name"], command.command["author"],
                       command.command["pages"]);
      std::cout << "\n             Log :             \n\r";
      std::cout << "-----------------------------------\n\r";
      std::cout << size.size() << " Books Successfully Deleted\n\r";

      stream << "\n             Log :             \n\r";
      stream << "-----------------------------------\n\r";
      stream << size.size() << " Books Successfully Deleted\n\r";

      if (em) {
        std::cout << "(There was nothing to delete)\n\r";
        stream << "(There was nothing to delete)\n\r";
      }
      std::cout << "\n\r";
      stream << "\n\r";
    } else {
      std::cout << "\n             Log :             \n\r";
      std::cout << "-----------------------------------\n\r";
      std::cout << "Delete Aborted\n\n\r";

      stream << "\n             Log :             \n\r";
      stream << "-----------------------------------\n\r";
      stream << "Delete Aborted\n\n\r";

      return stream;
    }
  }

  std::cout << "\n             Log :             \n\r";
  std::cout << "-----------------------------------\n\r";

  stream << "\n             Log :             \n\r";
  stream << "-----------------------------------\n\r";

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
      delete patch_book(command.id, book);
    } catch (std::vector<std::string> errors) {

      for (int i = 0; i < errors.size(); i++) {
        std::cout << ". ";
        std::cout << errors[i] << "\n\r";

        stream << ". ";
        stream << errors[i] << "\n\r";
      }
      std::cout << "Command Failed , read my REAMDE.md on github : "
                   "https://github.com/beemibrahim/Library-program\n\n";

      stream << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n";

      return stream;
    }
    std::cout << "Book Successfully Patched\n\n\r";

    stream << "Book Successfully Patched\n\n\r";
  }

  if (command.type == 8) {
    Book book = Book();

    book.name = command.command["name"];
    book.author = command.command["author"];
    book.pages = command.command["pages"];
    try {
      delete update_book(command.id, book);
    } catch (std::vector<std::string> errors) {

      for (int i = 0; i < errors.size(); i++) {
        std::cout << ". ";
        std::cout << errors[i] << "\n\r";
        stream << ". ";
        stream << errors[i] << "\n\r";
      }
      std::cout << "Command Failed , read my REAMDE.md on github : "
                   "https://github.com/beemibrahim/Library-program\n\n\r";
      stream << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n\r";

      return stream;
    }
    std::cout << "Book Successfully Updated\n\n\r";
    stream << "Book Successfully Updated\n\n\r";

    return stream;
  }

  if (command.type == 3) {
    sqlite::connection con("data/library.db");

    sqlite::query q(con, "SELECT * FROM library;");
    boost::shared_ptr<sqlite::result> result = q.get_result();

    if (command.warning_log.size() == 1) {
      std::cout << "Delete Aborted\n\n\r";
      stream << "Delete Aborted\n\n\r";

      return stream;
    }
    bool em = false;
    if (!result->next_row())
      em = true;
    delete_all_books();
    std::cout << "All Books Successfully Deleted\n\r";
    stream << "All Books Successfully Deleted\n\r";
    if (em) {
      std::cout << "(There was nothing to delete)\n\n\r";
      stream << "(There was nothing to delete)\n\n\r";

    } else {
      std::cout << "\n\r";
      stream << "\n\r";
    }

    return stream;
  }

  if (command.type == 1) {
    // Creating book according to the json
    Book createe;
    createe.name = command.command["name"];
    createe.author = command.command["author"];
    createe.pages = command.command["pages"];
    Book *retu;
    try {
      delete create_book(createe);
    } catch (std::vector<std::string> errors) {

      for (int i = 0; i < errors.size(); i++) {
        std::cout << ". ";
        std::cout << errors[i] << "\n\r";
        stream << ". ";
        stream << errors[i] << "\n\r";
      }
      std::cout << "Command Failed , read my REAMDE.md on github : "
                   "https://github.com/beemibrahim/Library-program\n\n\r";
      stream << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n\r";

      return stream;
    }
    std::cout << "Book Successfully Created\n\n\r";
    stream << "Book Successfully Created\n\n\r";
    return stream;
  }

  if (command.type == 2) {
    bool work = delete_book(command.id);
    // ID didnt exist
    if (work == false) {
      std::cout << ". ";
      std::cout << "Id doesnt exist\n\r";
      std::cout << "Command Failed , read my REAMDE.md on github : "
                   "https://github.com/beemibrahim/Library-program\n\n";
      stream << ". ";
      stream << "Id doesnt exist\n\r";
      stream << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n";

      return stream;
    }
    std::cout << "Book Successfully Deleted \n\n\r";
    stream << "Book Successfully Deleted \n\n\r";
  }
  return stream;
}

void LibraryDatabaseService::import(std::unordered_map<int, Book *> library,
                                    int id) {
  return;
}
