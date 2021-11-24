
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

bool LibraryServiceTests::Test_Creating_Invalid_book_With_No_pages() {
  LibraryService major_test_subject1;
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "ibrahim usmani";
  minor_test_subject1.pages = 0;
  if (major_test_subject1.create_book(minor_test_subject1) != nullptr) {
    return false;
  }

  return true;
}

bool LibraryServiceTests::Test_Creating_Invalid_book_With_No_Name() {
  LibraryService major_test_subject1;
  Book minor_test_subject1;
  minor_test_subject1.name = "";
  minor_test_subject1.author = "ibrahim usmani";
  minor_test_subject1.pages = 24;
  if (major_test_subject1.create_book(minor_test_subject1) != nullptr) {
    return false;
  }

  return true;
}

bool LibraryServiceTests::Test_Creating_Invalid_book_With_No_Author() {
  LibraryService major_test_subject1;
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "";
  minor_test_subject1.pages = 24;

  if (major_test_subject1.create_book(minor_test_subject1) != nullptr) {
    return false;
  }

  return true;
}

bool LibraryServiceTests::
    Test_Creating_Invalid_book_With_No_Letters_In_Author() {
  LibraryService major_test_subject1;
  // Creating book
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "4@391 / ?./ ";
  minor_test_subject1.pages = 24;
  // Check if not failed to create
  if (major_test_subject1.create_book(minor_test_subject1) != nullptr) {
    return false;
  }

  return true;
};

bool LibraryServiceTests::Test_Deleting_a_book() {
  LibraryService major_test_subject1;
  // Creating book
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "ibrahim usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  // Deleting book
  major_test_subject1.delete_book(1);
  if (major_test_subject1.m_books.size() != 0) {
    return false;
  }
  return true;
};

bool LibraryServiceTests::Test_Deleting_All_books() {
  LibraryService major_test_subject1;
  // Creating Book 1
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "ibrahim usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  // Creating Book 2
  Book minor_test_subject2;
  minor_test_subject1.name = "How To Be More Cool";
  minor_test_subject1.author = "Ibrahim Usmani";
  minor_test_subject1.pages = 45;
  major_test_subject1.create_book(minor_test_subject2);
  // Creating Book 3
  Book minor_test_subject3;
  minor_test_subject1.name = "How To Be Even More Cool";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject3);
  // Deleting all books
  major_test_subject1.delete_all_books();
  if (major_test_subject1.m_books.size() != 0) {
    return false;
  }
  return true;
}

bool LibraryServiceTests::Test_Deleting_Nonexistent_book() {
  LibraryService major_test_subject1;
  // Creating Book 1
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "ibrahim usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  // Creating Book 2
  Book minor_test_subject2;
  minor_test_subject1.name = "How To Be More Cool";
  minor_test_subject1.author = "Ibrahim Usmani";
  minor_test_subject1.pages = 45;
  major_test_subject1.create_book(minor_test_subject2);
  // Creating Book 3
  Book minor_test_subject3;
  minor_test_subject1.name = "How To Be Even More Cool";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject3);
  auto tmp = major_test_subject1.m_books;
  // Deleting Nonexistent book test
  major_test_subject1.delete_book(4);
  if (major_test_subject1.m_books != tmp) {
    return false;
  }
  return true;
}

bool LibraryServiceTests::Test_Updating_a_book() {
  LibraryService major_test_subject1;
  // Creating book
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  // Updated book
  Book major_test_subject2;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 26;
  major_test_subject1.create_book(minor_test_subject1);
  Book *major_test_subject3;
  major_test_subject3 = &major_test_subject2;
  // Updating book to updated book
  major_test_subject1.update_book(1, major_test_subject2);
  if (major_test_subject1.m_books[1] != major_test_subject3) {
    return false;
  }
  return true;
}

bool LibraryServiceTests::Test_Updating_Invalid_book_With_No_pages() {
  LibraryService major_test_subject1;
  // Creating book
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  // Updated book
  Book major_test_subject2;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 0;
  major_test_subject1.create_book(minor_test_subject1);
  Book *major_test_subject3;
  major_test_subject3 = &major_test_subject2;
  // Updating book to updated book
  if (major_test_subject1.update_book(1, major_test_subject2) != nullptr) {
    return false;
  }
  return true;
};

bool LibraryServiceTests::Test_Updating_Invalid_book_With_No_Name() {
  LibraryService major_test_subject1;
  // Creating book
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  // Updated book
  Book major_test_subject2;
  minor_test_subject1.name = "";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  Book *major_test_subject3;
  major_test_subject3 = &major_test_subject2;
  // Updating book to updated book
  if (major_test_subject1.update_book(1, major_test_subject2) != nullptr) {
    return false;
  }
  return true;
};

bool LibraryServiceTests::Test_Updating_Invalid_book_With_No_Author() {
  LibraryService major_test_subject1;
  // Creating book
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  // Updated book
  Book major_test_subject2;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  Book *major_test_subject3;
  major_test_subject3 = &major_test_subject2;
  // Updating book to updated book
  if (major_test_subject1.update_book(1, major_test_subject2) != nullptr) {
    return false;
  }
  return true;
};

bool LibraryServiceTests::
    Test_Updating_Invalid_book_With_No_Letters_In_Author() {
  LibraryService major_test_subject1;
  // Creating book
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  // Updated book
  Book major_test_subject2;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "1/[4518 &8&*7 ^5&471";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  Book *major_test_subject3;
  major_test_subject3 = &major_test_subject2;
  // Updating book to updated book
  if (major_test_subject1.update_book(1, major_test_subject2) != nullptr) {
    return false;
  }
  return true;
};

bool LibraryServiceTests::Test_Updating_Nonexistent_id() {
  LibraryService major_test_subject1;
  // Creating book
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  // Updated book
  Book minor_test_subject2;
  minor_test_subject2.name = "How To Be Cool";
  minor_test_subject2.author = "Iber999";
  minor_test_subject2.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  Book *major_test_subject3;
  major_test_subject3 = &minor_test_subject2;
  // Updating book to updated book
  if (major_test_subject1.update_book(5, minor_test_subject2) != nullptr) {
    return false;
  }
  return true;
};

bool LibraryServiceTests::Test_Finding_Nonexistent_book() {
  LibraryService major_test_subject1;
  // Creating book
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  // Finding Non Existent Book
  if (major_test_subject1.find_book(4) != nullptr) {
    return false;
  }
  return true;
}

bool LibraryServiceTests::Test_Find_Book() {
  LibraryService major_test_subject1;
  // Creating book
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  // Finding Non Existent Book
  if (major_test_subject1.find_book(1) != &minor_test_subject1) {
    return false;
  }
  return true;
}

bool LibraryServiceTests::Test_Finding_Conditions_with_nopages() {
  LibraryService major_test_subject1;
  // Creating book 1
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  // Creating Book 2
  Book minor_test_subject2;
  minor_test_subject1.name = "How To Be More Cool";
  minor_test_subject1.author = "Ibrahim Usmani";
  minor_test_subject1.pages = 45;
  major_test_subject1.create_book(minor_test_subject2);
  // Creating Book 3
  Book minor_test_subject3;
  minor_test_subject1.name = "How To Be Even More Cool";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject3);
  // Finding Conditions (Invalid Ofc)
  if (major_test_subject1
          .find_all_books("How To Be Cool", "Ibrahim Muhmud Usmani", 0)
          ->size() != 0) {
    return false;
  }

  return true;
};

bool LibraryServiceTests::Test_Finding_No_match() {
  LibraryService major_test_subject1;
  // Creating book 1
  Book minor_test_subject1;
  minor_test_subject1.name = "Funy";
  minor_test_subject1.author = "Lolster";
  minor_test_subject1.pages = 69;
  major_test_subject1.create_book(minor_test_subject1);
  // Creating book 2
  Book minor_test_subject2;
  minor_test_subject2.name = "YnuF";
  minor_test_subject2.author = "retsloL";
  minor_test_subject2.pages = 96;
  major_test_subject1.create_book(minor_test_subject2);
  // Creating book 3
  Book minor_test_subject3;
  minor_test_subject3.name = "The Universe and everything";
  minor_test_subject3.author = "You May Not Know who";
  minor_test_subject3.pages = 42;
  major_test_subject1.create_book(minor_test_subject3);
  // Creating book 4
  Book minor_test_subject4;
  minor_test_subject4.name = "The Devil";
  minor_test_subject4.author = "You know who";
  minor_test_subject4.pages = 666;
  // Creating book 5
  Book minor_test_subject5;
  minor_test_subject5.name = "Infinit";
  minor_test_subject5.author = "Forevr";
  minor_test_subject5.pages = 8;
  // Finding No Test_Finding_No_match
  if (major_test_subject1.find_all_books("coooool", "Foerev", 424)->size() !=
      0) {
    return false;
  }
  return true;
};

bool LibraryServiceTests::Test_Finding_All_Books() {
  // Creating book 1
  LibraryService major_test_subject1;
  Book minor_test_subject1;
  minor_test_subject1.name = "Funy";
  minor_test_subject1.author = "Lolster";
  minor_test_subject1.pages = 69;
  major_test_subject1.create_book(minor_test_subject1);
  // Creating book 2
  Book minor_test_subject2;
  minor_test_subject2.name = "YnuF";
  minor_test_subject2.author = "retsloL";
  minor_test_subject2.pages = 96;
  major_test_subject1.create_book(minor_test_subject2);
  // Creating book 3
  Book minor_test_subject3;
  minor_test_subject3.name = "The Universe and everything";
  minor_test_subject3.author = "You May Not Know who";
  minor_test_subject3.pages = 42;
  major_test_subject1.create_book(minor_test_subject3);
  // Creating book 4
  Book minor_test_subject4;
  minor_test_subject4.name = "The Devil";
  minor_test_subject4.author = "You know who";
  minor_test_subject4.pages = 666;
  // Creating book 5
  Book minor_test_subject5;
  minor_test_subject5.name = "Infinit";
  minor_test_subject5.author = "Forevr";
  minor_test_subject5.pages = 8;
  // Testing Finding_all_books
  if (major_test_subject1.find_all_books(, , ).size() != 5) {
    return false;
  }
  return true;
};

bool LibraryServiceTests::Test_Finding_No_Names_Cond() {
  // Creating book 1
  LibraryService major_test_subject1;
  Book minor_test_subject1;
  minor_test_subject1.name = "Funy";
  minor_test_subject1.author = "Beem";
  minor_test_subject1.pages = 18;
  major_test_subject1.create_book(minor_test_subject1);
  // Creating book 2
  Book minor_test_subject2;
  minor_test_subject2.name = "YnuF";
  minor_test_subject2.author = "Beem";
  minor_test_subject2.pages = 18;
  major_test_subject1.create_book(minor_test_subject2);
  // Creating book 3
  Book minor_test_subject3;
  minor_test_subject3.name = "The Universe and everything";
  minor_test_subject3.author = "Beem";
  minor_test_subject3.pages = 18;
  major_test_subject1.create_book(minor_test_subject3);
  // Creating book 4
  Book minor_test_subject4;
  minor_test_subject4.name = "The Devil";
  minor_test_subject4.author = "Beem";
  minor_test_subject4.pages = 18;
  // Creating book 5
  Book minor_test_subject5;
  minor_test_subject5.name = "Infinit";
  minor_test_subject5.author = "Beem";
  minor_test_subject5.pages = 18;
  // Testing Finding_all_books
  if (major_test_subject1.find_all_books(, "Beem", 18).size() != 5) {
    return false;
  }
  return true;
};

bool LibraryServiceTests::Test_Finding_No_Author_Cond() {
  // Creating book 1
  LibraryService major_test_subject1;
  Book minor_test_subject1;
  minor_test_subject1.name = "Reality be like";
  minor_test_subject1.author = "Beemy";
  minor_test_subject1.pages = 18;
  major_test_subject1.create_book(minor_test_subject1);
  // Creating book 2
  Book minor_test_subject2;
  minor_test_subject2.name = "Reality be like";
  minor_test_subject2.author = "Beema";
  minor_test_subject2.pages = 18;
  major_test_subject1.create_book(minor_test_subject2);
  // Creating book 3
  Book minor_test_subject3;
  minor_test_subject3.name = "Reality be like";
  minor_test_subject3.author = "Beemi";
  minor_test_subject3.pages = 18;
  major_test_subject1.create_book(minor_test_subject3);
  // Creating book 4
  Book minor_test_subject4;
  minor_test_subject4.name = "Reality be like";
  minor_test_subject4.author = "Beemu";
  minor_test_subject4.pages = 18;
  // Creating book 5
  Book minor_test_subject5;
  minor_test_subject5.name = "Reality be like";
  minor_test_subject5.author = "Beemo";
  minor_test_subject5.pages = 18;
  // Testing
  if (major_test_subject1.find_all_books("Reality be like", , 18).size() != 5) {
    return false;
  }
  return true;
};
bool LibraryServiceTests::Test_Finding_No_Page_Cond() {
  // Creating book 1
  LibraryService major_test_subject1;
  Book minor_test_subject1;
  minor_test_subject1.name = "Funy";
  minor_test_subject1.author = "CooL";
  minor_test_subject1.pages = 181;
  major_test_subject1.create_book(minor_test_subject1);
  // Testing
  if (major_test_subject1.find_all_books("Funy", "CooL", 181).size() != 1) {
    return false;
  }
  return true;
};

bool LibraryServiceTests::Test_Finding_No_Names_and_Author_Cond() {
  // Creating book 1
  LibraryService major_test_subject1;
  Book minor_test_subject1;
  minor_test_subject1.name = "Funy";
  minor_test_subject1.author = "Lolster";
  minor_test_subject1.pages = 666;
  major_test_subject1.create_book(minor_test_subject1);
  // Creating book 2
  Book minor_test_subject2;
  minor_test_subject2.name = "YnuF";
  minor_test_subject2.author = "retsloL";
  minor_test_subject2.pages = 666;
  major_test_subject1.create_book(minor_test_subject2);
  // Creating book 3
  Book minor_test_subject3;
  minor_test_subject3.name = "The Universe and everything";
  minor_test_subject3.author = "You May Not Know who";
  minor_test_subject3.pages = 666;
  major_test_subject1.create_book(minor_test_subject3);
  // Creating book 4
  Book minor_test_subject4;
  minor_test_subject4.name = "The Devil";
  minor_test_subject4.author = "You know who";
  minor_test_subject4.pages = 666;
  // Creating book 5
  Book minor_test_subject5;
  minor_test_subject5.name = "Infinit";
  minor_test_subject5.author = "Forevr";
  minor_test_subject5.pages = 666;
  // Testing
  if (major_test_subject1.find_all_books(, , 666).size() != 5) {
    return false;
  }
  return true;
};
bool LibraryServiceTests::Test_Finding_No_Names_and_Page_Cond() {
  // Creating book 1
  LibraryService major_test_subject1;
  Book minor_test_subject1;
  minor_test_subject1.name = "Funy";
  minor_test_subject1.author = "A normal person";
  minor_test_subject1.pages = 69;
  major_test_subject1.create_book(minor_test_subject1);
  // Creating book 2
  Book minor_test_subject2;
  minor_test_subject2.name = "YnuF";
  minor_test_subject2.author = "A normal person";
  minor_test_subject2.pages = 96;
  major_test_subject1.create_book(minor_test_subject2);
  // Creating book 3
  Book minor_test_subject3;
  minor_test_subject3.name = "The Universe and everything";
  minor_test_subject3.author = "A normal person";
  minor_test_subject3.pages = 42;
  major_test_subject1.create_book(minor_test_subject3);
  // Creating book 4
  Book minor_test_subject4;
  minor_test_subject4.name = "The Devil";
  minor_test_subject4.author = "A normal person";
  minor_test_subject4.pages = 666;
  // Creating book 5
  Book minor_test_subject5;
  minor_test_subject5.name = "Infinit";
  minor_test_subject5.author = "A normal person";
  minor_test_subject5.pages = 8;
  // Testing
  if (major_test_subject1.find_all_books(, "A normal person", ) != 5) {
    return false;
  }
  return true;
};
bool LibraryServiceTests::Test_Finding_No_Author_and_Pages_Cond() {
  // Creating book 1
  LibraryService major_test_subject1;
  Book minor_test_subject1;
  minor_test_subject1.name = "Funy";
  minor_test_subject1.author = "Lolster";
  minor_test_subject1.pages = 69;
  major_test_subject1.create_book(minor_test_subject1);
  // Creating book 2
  Book minor_test_subject2;
  minor_test_subject2.name = "Funy";
  minor_test_subject2.author = "retsloL";
  minor_test_subject2.pages = 96;
  major_test_subject1.create_book(minor_test_subject2);
  // Creating book 3
  Book minor_test_subject3;
  minor_test_subject3.name = "Funy";
  minor_test_subject3.author = "You May Not Know who";
  minor_test_subject3.pages = 42;
  major_test_subject1.create_book(minor_test_subject3);
  // Creating book 4
  Book minor_test_subject4;
  minor_test_subject4.name = "Funy";
  minor_test_subject4.author = "You know who";
  minor_test_subject4.pages = 666;
  // Creating book 5
  Book minor_test_subject5;
  minor_test_subject5.name = "Funy";
  minor_test_subject5.author = "Forevr";
  minor_test_subject5.pages = 8;
  // Testing
  if (major_test_subject1.find_all_books("Funy", , ).size() == 5) {
    return false;
  }
  return true;
};
bool LibraryServiceTests::Test_Finding_With_No_Letters_In_Author() {
  LibraryService major_test_subject1;
  // Creating book 1
  Book minor_test_subject1;
  minor_test_subject1.name = "Funy";
  minor_test_subject1.author = "Lolster";
  minor_test_subject1.pages = 69;
  major_test_subject1.create_book(minor_test_subject1);
  // testing
  if (major_test_subject1.find_all_books("Funy", "1232*$", 69) != 0) {
    return false;
  }
  return true;
};

// 75648884
