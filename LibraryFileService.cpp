#include "LibraryFileService.hpp"

const Book *LibraryFileService::create_book(const Book &book) {
  std::vector<std::string> errors;

  if (!validate(book)) {
    errors.push_back("Book is invalid");
    throw errors;
  }
  if (dupchk(book)) {
    errors.push_back("Book is a duplicate");
    throw errors;
  }
  // Concatenating stuff
  std::string idf = std::to_string(last_id + 1);
  std::string idfi = ".json";
  std::string idnr = "Books/";
  std::string newf = idf + idfi;
  //
  std::string filepath = idnr + newf;
  std::ofstream file(filepath);
  json fileconl;
  fileconl["name"] = book.name;
  fileconl["author"] = book.author;
  fileconl["pages"] = book.pages;
  std::string dump = fileconl.dump();
  file << dump;
  file.close();
  std::fstream filei;
  std::string fo = "Information/last_id.txt";
  filei.open(fo.c_str(), std::ifstream::out | std::ifstream::trunc);
  last_id += 1;
  filei << last_id;
  filei.close();

  Book *mall = new Book;
  mall->name = book.name;
  mall->author = book.author;
  mall->pages = book.pages;
  m_books[last_id] = mall;
  Book *cop = new Book;
  cop->name = m_books[last_id]->name;
  cop->author = m_books[last_id]->author;
  cop->pages = m_books[last_id]->pages;
  return cop;
}

const Book *LibraryFileService::find_book(unsigned const int &id) {
  std::vector<std::string> errors;

  if (m_books.count(id) == 0) {
    errors.push_back("Id doesnt exist");
    throw errors;
  }

  Book *cop = new Book;
  cop->name = m_books[id]->name;
  cop->author = m_books[id]->author;
  cop->pages = m_books[id]->pages;
  return cop;
}

const std::unordered_map<int, Book *>
LibraryFileService::find_all_books(const std::string &name,
                                   const std::string &author,
                                   unsigned const int &pages) {
  std::unordered_map<int, Book *> answer;
  int count = 0;
  std::unordered_map<int, Book *>::iterator it = m_books.begin();
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
      Book *cop = new Book;
      cop->name = it->second->name;
      cop->author = it->second->author;
      cop->pages = it->second->pages;

      answer[count] = cop;
      count++;
    }
  }
  return answer;
}

const Book *LibraryFileService::patch_book(unsigned const int &id,
                                           const Book &book) {
  std::vector<std::string> errors;

  std::string idf = std::to_string(id);
  std::string idfi = ".json";
  std::string idnr = "Books/";
  std::string newf = idf + idfi;

  std::string filepath = idnr + newf;
  Book *extr = m_books[id];

  if (book.name != "") {
    extr->name = book.name;
  }
  if (book.author != "") {
    extr->author = book.author;
  }
  if (book.pages > 0) {
    extr->pages = book.pages;
  }

  if (m_books.count(id) == 0) {
    errors.push_back("Id doesnt exist");
    throw errors;
  }
  if (!validate(*extr)) {
    errors.push_back("Book is invalid");
    throw errors;
  }
  if (dupchk_upd(*extr, id)) {
    errors.push_back("Book is a duplicate");
    throw errors;
  }

  m_books[id]->name = extr->name;
  m_books[id]->author = extr->author;
  m_books[id]->pages = extr->pages;
  json command;
  command["name"] = extr->name;
  command["author"] = extr->author;
  command["pages"] = extr->pages;
  std::string dump = command.dump();
  std::fstream pathcer;
  pathcer.open(filepath);
  pathcer.clear();
  pathcer << dump;
  pathcer.close();

  Book *cop = new Book;
  cop->name = extr->name;
  cop->author = extr->author;
  cop->pages = extr->pages;
  return cop;
}

const Book *LibraryFileService::update_book(unsigned const int &id,
                                            const Book &book) {
  std::vector<std::string> errors;

  std::string idf = std::to_string(id);
  std::string idfi = ".json";
  std::string idnr = "Books/";
  std::string newf = idf + idfi;

  std::string filepath = idnr + newf;

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

  json command;
  command["name"] = book.name;
  command["author"] = book.author;
  command["pages"] = book.pages;
  std::string dump = command.dump();
  std::fstream pathcer;
  pathcer.open(filepath);
  pathcer.clear();
  pathcer << dump;
  pathcer.close();
  Book *cop = new Book;
  cop->name = m_books[id]->name;
  cop->author = m_books[id]->author;
  cop->pages = m_books[id]->pages;
  return cop;
}

bool LibraryFileService::validate(const Book &book) {
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

bool LibraryFileService::delete_book(unsigned const int &id) {
  if (m_books.count(id) == 0) {
    return false;
  }
  std::string idf = std::to_string(id);
  std::string idfi = ".json";
  std::string idnr = "Books/";
  std::string newf = idf + idfi;

  std::string filepath = idnr + newf;

  remove(filepath.c_str()); // delete file
  delete m_books[id];
  m_books.erase(id);
  return true;
}
void LibraryFileService::delete_all_books() {
  std::unordered_map<int, Book *>::iterator it = m_books.begin();
  for (; it != m_books.end(); it++) {
    delete m_books[it->first];
  }
  m_books.erase(m_books.begin(), m_books.end());
  std::string dir_path = "Books";
  for (const auto &entry :
       std::filesystem::recursive_directory_iterator(dir_path))
    std::filesystem::remove_all(entry.path());
}

bool LibraryFileService::dupchk(const Book &book) {
  std::unordered_map<int, Book *>::iterator it = m_books.begin();
  for (; it != m_books.end(); it++) {
    if (it->second->name == book.name && it->second->author == book.author) {
      return true;
    }
  }
  return false;
}

void LibraryFileService::delete_condition(const std::string &name,
                                          const std::string &author,
                                          unsigned const int &pages) {
  std::unordered_map<int, Book *>::iterator it = m_books.begin();
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
      delete m_books[it->first];
      m_books.erase(it->first);
      std::string idf = std::to_string(it->first);
      std::string idfi = ".json";
      std::string idnr = "Books/";
      std::string newf = idf + idfi;

      std::string filepath = idnr + newf;
      std::remove(filepath.c_str());
    }
  }
}

bool LibraryFileService::dupchk_upd(const Book &book, int id) {
  if (m_books.count(id) == 0) {
    return false;
  }

  std::unordered_map<int, Book *>::iterator it = m_books.begin();
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

std::stringstream LibraryFileService::execute_command(Command &command) {
  std::stringstream stream;
  if (command.type == 6) {
    std::unordered_map<int, Book *>::iterator it = m_books.begin();
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
    }
    return stream;
  }

  if (command.type == 5) {
    const Book *book;
    try {
      book = find_book(command.id);
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

    std::cout << "\n             Book :             \n\r";
    std::cout << "-----------------------------------\n\n\r";
    std::cout << "name : " << book->name << "\n\n";
    std::cout << "author : " << book->author << "\n\n";
    std::cout << "pages : " << book->pages << "\n\n";
    std::cout << "id : " << command.id << "\n\n\n\r";

    stream << "\n             Book :             \n\r";
    stream << "-----------------------------------\n\n\r";
    stream << "name : " << book->name << "\n\n";
    stream << "author : " << book->author << "\n\n";
    stream << "pages : " << book->pages << "\n\n";
    stream << "id : " << command.id << "\n\n\n\r";

    return stream;
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
    }
    return stream;
  }

  if (command.type == 4) {
    std::string input = std::string();
    std::unordered_map<int, Book *> size =
        find_all_books(command.command["name"], command.command["author"],
                       command.command["pages"]);

    // Prompting user if they are sure about the consequenses
    std::cout << "Are You Sure About These ( " << size.size()
              << " books are being deleted ) [Y/n]";

    stream << "Are You Sure About These ( " << size.size()
           << " books are being deleted ) [Y/n]";

    bool em = false;
    if (size.size() == 0) {
      em = true;
    }
    getline(std::cin, input);
    std::cout << "\n\r";
    stream << "\n\r";
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
      patch_book(command.id, book);
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
      const Book *bookr = update_book(command.id, book);
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
    if (command.warning_log.size() == 1) {
      std::cout << "Delete Aborted\n\n\r";
      stream << "Delete Aborted\n\n\r";

      return stream;
    }
    delete_all_books();
    std::cout << "All Books Successfully Deleted\n\r";
    stream << "All Books Successfully Deleted\n\r";

    if (m_books.size() == 0) {
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
    try {
      create_book(createe);
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

void LibraryFileService::import(std::unordered_map<int, Book *> library,
                                int id) {
  m_books = library;
  this->last_id = id;
}
