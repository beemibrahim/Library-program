#include "LibraryManagerTests.hpp"

int main() {
  LibraryServiceTests tester;
  // Create tests
  cout << std::boolalpha;
  cout << "Creating a book : " << tester.Test_Creating_a_book() << "\n\n";
  cout << "Creating An Invalid Book With No Pages : "
       << tester.Test_Creating_Invalid_book_With_No_pages() << "\n\n";
  cout << "Creating Invalid Book With No Name : "
       << tester.Test_Creating_Invalid_book_With_No_Name() << "\n\n";
  cout << "Creating Invalid Book With No Author : "
       << tester.Test_Creating_Invalid_book_With_No_Author() << "\n\n";
  cout << "Creating Invalid Book With No letters in Author : "
       << tester.Test_Creating_Invalid_book_With_No_Letters_In_Author()
       << "\n\n";
  // delete tests
  cout << "Deleting Book : " << tester.Test_Deleting_a_book() << "\n\n";
  cout << "Deleting All Book : " << tester.Test_Deleting_All_books() << "\n\n";
  cout << "Testing Delete Nonexistent Book : "
       << tester.Test_Deleting_Nonexistent_book() << "\n\n";
  // update tests
  cout << "Updating a book : " << tester.Test_Updating_a_book() << "\n\n";
  cout << "Updating Invalid Book With No Pages : "
       << tester.Test_Updating_Invalid_book_With_No_pages() << "\n\n";
  cout << "Updating Invalid Book With No Name : "
       << tester.Test_Updating_Invalid_book_With_No_Name() << "\n\n";
  cout << "Updating Invalid Book With No Author : "
       << tester.Test_Updating_Invalid_book_With_No_Author() << "\n\n";
  cout << "Updating Invalid Book With No Letters in Author : "
       << tester.Test_Updating_Invalid_book_With_No_Letters_In_Author()
       << "\n\n";
  cout << "Updating Non Existent id : " << tester.Test_Updating_Nonexistent_id()
       << "\n\n";
  // find tests
  cout << "Finding Nonexistent Book : "
       << tester.Test_Finding_Nonexistent_book() << "\n\n";
  cout << "Finding Book : " << tester.Test_Find_Book() << "\n\n";
  // find_all_tests
  cout << "Finding Invalid Conditions With No Pages : "
       << tester.Test_Finding_Conditions_with_nopages() << "\n\n";
  cout << "Finding No Matching Conditions : " << tester.Test_Finding_No_match()
       << "\n\n";
  cout << "Finding All Books : " << tester.Test_Finding_All_Books() << "\n\n";
  cout << "Finding Invalid Conditions With No Names : "
       << tester.Test_Finding_No_Names_Cond() << "\n\n";
  cout << "Finding Invalid Conditions With No Author : "
       << tester.Test_Finding_No_Author_Cond() << "\n\n";
  cout << "Finding Conditions Excluding Page Number : "
       << tester.Test_Finding_No_Page_Cond() << "\n\n";
  cout << "Finding Conditions Excluding Page Number & Author : "
       << tester.Test_Finding_No_Names_and_Author_Cond() << "\n\n";
  cout << "Finding Conditions Excluding Name & Page Number : "
       << tester.Test_Finding_No_Names_and_Page_Cond() << "\n\n";
  cout << "Finding Conditions Excluding Author & Page Number : "
       << tester.Test_Finding_No_Author_and_Pages_Cond() << "\n\n";
  cout << "Finding Invalid Conditions No Letters In Author : "
       << tester.Test_Finding_With_No_Letters_In_Author();
}
