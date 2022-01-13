
#ifndef _LIBRARY_LIBRARY_MANAGER_
#define _LIBRARY_LIBRARY_MANAGER_
#include "Book.hpp"
#include <unordered_map>
#include <vector>

class LibraryService {
public:
  int last_id = 0;
  std::unordered_map<int, Book *> m_books;
  bool validate(const Book &book);
  friend class LibraryServiceTests;

  const Book *create_book(const Book &book);

  const Book *find_book(unsigned const int &id);
  bool dupchk(const Book &book);
  const std::unordered_map<int, Book *>
  find_all_books(const std::string &name = "", const std::string &author = "",
                 unsigned const int &pages = 0);

  const Book *update_book(unsigned const int &id, const Book &book);

  void delete_book(unsigned const int &id);

  void delete_condition(const std::string &name = "",
                        const std::string &author = "",
                        unsigned const int &pages = 0);

  void delete_all_books();
};

#endif // _LIBRARY_LIBRARY_MANAGER_
