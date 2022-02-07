
#ifndef _LIBRARY_FILE_MANAGER_
#define _LIBRARY_FILE_MANAGER_
#include "Book.hpp"
#include "Command.hpp"
#include "LibraryService.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
class LibraryFileService : public LibraryService {
  /* IMPORTANT NOTE :  The caller of these functions are responbilites for
   freeing the Book pointers that are returned :

   .create_book()

   .find_book()

   .find_all_books() <----- iterate over it

   .update_book()

   .patch_book()
   */

  int last_id = 0;
  std::unordered_map<int, Book *> m_books;

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

#endif // _LIBRARY_FILE_MANAGER_
