#include "Library_DatabaseService.hpp"

const Bookwid *LibraryDatabaseService::create_book(const Book &book) {
  std::vector<std::string> errors;
  if (!validate(book)) {
    errors.push_back("Book is invalid");
    throw errors;
  }
  if (dupchk(book)) {
    errors.push_back("Book is a duplicate");
    throw errors;
  }

  std::ifstream input_file("ServerStorage/last_id.txt");
  std::string ids = std::string((std::istreambuf_iterator<char>(input_file)),
                                std::istreambuf_iterator<char>());
  int newid = stoi(ids);
  newid += 1;
  last_id += 1;
  sqlite::connection con("ServerStorage/library.db");
  sqlite::execute ins(con, "INSERT INTO library VALUES(? , ? , ? , ?);");

  ins % newid % book.name % book.author % (int)book.pages;

  ins();
  std::fstream file;
  file.open("ServerStorage/last_id.txt",
            std::ofstream::out | std::ofstream::trunc);
  file << newid;

  Bookwid *ptr = new Bookwid;
  ptr->name = book.name;
  ptr->author = book.author;
  ptr->pages = book.pages;
  ptr->id = newid;
  return ptr;
}

const Book *LibraryDatabaseService::find_book(unsigned const int &id) {

  Book *boor = new Book;
  char *err = 0;
  sqlite::connection con("ServerStorage/library.db");
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
  sqlite::connection con("ServerStorage/library.db");
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
  sqlite::connection con("ServerStorage/library.db");
  sqlite::query q(con, "SELECT * FROM library WHERE id = ?;");
  q % (int)id;
  q();
  boost::shared_ptr<sqlite::result> result = q.get_result();

  if (result->get_string(1) == "NULL") {
    errors.push_back("Id doesnt exist");
    throw errors;
  }

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
      con, "UPDATE library SET name = ?,author = ?,pages = ? WHERE id = ?;");
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
  std::vector<std::string> errors;
  sqlite::connection con("ServerStorage/library.db");

  if (find_book(id) == nullptr) {
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

  sqlite::execute ins(
      con, "UPDATE library SET name = ?,author = ?,pages = ? WHERE id = ?;");
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
  sqlite::connection con("ServerStorage/library.db");
  sqlite::execute ins(con, "DELETE FROM library WHERE id = ?;");
  ins % (int)id;
  ins();
  return true;
}

bool LibraryDatabaseService::are_existing_books() {
  sqlite::connection con("ServerStorage/library.db");

  sqlite::query q(con, "SELECT * FROM library limit 1;");
  boost::shared_ptr<sqlite::result> result = q.get_result();

  bool em = false;
  if (!result->next_row())
    em = true;

  return em;
}

void LibraryDatabaseService::delete_all_books() {
  sqlite::connection con("ServerStorage/library.db");
  sqlite::execute del(con, "delete from library;");
  del();
}

bool LibraryDatabaseService::dupchk(const Book &book) {
  sqlite::connection con("ServerStorage/library.db");

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
  sqlite::connection con("ServerStorage/library.db");
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

  sqlite::connection con("ServerStorage/library.db");
  sqlite::query q(con, "SELECT * FROM library where name = ? AND author = ?;");
  int al = 0;
  q % book.name % book.author;
  q();
  boost::shared_ptr<sqlite::result> result = q.get_result();
  if (result->get_string(1) == "NULL") {
    return false;
  }

  return true;
}

void LibraryDatabaseService::import() {
  std::ifstream input_file("ServerStorage/last_id.txt");
  std::string ids = std::string((std::istreambuf_iterator<char>(input_file)),
                                std::istreambuf_iterator<char>());
  int idf = stoi(ids);
  last_id = idf;
  return;
}
