#include "Book.hpp"
#include "Command.hpp"
#include <iostream>
#include <sqlite/connection.hpp>
#include <sqlite/execute.hpp>
#include <sqlite/query.hpp>
class LibraryDatabaseService {

public:
  bool validate(const Book &book);
  const Book *create_book(const Book &book);
  std::stringstream execute_command(Command &command);

  const Book *find_book(unsigned const int &id);
  bool dupchk(const Book &book);
  bool dupchk_upd(const Book &book, int id);
  const std::unordered_map<int, Book *>
  find_all_books(const std::string &name = "", const std::string &author = "",
                 unsigned const int &pages = 0);

  const Book *update_book(unsigned const int &id, const Book &book);
  const Book *patch_book(unsigned const int &id, const Book &book);

  bool delete_book(unsigned const int &id);

  void delete_condition(const std::string &name = "",
                        const std::string &author = "",
                        unsigned const int &pages = 0);

  void delete_all_books();
  void import(std::unordered_map<int, Book *> library, int id);
};
