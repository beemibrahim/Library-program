
#ifndef _LIBRARY_LIBRARY_MANAGER_
#define _LIBRARY_LIBRARY_MANAGER_
#include "Book.hpp"
#include <vector>

class LibraryManager {
private:
  std::vector<Book *> m_books;
  bool validate(const Book &book);

public:
  Book *create_book(const Book &book);

  Book *find_book(int id);
  std::vector<Book *> *find_all_books(const std::string &name = "",
                                      const std::string &author = "",
                                      int pages = -1);

  Book *update_book(int id, const Book &book);

  void delete_book(int id);
  void delete_all_books();
};

#endif // _LIBRARY_LIBRARY_MANAGER_
