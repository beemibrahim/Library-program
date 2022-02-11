#include "Book.hpp"
#include <fstream>
#include <iostream>
#include <sqlite/connection.hpp>
#include <sqlite/execute.hpp>
#include <sqlite/query.hpp>
#include <sstream>
#include <string>
#include <unordered_map>

class LibraryDatabaseService {
  int last_id;

public:
  bool validate(const Book &book);
  const Bookwid *create_book(const Book &book);

  const Book *find_book(unsigned const int &id);
  bool dupchk(const Book &book);
  bool dupchk_upd(const Book &book, int id);
  const std::unordered_map<int, Book *>
  find_all_books(const std::string &name = "", const std::string &author = "",
                 unsigned const int &pages = 0);
  bool are_existing_books();

  const Book *update_book(unsigned const int &id, const Book &book);
  const Book *patch_book(unsigned const int &id, const Book &book);

  bool delete_book(unsigned const int &id);

  void delete_condition(const std::string &name = "",
                        const std::string &author = "",
                        unsigned const int &pages = 0);

  void delete_all_books();
  void import();
};
