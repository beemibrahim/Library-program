

#include "LibraryManager.hpp"

Book *LibraryManager::create_book(const Book &book) {
  if (!validate(book)) {
  }
  Book booky = book;
  Book *bookyf = &booky;
  return bookyf;
}

Book *LibraryManager::find_book(int id) {
  int start = 0;
  int end = m_books.size() - 1;
  int middle = 0;
  for (;;) {
    middle = (start - end) / 2;
    if (m_books[middle]->id > id) {
      start = middle;
    } else if (m_books[middle]->id < id) {
      end = middle;
    } else if (m_books[middle]->id == id) {
      return m_books[middle];
    }
    if (middle == start || middle == end) {
      printf("Book not found");
      printf("\n");
      return nullptr;
    }
  }
}

std::vector<Book *> *LibraryManager::find_all_books(const std::string &name,
                                                    const std::string &author,
                                                    int pages) {
  vector<Book *> *answer;
  bool valid = false;
  for (int i = 0; i < m_books.size(); i++) {
    if (name == "") {
      valid = true;
    } else if (name == m_books[i]->name) {
    }
  }
  return answer;
}

bool validate(const Book &book) {
  if (book.name.size() == 0) {
    return false;
  }
  if (book.author.size() == 0) {
    return false;
  }
  if (book.pages == 0) {
    return false;
  }
  return true;
}
