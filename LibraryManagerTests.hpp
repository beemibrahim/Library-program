#include "LibraryManager.hpp"
#include <iostream>
class LibraryServiceTests {
public:
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
  bool Test_Finding_Nonexistent_book();
  bool Test_Find_Book();
  // find_all_tests
  bool Test_Finding_Conditions_with_nopages();
  bool Test_Finding_No_match();
  bool Test_Finding_All_Books();
  bool Test_Finding_No_Names_Cond();
  bool Test_Finding_No_Author_Cond();
  bool Test_Finding_No_Page_Cond();
  bool Test_Finding_No_Names_and_Author_Cond();
  bool Test_Finding_No_Names_and_Page_Cond();
  bool Test_Finding_No_Author_and_Pages_Cond();
  bool Test_Finding_With_No_Letters_In_Author();
};
