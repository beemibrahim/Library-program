#include "LibraryManagerTests.hpp"
bool LibraryServiceTests::Test_Creating_a_book() {
  LibraryService major_test_subject1;
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "ibrahim usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  if (major_test_subject1.m_books.count(1) == 0) {
    std::cout << "Error : book didnt exist ??";
    return false;
  }
  if (major_test_subject1.m_books[1]->name != "How To Be Cool" ||
      major_test_subject1.m_books[1]->author != "ibrahim usmani" ||
      major_test_subject1.m_books[1]->pages != 24) {
    std::cout << "Error : Book didnt have the correct values ??";
    return false;
  }
  return true;
}
