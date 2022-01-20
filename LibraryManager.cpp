#include "LibraryManager.hpp"
LibSev LibraryService::create_book(const Book &book) {
  LibSev exi;
  if (!validate(book)) {
    exi.error_log.push_back("Book is invalid");
    exi.func = true;
    return exi;
  }
  if (dupchk(book)) {
    exi.error_log.push_back("Book is a duplicate");
    exi.func = true;
    return exi;
  }
  Book *bookt = new Book;
  bookt->name = book.name;
  bookt->author = book.author;
  bookt->pages = book.pages;
  m_books[this->last_id + 1] = bookt;
  ++this->last_id;
  exi.ret = bookt;
  return exi;
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

LibSev LibraryService::patch_book(unsigned const int &id, const Book &book) {
  LibSev exi;

  Book extr = *m_books[id];
  if (m_books.count(id) == 0) {
    exi.error_log.push_back("Id doesnt exist");
    exi.func = true;
    return exi;
  }

  if (book.name != "") {
    extr.name = book.name;
  }
  if (book.author != "") {
    extr.author = book.author;
  }
  if (book.pages > 0) {
    extr.pages = book.pages;
  }

  if (!validate(extr)) {
    exi.error_log.push_back("Book is invalid");
    exi.func = true;
    return exi;
  }
  if (dupchk_upd(extr, id)) {
    exi.error_log.push_back("Book is a duplicate");
    exi.func = true;
    return exi;
  }

  if (book.name != "") {
    m_books[id]->name = book.name;
  }
  if (book.author != "") {
    m_books[id]->author = book.author;
  }
  if (book.pages > 0) {
    m_books[id]->pages = book.pages;
  }

  return m_books[id];
}

LibSev LibraryService::update_book(unsigned const int &id, const Book &book) {
  LibSev exi;

  if (m_books.count(id) == 0) {
    exi.error_log.push_back("Id doesnt exist");
    exi.func = true;
    return exi;
  }

  if (!validate(book)) {
    exi.error_log.push_back("Book is invalid");
    exi.func = true;
    return exi;
  }
  if (dupchk_upd(book, id)) {
    exi.error_log.push_back("Book is a duplicate");
    exi.func = true;
    return exi;
  }

  m_books[id]->name = book.name;
  m_books[id]->author = book.author;
  m_books[id]->pages = book.pages;

  return m_books[id];
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

bool LibraryService::delete_book(unsigned const int &id) {
  if (m_books.count(id) == 0) {
    return false;
  }
  delete m_books[id];
  m_books.erase(id);
  return true;
}
void LibraryService::delete_all_books() {
  unordered_map<int, Book *>::iterator it = m_books.begin();

  for (; it != m_books.end(); it++) {
    delete m_books[it->first];
  }

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
      delete m_books[it->first];
      m_books.erase(erase);
      continue;
    }
    it++;
  }
}

bool LibraryService::dupchk_upd(const Book &book, int id) {
  if (m_books.count(id) == 0) {
    return false;
  }

  unordered_map<int, Book *>::iterator it = m_books.begin();
  for (; it != m_books.end(); it++) {
    if (it->first == id) {
      continue;
    }
    if (it->second->name == book.name && it->second->author == book.author) {
      return true;
    }
  }
  return false;
}
