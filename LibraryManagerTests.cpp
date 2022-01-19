#include "LibraryManager.hpp"
#include <gtest/gtest.h>
/*
 // create tests


  bool Test_Creating_a_book();
  bool Test_Creating_Invalid_book_With_No_pages();
  bool Test_Creating_Invalid_book_With_No_Name();
  bool Test_Creating_Invalid_book_With_No_Author();
  bool Test_Creating_Invalid_book_With_No_Letters_In_Author();


  // delete tests


  bool Test_Deleting_a_book();
  bool Test_Deleting_All_books();
  bool Test_Deleting_Nonexistent_book();


  // update tests



  bool Test_Updating_a_book();
  bool Test_Updating_Invalid_book_With_No_pages();
  bool Test_Updating_Invalid_book_With_No_Name();
  bool Test_Updating_Invalid_book_With_No_Author();
  bool Test_Updating_Invalid_book_With_No_Letters_In_Author();
  bool Test_Updating_Nonexistent_id();


  // find tests

  bool Test_Find_Book();
  bool Test_Finding_Nonexistent_book();


  // find_all_tests

  bool Test_Finding_No_match();
  bool Test_Finding_All_Books();
  bool Test_Finding_No_Names_Cond();
  bool Test_Finding_No_Author_Cond();
  bool Test_Finding_No_Page_Cond();
  bool Test_Finding_No_Names_and_Author_Cond();
  bool Test_Finding_No_Names_and_Page_Cond();
  bool Test_Finding_No_Author_and_Pages_Cond();

*/

TEST(CreateTests, NormalCreate) {
  LibraryService major_test_subject1;
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "ibrahim usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  EXPECT_EQ(1, major_test_subject1.m_books.count(1));
}

TEST(CreateTests, CreateInvalid_No_Pages) {
  LibraryService major_test_subject1;
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "ibrahim usmani";
  minor_test_subject1.pages = 0;
  EXPECT_EQ(nullptr, major_test_subject1.create_book(minor_test_subject1));
}

TEST(CreateTests, CreateInvalid_No_Name) {
  LibraryService major_test_subject1;
  Book minor_test_subject1;
  minor_test_subject1.name = "";
  minor_test_subject1.author = "ibrahim usmani";
  minor_test_subject1.pages = 24;
  EXPECT_EQ(nullptr, major_test_subject1.create_book(minor_test_subject1));
}

TEST(CreateTests, CreateInvalid_No_Author) {
  LibraryService major_test_subject1;
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "";
  minor_test_subject1.pages = 24;
  EXPECT_EQ(nullptr, major_test_subject1.create_book(minor_test_subject1));
}

TEST(CreateTests, Create_NoLetters_Author) {
  LibraryService major_test_subject1;
  // Creating book
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "4@391 / ?./ ";
  minor_test_subject1.pages = 24;
  // Check if not failed to create
  EXPECT_EQ(nullptr, major_test_subject1.create_book(minor_test_subject1));
}

TEST(DeleteTests, NormalDelete) {
  LibraryService major_test_subject1;
  // Creating book
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "ibrahim usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  // Deleting book
  major_test_subject1.delete_book(1);
  EXPECT_EQ(0, major_test_subject1.m_books.size());
}

TEST(DeleteTests, DeleteAll) {
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
  EXPECT_EQ(0, major_test_subject1.m_books.size());
}

TEST(DeleteTests, Delete_Nonexist) {
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
  EXPECT_EQ(tmp, major_test_subject1.m_books);
}

TEST(UpdateTests, NormalUpdate) {
  LibraryService major_test_subject1;
  // Creating book
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  // Updated book
  Book major_test_subject2;
  major_test_subject2.name = "How To Be Cool";
  major_test_subject2.author = "Ibrahim Muhmud Usmani";
  major_test_subject2.pages = 26;
  Book *major_test_subject3 = &major_test_subject2;
  // Updating book to updated book
  const Book *ans = major_test_subject1.update_book(1, major_test_subject2);
  const Book *answ = major_test_subject1.m_books[1];
  EXPECT_EQ(major_test_subject3->name, major_test_subject1.m_books[1]->name);
  EXPECT_EQ(major_test_subject3->author,
            major_test_subject1.m_books[1]->author);
  EXPECT_EQ(major_test_subject3->pages, major_test_subject1.m_books[1]->pages);
}

TEST(UpdateTests, UpdateInvalid_Nopages) {
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
  EXPECT_EQ(nullptr, major_test_subject1.update_book(1, major_test_subject2));
}

TEST(UpdateTests, UpdateInvalid_NoName) {
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
  EXPECT_EQ(nullptr, major_test_subject1.update_book(1, major_test_subject2));
}

TEST(UpdateTests, UpdateInvalid_NoAuthor) {
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
  EXPECT_EQ(nullptr, major_test_subject1.update_book(1, major_test_subject2));
}

TEST(UpdateTests, UpdateInvalid_NoLetters_author) {
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
  EXPECT_EQ(nullptr, major_test_subject1.update_book(1, major_test_subject2));
}

TEST(UpdateTests, UpdateNon_ExisID) {
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
  EXPECT_EQ(nullptr, major_test_subject1.update_book(5, minor_test_subject2));
}

TEST(FindTests, NormalFind) {
  LibraryService major_test_subject1;
  // Creating book
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  // Finding
  EXPECT_EQ(minor_test_subject1.name, major_test_subject1.find_book(1)->name);
  EXPECT_EQ(minor_test_subject1.author,
            major_test_subject1.find_book(1)->author);
  EXPECT_EQ(minor_test_subject1.pages, major_test_subject1.find_book(1)->pages);
}

TEST(FindTests, FindNonExis_Book) {
  LibraryService major_test_subject1;
  // Creating book
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  // Finding Non Existent Book
  EXPECT_EQ(nullptr, major_test_subject1.find_book(4));
}

TEST(FindCond_Tests, Find_NoMatch) {
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
  EXPECT_EQ(
      0, major_test_subject1.find_all_books("coooool", "Foerev", 424).size());
}

TEST(FindCond_Tests, FindAll) {
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
  major_test_subject1.create_book(minor_test_subject4);
  // Creating book 5
  Book minor_test_subject5;
  minor_test_subject5.name = "Infinit";
  minor_test_subject5.author = "Forevr";
  minor_test_subject5.pages = 8;
  major_test_subject1.create_book(minor_test_subject5);
  // Testing Finding_all_books
  EXPECT_EQ(5, major_test_subject1.find_all_books("", "", 0).size());
}

TEST(FindCond_Tests, Find_NoName_Cond) {
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
  major_test_subject1.create_book(minor_test_subject4);
  // Creating book 5
  Book minor_test_subject5;
  minor_test_subject5.name = "Infinit";
  minor_test_subject5.author = "Beem";
  minor_test_subject5.pages = 18;
  major_test_subject1.create_book(minor_test_subject5);
  // Testing Finding_all_books
  EXPECT_EQ(5, major_test_subject1.find_all_books("", "Beem", 18).size());
}

TEST(FindCond_Tests, Find_NoAuthor_Cond) {
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
  major_test_subject1.create_book(minor_test_subject4);
  // Creating book 5
  Book minor_test_subject5;
  minor_test_subject5.name = "Reality be like";
  minor_test_subject5.author = "Beemo";
  minor_test_subject5.pages = 18;
  major_test_subject1.create_book(minor_test_subject5);
  // Testing
  EXPECT_EQ(
      5, major_test_subject1.find_all_books("Reality be like", "", 18).size());
}

TEST(FindCond_Tests, Find_NoPage_Cond) {
  LibraryService major_test_subject1;
  // Creating book 1
  Book minor_test_subject1;
  minor_test_subject1.name = "How To Be Cool";
  minor_test_subject1.author = "Ibrahim Muhmud Usmani";
  minor_test_subject1.pages = 24;
  major_test_subject1.create_book(minor_test_subject1);
  EXPECT_EQ(1, major_test_subject1
                   .find_all_books("How To Be Cool", "Ibrahim Muhmud Usmani", 0)
                   .size());
}

TEST(FindCond_Tests, Find_NoName_Author_Cond) {
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
  major_test_subject1.create_book(minor_test_subject4);
  // Creating book 5
  Book minor_test_subject5;
  minor_test_subject5.name = "Infinit";
  minor_test_subject5.author = "Forevr";
  minor_test_subject5.pages = 666;
  major_test_subject1.create_book(minor_test_subject5);
  // Testing
  EXPECT_EQ(5, major_test_subject1.find_all_books("", "", 666).size());
}

TEST(FindCond_Tests, No_Name_Page_Cond) {
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
  major_test_subject1.create_book(minor_test_subject4);
  // Creating book 5
  Book minor_test_subject5;
  minor_test_subject5.name = "Infinit";
  minor_test_subject5.author = "A normal person";
  minor_test_subject5.pages = 8;
  major_test_subject1.create_book(minor_test_subject5);
  EXPECT_EQ(
      5, major_test_subject1.find_all_books("", "A normal person", 0).size());
}

TEST(FindCond_Tests, Find_No_Author_Page_Cond) { // Creating book 1
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
  major_test_subject1.create_book(minor_test_subject4);

  // Creating book 5
  Book minor_test_subject5;
  minor_test_subject5.name = "Funy";
  minor_test_subject5.author = "Forevr";
  minor_test_subject5.pages = 8;
  major_test_subject1.create_book(minor_test_subject5);
  EXPECT_EQ(5, major_test_subject1.find_all_books("Funy", "", 0).size());
}

// 75648884
