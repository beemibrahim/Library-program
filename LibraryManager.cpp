

#include "LibraryManager.hpp"

const Book *LibraryService::create_book(const Book &book) {
  if (!validate(book)) {
    return nullptr;
  }
  if (dupchk(book)) {
    return nullptr;
  }
  const Book *booky = &book;
  Book *bookyf = (Book *)booky;
  m_books[this->last_id + 1] = bookyf;
  Book *cool = m_books[this->last_id + 1];
  ++this->last_id;
  return bookyf;
}

const Book *LibraryService::find_book(unsigned const int &id) {
  if (m_books.count(id) == 0) {
    return nullptr;
  }
  int d = id;
  Book *booky = m_books[d];
  return booky;
}

const std::unordered_map<int, Book *>
LibraryService::find_all_books(const std::string &name,
                               const std::string &author,
                               unsigned const int &pages) {
  unordered_map<int, Book *> answer;
  int count = 0;
  unordered_map<int, Book *>::iterator it = m_books.begin();
  for (; it != m_books.end(); it++) {
    int valid = 0;
    if (name == "") {
      valid++;
    } else if (name == it->second->name) {
      valid++;
    }

    if (author == "") {
      valid++;
    } else if (author == it->second->author) {
      valid++;
    }

    if (pages == 0) {
      valid++;
    } else if (pages == it->second->pages) {
      valid++;
    }
    if (valid == 3) {
      answer[count] = it->second;
      count++;
    }
  }
  return answer;
}

const Book *LibraryService::update_book(unsigned const int &id,
                                        const Book &book) {
  void *ptr = (Book *)find_book(id);
  if (ptr == nullptr) {
    return nullptr;
  }

  ptr = (Book *)&book;
  if (!validate(book)) {
    return nullptr;
  }
  m_books[id] = (Book *)ptr;
  return (const Book *)ptr;
}

bool LibraryService::validate(const Book &book) {
  if (book.name.size() == 0) {
    return false;
  }
  if (book.author.size() == 0) {
    return false;
  }
  int count = 0;
  bool letchk = false;
  for (int i = 0; i < book.author.size(); i++) {
    if (book.author[i] == ' ') {
      continue;
    }
    if (book.author[i] > 47 && book.author[i] < 58) {
      ++count;
    }
    if ((book.author[i] >= 97 && book.author[i] <= 122) ||
        (book.author[i] >= 65 && book.author[i] <= 90)) {
      letchk = true;
    }
  }
  if (count == book.author.size() || letchk == false) {
    return false;
  }

  if (book.pages == 0) {
    return false;
  }
  return true;
}

void LibraryService::delete_book(unsigned const int &id) {
  if (m_books.count(id) == 0) {
    return;
  }
  m_books.erase(id);
}
void LibraryService::delete_all_books() {
  m_books.erase(m_books.begin(), m_books.end());
}

bool LibraryService::dupchk(const Book &book) {
  unordered_map<int, Book *>::iterator it = m_books.begin();
  for (; it != m_books.end(); it++) {
    if (it->second->name == book.name && it->second->author == book.author) {
      return true;
    }
  }
  return false;
}

void LibraryService::delete_condition(const std::string &name,
                                      const std::string &author,
                                      unsigned const int &pages) {
  unordered_map<int, Book *>::iterator it = m_books.begin();
  for (; it != m_books.end();) {
    int valid = 0;
    if (name == "") {
      valid++;
    } else if (name == it->second->name) {
      valid++;
    }

    if (author == "") {
      valid++;
    } else if (author == it->second->author) {
      valid++;
    }

    if (pages == 0) {
      valid++;
    } else if (pages == it->second->pages) {
      valid++;
    }
    if (valid == 3) {
      int erase = it->first;
      it++;
      m_books.erase(erase);
      continue;
    }
    it++;
  }
}
