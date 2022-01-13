#include "Userinput.hpp"
#include <gtest/gtest.h>
/*
  // create
   NormalCreate();
   NormalCreate_Non_Exisfile();
  NormalCreate_Non_JsonFile();
   NormalCreate_NonsenseJson();
   InvalidCreate_WrongJsonObj();
   InvalidCreate_WrongJsonType();
   InvalidCreate_NotLettersinAtuhor();
   InvalidCreate_Pagesiszero();
   InvalidCreate_emptyname();
   InvalidCreate_emptyauthor();

  // find
   NormalFind();
   Find_NonSense();

  // find condition
   FindNormal_Cond();
   Find_NonJson_File();
   Find_NonExist_File();
   Find_NonsenseJson();
   Find_WrongObj();

  // delete
   delete_book();
   Delete_Nonsense();
   Delete_All();

   // delete_Cond
   DeleteNormal_Cond();
   Delete_NonJson_File();
   Delete_NonExist_File();
   Delete_NonsenseJson();
   Delete_WrongObj();

  // update
   NormalUpdate();
   Update_Non_Exisfile();
   Update_Non_JsonFile();
   Update_NonsenseJson();
   Update_WrongJsonObj();
   Update_WrongJsonType();
   Update_NotLettersinAuthor();
   Update_Pagesiszero();
   Update_emptyname();
   Update_emptyauthor();
*/

TEST(InputCreate, NormalCreate) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput("create "
                               "/home/ibrahim/code/github/beemibrahim/"
                               "Library-program/JsontestFiles/testfile.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(1, major_test_subject2.type);
  EXPECT_EQ(false, major_test_subject2.fail);
}

TEST(InputCreate, Create_NonExisFile) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput("create "
                               "/home/ibrahim/code/github/beemibrahim/"
                               "Library-program/testfilefish.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(InputCreate, Create_NonJson) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput("create "
                               "/home/ibrahim/code/github/beemibrahim/"
                               "Library-program/Library.cpp");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(InputCreate, Create_NonsenseJson) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput("create "
                               "/home/ibrahim/code/github/beemibrahim/"
                               "Library-program/JsontestFiles/Nonsense.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(InputCreate, Create_WrongObj) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput("create "
                               "/home/ibrahim/code/github/beemibrahim/"
                               "Library-program/JsontestFiles/Wrongobj.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(InputCreate, WrongJsonType) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput("create "
                               "/home/ibrahim/code/github/beemibrahim/"
                               "Library-program/JsontestFiles/Wrongobj.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(InputCreate, NoLetters_Author) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput(
      "create "
      "/home/ibrahim/code/github/beemibrahim/"
      "Library-program/JsontestFiles/NoLettersAuthor.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(InputCreate, Pages_IsZero) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput(
      "create "
      "/home/ibrahim/code/github/beemibrahim/"
      "Library-program/JsontestFiles/pagesiszero.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(InputCreate, EmptyName) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput("create "
                               "/home/ibrahim/code/github/beemibrahim/"
                               "Library-program/JsontestFiles/emptyname.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(InputCreate, EmptyAuthor) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput(
      "create "
      "/home/ibrahim/code/github/beemibrahim/"
      "Library-program/JsontestFiles/emptyauthor.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(InputFind, NormalFind) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput("find 5");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(false, major_test_subject2.fail);
  EXPECT_EQ(5, major_test_subject2.type);
}

TEST(InputFind, Find_NonSense) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput("find coolination");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(InputFind_Cond, FindNormal_Cond) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput(
      "find "
      "/home/ibrahim/code/github/beemibrahim/"
      "Library-program/JsontestFiles/NormalFindCond.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(false, major_test_subject2.fail);
}

TEST(InputFind_Cond, Find_NonJson_File) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput(
      "find /home/ibrahim/code/github/beemibrahim/Library-program/Library.hpp");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(InputFind_Cond, Find_NonExist_File) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput(
      "find /home/ibrahim/code/github/beemibrahim/Library-program/Del.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(InputFind_Cond, Find_NonsenseJson) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput("find "
                               "/home/ibrahim/code/github/beemibrahim/"
                               "Library-program/JsontestFiles/Nonsense.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(InputFind_Cond, FindWrongObj) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput("find "
                               "/home/ibrahim/code/github/beemibrahim/"
                               "Library-program/JsontestFiles/Wrongobj.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(Delete_Books, NormalDelete) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput("delete 5");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(5, major_test_subject2.id);
  EXPECT_EQ(false, major_test_subject2.fail);
  EXPECT_EQ(2, major_test_subject2.type);
}

TEST(Delete_Books, DeleteNonsense) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput("delete coolianrion");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
  EXPECT_EQ(2, major_test_subject2.type);
}

TEST(Delete_Books, Delete_All) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput("delete");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(false, major_test_subject2.fail);
  EXPECT_EQ(3, major_test_subject2.type);
}

TEST(Update_Books, NormalUpdate) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput(
      "update "
      "/home/ibrahim/code/github/beemibrahim/"
      "Library-program/JsontestFiles/NormalUpdate.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(false, major_test_subject2.fail);
  EXPECT_EQ(8, major_test_subject2.type);
}

TEST(Update_Books, UpdateNon_ExisFile) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput("update "
                               "/home/ibrahim/code/github/beemibrahim/"
                               "Library-program/IDontExist.hpp");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(Update_Books, Update_NonJson_File) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput("update "
                               "/home/ibrahim/code/github/beemibrahim/"
                               "Library-program/Library.hpp");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(Update_Books, Update_Nonsense_File) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput("update "
                               "/home/ibrahim/code/github/beemibrahim/"
                               "Library-program/JsontestFiles/Nonsense.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(Update_Books, Update_WrongObj) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput(
      "update "
      "/home/ibrahim/code/github/beemibrahim/"
      "Library-program/JsontestFiles/Update_WrongObj.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(Update_Books, Update_WrongType) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput(
      "update "
      "/home/ibrahim/code/github/beemibrahim/"
      "Library-program/JsontestFiles/Update_WrongType.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(Update_Books, No_Letters_Author) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput(
      "update "
      "/home/ibrahim/code/github/beemibrahim/"
      "Library-program/JsontestFiles/Update_NoLetters_Author.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(Update_Books, Update_Pagesis_zero) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput(
      "update "
      "/home/ibrahim/code/github/beemibrahim/"
      "Library-program/JsontestFiles/update_Pageszero.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(Update_Books, Update_Emptyname) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput(
      "update "
      "/home/ibrahim/code/github/beemibrahim/"
      "Library-program/JsontestFiles/Update_Emptyname.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}

TEST(Update_Books, Update_EmptyAuthor) {
  UserInput major_test_subject1;
  major_test_subject1.GetInput(
      "update "
      "/home/ibrahim/code/github/beemibrahim/"
      "Library-program/JsontestFiles/Update_Emptyauthor.json");
  Command major_test_subject2 = major_test_subject1.ParseInput();
  EXPECT_EQ(true, major_test_subject2.fail);
}
