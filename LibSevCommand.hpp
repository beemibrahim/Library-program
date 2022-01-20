#ifndef _LIBSERV
#define _LIBSERV

#include "Book.hpp"
#include <unordered_map>
class LibSev {
public:
  const Book *ret;
  std::string error_log = std::string();
  std::string warning_log = std::string();
  bool func;
  const std::unordered_map<int, Book *> reta =
      std::unordered_map<int, Book *>();
};

#endif // _LIBSERV
