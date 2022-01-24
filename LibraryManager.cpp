#include "LibraryManager.hpp"

const Book *LibraryService::create_book(const Book &book) {
  vector<string> errors;
  if (!validate(book)) {
    errors.push_back("Book is invalid");
    throw errors;
  }
  if (dupchk(book)) {
    errors.push_back("Book is a duplicate");
    throw errors;
  }
  Book *bookt = new Book;
  bookt->name = book.name;
  bookt->author = book.author;
  bookt->pages = book.pages;
  m_books[this->last_id + 1] = bookt;
  ++this->last_id;
  return bookt;
}

const Book *LibraryService::find_book(unsigned const int &id) {
  if (m_books.count(id) == 0) {
    return nullptr;
  }
  int d = id;
  Book *booky = m_books[d];
  return booky;
}

const std::unordered_map<int, Book *>
LibraryService::find_all_books(const std::string &name,
                               const std::string &author,
                               unsigned const int &pages) {
  unordered_map<int, Book *> answer;
  int count = 0;
  unordered_map<int, Book *>::iterator it = m_books.begin();
  for (; it != m_books.end(); it++) {
    int valid = 0;
    if (name == "") {
      valid++;
    } else if (name == it->second->name) {
      valid++;
    }

    if (author == "") {
      valid++;
    } else if (author == it->second->author) {
      valid++;
    }

    if (pages == 0) {
      valid++;
    } else if (pages == it->second->pages) {
      valid++;
    }
    if (valid == 3) {
      answer[count] = it->second;
      count++;
    }
  }
  return answer;
}

const Book *LibraryService::patch_book(unsigned const int &id,
                                       const Book &book) {
  vector<string> errors;

  Book extr = *m_books[id];
  if (m_books.count(id) == 0) {
    errors.push_back("Id doesnt exist");
    throw errors;
  }

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

  if (book.name != "") {
    m_books[id]->name = book.name;
  }
  if (book.author != "") {
    m_books[id]->author = book.author;
  }
  if (book.pages > 0) {
    m_books[id]->pages = book.pages;
  }

  return m_books[id];
}

const Book *LibraryService::update_book(unsigned const int &id,
                                        const Book &book) {
  vector<string> errors;

  if (m_books.count(id) == 0) {
    errors.push_back("Id doesnt exist");
    throw errors;
  }

  if (!validate(book)) {
    errors.push_back("Book is invalid");
    throw errors;
  }
  if (dupchk_upd(book, id)) {
    errors.push_back("Book is a duplicate");
    throw errors;
  }

  m_books[id]->name = book.name;
  m_books[id]->author = book.author;
  m_books[id]->pages = book.pages;

  return m_books[id];
}

bool LibraryService::validate(const Book &book) {
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

bool LibraryService::delete_book(unsigned const int &id) {
  if (m_books.count(id) == 0) {
    return false;
  }
  delete m_books[id];
  m_books.erase(id);
  return true;
}
void LibraryService::delete_all_books() {
  unordered_map<int, Book *>::iterator it = m_books.begin();

  for (; it != m_books.end(); it++) {
    delete m_books[it->first];
  }

  m_books.erase(m_books.begin(), m_books.end());
}

bool LibraryService::dupchk(const Book &book) {
  unordered_map<int, Book *>::iterator it = m_books.begin();
  for (; it != m_books.end(); it++) {
    if (it->second->name == book.name && it->second->author == book.author) {
      return true;
    }
  }
  return false;
}

void LibraryService::delete_condition(const std::string &name,
                                      const std::string &author,
                                      unsigned const int &pages) {
  unordered_map<int, Book *>::iterator it = m_books.begin();
  for (; it != m_books.end();) {
    int valid = 0;
    if (name == "") {
      valid++;
    } else if (name == it->second->name) {
      valid++;
    }

    if (author == "") {
      valid++;
    } else if (author == it->second->author) {
      valid++;
    }

    if (pages == 0) {
      valid++;
    } else if (pages == it->second->pages) {
      valid++;
    }
    if (valid == 3) {
      int erase = it->first;
      it++;
      delete m_books[it->first];
      m_books.erase(erase);
      continue;
    }
    it++;
  }
}

bool LibraryService::dupchk_upd(const Book &book, int id) {
  if (m_books.count(id) == 0) {
    return false;
  }

  unordered_map<int, Book *>::iterator it = m_books.begin();
  for (; it != m_books.end(); it++) {
    if (it->first == id) {
      continue;
    }
    if (it->second->name == book.name && it->second->author == book.author) {
      return true;
    }
  }
  return false;
}

std::stringstream LibraryService::execute_command(Command &command) {
  std::stringstream stream;
  if (command.type == 6) {
    unordered_map<int, Book *>::iterator it = m_books.begin();
    if (m_books.size() == 0) {
      cout << "\n             Log :             \n\r";
      cout << "-----------------------------------\n\r";

      cout << ". ";
      cout << "No Books are created\n\r";
      cout << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n\r";
      stream << "\n             Log :             \n\r";
      stream << "-----------------------------------\n\r";

      stream << ". ";
      stream << "No Books are created\n\r";
      stream << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n\r";

      return stream;
    }
    cout << "\n             Books :             \n\r";
    cout << "-----------------------------------\n\n\r";

    stream << "\n             Books :             \n\r";
    stream << "-----------------------------------\n\n\r";

    int num = 1;
    for (; it != m_books.end(); it++) {
      cout << num << "."
           << "\n\n\r";
      Book *book = m_books[it->first];
      cout << "name : " << book->name << "\n\n";
      cout << "author : " << book->author << "\n\n";
      cout << "pages : " << book->pages << "\n\n";
      cout << "id : " << it->first << "\n\n\n\r";
      stream << num << "."
             << "\n\n\r";
      stream << "name : " << book->name << "\n\n";
      stream << "author : " << book->author << "\n\n";
      stream << "pages : " << book->pages << "\n\n";
      stream << "id : " << it->first << "\n\n\n\r";

      num += 1;
    }
    return stream;
  }

  if (command.type == 5) {
    if (find_book(command.id) == nullptr) {
      cout << "\n             Log :             \n\r";
      cout << "-----------------------------------\n\r";

      cout << ". ";
      cout << "That Id doesnt Exist\n\r";
      cout << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n\r";

      stream << "\n             Log :             \n\r";
      stream << "-----------------------------------\n\r";

      stream << ". ";
      stream << "That Id doesnt Exist\n\r";
      stream << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n\r";

      return stream;
    }
    cout << "\n             Book :             \n\r";
    cout << "-----------------------------------\n\n\r";
    Book *book = m_books[1];
    Book *found = (Book *)find_book(command.id);
    cout << "name : " << found->name << "\n\n";
    cout << "author : " << found->author << "\n\n";
    cout << "pages : " << found->pages << "\n\n";
    cout << "id : " << command.id << "\n\n\n\r";

    stream << "\n             Book :             \n\r";
    stream << "-----------------------------------\n\n\r";
    stream << "name : " << found->name << "\n\n";
    stream << "author : " << found->author << "\n\n";
    stream << "pages : " << found->pages << "\n\n";
    stream << "id : " << command.id << "\n\n\n\r";

    return stream;
  }
  if (command.type == 7) {
    unordered_map<int, Book *> arra =
        find_all_books(command.command["name"], command.command["author"],
                       command.command["pages"]);
    if (arra.size() == 0) {
      cout << "\n             Log :             \n\r";
      cout << "-----------------------------------\n\r";

      cout << ". ";
      cout << "No Book meets those conditions\n\r";
      cout << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n\r";

      stream << "\n             Log :             \n\r";
      stream << "-----------------------------------\n\r";

      stream << ". ";
      stream << "No Book meets those conditions\n\r";
      stream << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n\r";

      return stream;
    }

    unordered_map<int, Book *>::iterator it = arra.begin();
    cout << "\n             Books :             \n\r";
    cout << "-----------------------------------\n\n\r";

    stream << "\n             Books :             \n\r";
    stream << "-----------------------------------\n\n\r";

    int num = 1;
    for (; it != arra.end(); it++) {
      cout << num << "."
           << "\n\n\r";
      Book *book = arra[it->first];
      cout << "name : " << book->name << "\n\n";
      cout << "author : " << book->author << "\n\n";
      cout << "pages : " << book->pages << "\n\n";
      cout << "id : " << it->first << "\n\n\n\r";

      stream << num << "."
             << "\n\n\r";
      stream << "name : " << book->name << "\n\n";
      stream << "author : " << book->author << "\n\n";
      stream << "pages : " << book->pages << "\n\n";
      stream << "id : " << it->first << "\n\n\n\r";

      num += 1;
    }
    return stream;
  }

  if (command.type == 4) {
    string input = string();
    // Prompting user if they are sure about the consequenses
    cout << "Are You Sure About This ( " << m_books.size()
         << " books are being deleted ) [Y/n]";

    stream << "Are You Sure About This ( " << m_books.size()
           << " books are being deleted ) [Y/n]";

    bool em = false;
    if (m_books.size() == 0) {
      em = true;
    }
    getline(cin, input);
    cout << "\n\r";
    stream << "\n\r";
    if (input == "Y") {
      delete_condition(command.command["name"], command.command["author"],
                       command.command["pages"]);
      cout << "\n             Log :             \n\r";
      cout << "-----------------------------------\n\r";
      cout << m_books.size() << " Books Successfully Deleted\n\r";

      stream << "\n             Log :             \n\r";
      stream << "-----------------------------------\n\r";
      stream << m_books.size() << " Books Successfully Deleted\n\r";

      if (em) {
        cout << "(There was nothing to delete)\n\r";
        stream << "(There was nothing to delete)\n\r";
      }
      cout << "\n\r";
      stream << "\n\r";
    } else {
      cout << "\n             Log :             \n\r";
      cout << "-----------------------------------\n\r";
      cout << "Delete Aborted\n\n\r";

      stream << "\n             Log :             \n\r";
      stream << "-----------------------------------\n\r";
      stream << "Delete Aborted\n\n\r";

      return stream;
    }
  }

  cout << "\n             Log :             \n\r";
  cout << "-----------------------------------\n\r";

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
      patch_book(command.id, book);
    } catch (vector<string> errors) {

      for (int i = 0; i < errors.size(); i++) {
        cout << ". ";
        cout << errors[i] << "\n\r";

        stream << ". ";
        stream << errors[i] << "\n\r";
      }
      cout << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n";

      stream << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n";

      return stream;
    }
    cout << "Book Successfully Patched\n\n\r";

    stream << "Book Successfully Patched\n\n\r";
  }

  if (command.type == 8) {
    Book book = Book();

    book.name = command.command["name"];
    book.author = command.command["author"];
    book.pages = command.command["pages"];
    try {
      const Book *bookr = update_book(command.id, book);
    } catch (vector<string> errors) {

      for (int i = 0; i < errors.size(); i++) {
        cout << ". ";
        cout << errors[i] << "\n\r";
        stream << ". ";
        stream << errors[i] << "\n\r";
      }
      cout << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n\r";
      stream << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n\r";

      return stream;
    }
    cout << "Book Successfully Updated\n\n\r";
    stream << "Book Successfully Updated\n\n\r";

    return stream;
  }

  if (command.type == 3) {
    if (command.warning_log.size() == 1) {
      cout << "Delete Aborted\n\n\r";
      stream << "Delete Aborted\n\n\r";

      return stream;
    }
    delete_all_books();
    cout << "All Books Successfully Deleted\n\r";
    stream << "All Books Successfully Deleted\n\r";

    if (m_books.size() == 0) {
      cout << "(There was nothing to delete)\n\n\r";
      stream << "(There was nothing to delete)\n\n\r";

    } else {
      cout << "\n\r";
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
      create_book(createe);
    } catch (vector<string> errors) {

      for (int i = 0; i < errors.size(); i++) {
        cout << ". ";
        cout << errors[i] << "\n\r";
        stream << ". ";
        stream << errors[i] << "\n\r";
      }
      cout << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n\r";
      stream << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n\r";

      return stream;
    }
    cout << "Book Successfully Created\n\n\r";
    stream << "Book Successfully Created\n\n\r";
    return stream;
  }

  if (command.type == 2) {
    bool work = delete_book(command.id);
    // ID didnt exist
    if (work == false) {
      cout << ". ";
      cout << "Id doesnt exist\n\r";
      cout << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n";
      stream << ". ";
      stream << "Id doesnt exist\n\r";
      stream << "Command Failed , read my REAMDE.md on github : "
                "https://github.com/beemibrahim/Library-program\n\n";

      return stream;
    }
    cout << "Book Successfully Deleted \n\n\r";
    stream << "Book Successfully Deleted \n\n\r";
  }
  return stream;
}
