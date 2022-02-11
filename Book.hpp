
#ifndef _LIBRARY_BOOK_
#define _LIBRARY_BOOK_

#include <string>
class Book {
public:
  std::string name;
  std::string author;
  unsigned int pages = 0;
};

class Bookwid {
public:
  std::string name;
  std::string author;
  unsigned int pages = 0;
  int id;
};

#endif // _LIBRARY_BOOK_
