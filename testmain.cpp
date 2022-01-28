#include "LibraryManager.hpp"

int main() {
  LibraryService services;

  Book book;
  book.name = "Hello";
  book.author = "Cool";
  book.pages = 45;
  services.create_book(book);
}
