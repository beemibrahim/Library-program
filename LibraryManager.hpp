
#ifndef _LIBRARY_LIBRARY_MANAGER_
#define _LIBRARY_LIBRARY_MANAGER_
#include "Book.hpp"
#include "Command.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

class LibraryService {
public:
  int last_id = 0;
  std::unordered_map<int, Book> m_books;
  bool validate(const Book &book);
  std::string readFileIntoString(const std::string &path);

  friend class LibraryServiceTests;

  void create_book(const Book &book);
  std::stringstream execute_command(Command &command);

  Book find_book(unsigned const int &id);
  bool dupchk(const Book &book);
  bool dupchk_upd(const Book &book, int id);
  const std::unordered_map<int, Book>
  find_all_books(const std::string &name = "", const std::string &author = "",
                 unsigned const int &pages = 0);

  const Book update_book(unsigned const int &id, const Book &book);
  const Book patch_book(unsigned const int &id, const Book &book);

  bool delete_book(unsigned const int &id);

  void delete_condition(const std::string &name = "",
                        const std::string &author = "",
                        unsigned const int &pages = 0);

  void delete_all_books();
  void extract();
};

#endif // _LIBRARY_LIBRARY_MANAGER_
