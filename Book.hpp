
#ifndef _LIBRARY_BOOK_
#define _LIBRARY_BOOK_
#include "Library.hpp"
#include <string>

class Book {
public:
  int id = 0;
  std::string name;
  std::string author;
  int pages = 0;
};

#endif // _LIBRARY_BOOK_
