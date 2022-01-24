#include "LibraryApp.hpp"
/*
. Create

NormalCreate();
InvalidCreateNonFile();
NormalCreate_Non_Exisfile();
NormalCreate_Non_JsonFile();
NormalCreate_NonsenseJson();
InvalidCreate_WrongJsonObj();
InvalidCreate_WrongJsonType();
InvalidCreate_NotLettersinAtuhor();
InvalidCreate_Pagesiszero();
InvalidCreate_emptyname();
InvalidCreate_emptyauthor();
InvalidCreate_duplicate();




. Delete

. Find

. Update












*/

TEST(Create_Books, NormalCreate) {
  std::stringstream expected;
  // setting what it is expected to be
  expected << "\n             Log :             \n\r";
  expected << "-----------------------------------\n\r";
  expected << "Book Successfully Created\n\n\r";

  UserInput input;
  LibraryService services;
  input.GetInput("create JsontestFiles/testfile.json");
  Command command = input.ParseInput();
  std::stringstream reality = services.execute_command(command);
  EXPECT_EQ(expected.str(), reality.str());
}

TEST(Create_Books, Invalid_NoFile) {
  std::stringstream expected;
  std::stringstream reality;
  // setting what it is expected to be
  expected << "\n             Log :             \n\r";
  expected << "-----------------------------------\n\r";
  expected << ". Provide a file\n\r";
  expected << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n";
  UserInput input;
  LibraryService services;
  input.GetInput("create");
  try {
    Command command = input.ParseInput();
  } catch (vector<string> errors) {
    reality << "\n             Log :             \n\r";
    reality << "-----------------------------------\n\r";

    for (int i = 0; i < errors.size(); i++) {
      reality << ". ";
      reality << errors[i] << "\n\r";
    }
    reality << "Command Failed , read my REAMDE.md on github : "
               "https://github.com/beemibrahim/Library-program\n\n";
  }
  EXPECT_EQ(expected.str(), reality.str());
}

TEST(Create_Books, NonExisFile) {
  std::stringstream expected;
  std::stringstream reality;
  // setting what it is expected to be
  expected << "\n             Log :             \n\r";
  expected << "-----------------------------------\n\r";
  expected << ". File doesnt exist\n\r";
  expected << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n";
  UserInput input;
  LibraryService services;
  input.GetInput("create gulpup.json");
  try {
    Command command = input.ParseInput();
  } catch (vector<string> errors) {
    reality << "\n             Log :             \n\r";
    reality << "-----------------------------------\n\r";

    for (int i = 0; i < errors.size(); i++) {
      reality << ". ";
      reality << errors[i] << "\n\r";
    }
    reality << "Command Failed , read my REAMDE.md on github : "
               "https://github.com/beemibrahim/Library-program\n\n";
  }
  EXPECT_EQ(expected.str(), reality.str());
}

TEST(Create_Books, NonJsonFile) {
  std::stringstream expected;
  std::stringstream reality;
  // setting what it is expected to be
  expected << "\n             Log :             \n\r";
  expected << "-----------------------------------\n\r";
  expected << ". File isnt json\n\r";
  expected << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n";
  UserInput input;
  LibraryService services;
  input.GetInput("create Library.cpp");
  try {
    Command command = input.ParseInput();
  } catch (vector<string> errors) {
    reality << "\n             Log :             \n\r";
    reality << "-----------------------------------\n\r";

    for (int i = 0; i < errors.size(); i++) {
      reality << ". ";
      reality << errors[i] << "\n\r";
    }
    reality << "Command Failed , read my REAMDE.md on github : "
               "https://github.com/beemibrahim/Library-program\n\n";
  }
  EXPECT_EQ(expected.str(), reality.str());
}

TEST(Create_Books, NonSenseFile) {
  std::stringstream expected;
  std::stringstream reality;
  // setting what it is expected to be
  expected << "\n             Log :             \n\r";
  expected << "-----------------------------------\n\r";
  expected << ". File isnt a valid json File\n\r";
  expected << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n";
  UserInput input;
  LibraryService services;
  input.GetInput("create JsontestFiles/Nonsense.json");
  try {
    Command command = input.ParseInput();
  } catch (vector<string> errors) {
    reality << "\n             Log :             \n\r";
    reality << "-----------------------------------\n\r";

    for (int i = 0; i < errors.size(); i++) {
      reality << ". ";
      reality << errors[i] << "\n\r";
    }
    reality << "Command Failed , read my REAMDE.md on github : "
               "https://github.com/beemibrahim/Library-program\n\n";
  }
  EXPECT_EQ(expected.str(), reality.str());
}

TEST(Create_Books, WrongObj) {
  std::stringstream expected;
  std::stringstream reality;
  // setting what it is expected to be
  expected << "\n             Log :             \n\r";
  expected << "-----------------------------------\n\r";
  expected << ". File doesnt have three entries\n\r";
  expected << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n";
  UserInput input;
  LibraryService services;
  input.GetInput("create JsontestFiles/WrongObj.json");
  try {
    Command command = input.ParseInput();
  } catch (vector<string> errors) {
    reality << "\n             Log :             \n\r";
    reality << "-----------------------------------\n\r";

    for (int i = 0; i < errors.size(); i++) {
      reality << ". ";
      reality << errors[i] << "\n\r";
    }
    reality << "Command Failed , read my REAMDE.md on github : "
               "https://github.com/beemibrahim/Library-program\n\n";
  }
  EXPECT_EQ(expected.str(), reality.str());
}

TEST(Create_Books, WrongType) {
  std::stringstream expected;
  std::stringstream reality;
  // setting what it is expected to be
  expected << "\n             Log :             \n\r";
  expected << "-----------------------------------\n\r";
  expected << ". Files book propeties are the wrong type\n\r";
  expected << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n";
  UserInput input;
  LibraryService services;
  input.GetInput("create JsontestFiles/WrongType.json");
  try {
    Command command = input.ParseInput();
  } catch (vector<string> errors) {
    reality << "\n             Log :             \n\r";
    reality << "-----------------------------------\n\r";

    for (int i = 0; i < errors.size(); i++) {
      reality << ". ";
      reality << errors[i] << "\n\r";
    }
    reality << "Command Failed , read my REAMDE.md on github : "
               "https://github.com/beemibrahim/Library-program\n\n";
  }
  EXPECT_EQ(expected.str(), reality.str());
}

TEST(Create_Books, NoLetters_Author) {
  std::stringstream expected;
  std::stringstream reality;
  // setting what it is expected to be
  expected << "\n             Log :             \n\r";
  expected << "-----------------------------------\n\r";
  expected << ". The Author must at least have one letter to be valid\n\r";
  expected << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n";
  UserInput input;
  LibraryService services;
  input.GetInput("create JsontestFiles/NoLettersAuthor.json");
  try {
    Command command = input.ParseInput();
  } catch (vector<string> errors) {
    reality << "\n             Log :             \n\r";
    reality << "-----------------------------------\n\r";

    for (int i = 0; i < errors.size(); i++) {
      reality << ". ";
      reality << errors[i] << "\n\r";
    }
    reality << "Command Failed , read my REAMDE.md on github : "
               "https://github.com/beemibrahim/Library-program\n\n";
  }
  EXPECT_EQ(expected.str(), reality.str());
}

TEST(Create_Books, PagesisZero) {
  std::stringstream expected;
  std::stringstream reality;
  // setting what it is expected to be
  expected << "\n             Log :             \n\r";
  expected << "-----------------------------------\n\r";
  expected << ". Files book propeties for empty / page number is zero\n\r";
  expected << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n";
  UserInput input;
  LibraryService services;
  input.GetInput("create JsontestFiles/pagesiszero.json");
  try {
    Command command = input.ParseInput();
  } catch (vector<string> errors) {
    reality << "\n             Log :             \n\r";
    reality << "-----------------------------------\n\r";

    for (int i = 0; i < errors.size(); i++) {
      reality << ". ";
      reality << errors[i] << "\n\r";
    }
    reality << "Command Failed , read my REAMDE.md on github : "
               "https://github.com/beemibrahim/Library-program\n\n";
  }
  EXPECT_EQ(expected.str(), reality.str());
}

TEST(Create_Books, EmptyName) {
  std::stringstream expected;
  std::stringstream reality;
  // setting what it is expected to be
  expected << "\n             Log :             \n\r";
  expected << "-----------------------------------\n\r";
  expected << ". Files book propeties for empty / page number is zero\n\r";
  expected << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n";
  UserInput input;
  LibraryService services;
  input.GetInput("create JsontestFiles/emptyname.json");
  try {
    Command command = input.ParseInput();
  } catch (vector<string> errors) {
    reality << "\n             Log :             \n\r";
    reality << "-----------------------------------\n\r";

    for (int i = 0; i < errors.size(); i++) {
      reality << ". ";
      reality << errors[i] << "\n\r";
    }
    reality << "Command Failed , read my REAMDE.md on github : "
               "https://github.com/beemibrahim/Library-program\n\n";
  }
  EXPECT_EQ(expected.str(), reality.str());
}

TEST(Create_Books, EmptyAuthor) {
  std::stringstream expected;
  std::stringstream reality;
  // setting what it is expected to be
  expected << "\n             Log :             \n\r";
  expected << "-----------------------------------\n\r";
  expected << ". Files book propeties for empty / page number is zero\n\r";
  expected << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n";
  UserInput input;
  LibraryService services;
  input.GetInput("create JsontestFiles/emptyauthor.json");
  try {
    Command command = input.ParseInput();
  } catch (vector<string> errors) {
    reality << "\n             Log :             \n\r";
    reality << "-----------------------------------\n\r";

    for (int i = 0; i < errors.size(); i++) {
      reality << ". ";
      reality << errors[i] << "\n\r";
    }
    reality << "Command Failed , read my REAMDE.md on github : "
               "https://github.com/beemibrahim/Library-program\n\n";
  }
  EXPECT_EQ(expected.str(), reality.str());
}

TEST(Create_Books, Duplicate_Book) {
  std::stringstream expected;
  // setting what it is expected to be
  expected << "\n             Log :             \n\r";
  expected << "-----------------------------------\n\r";
  expected << ". Book is a duplicate\n\r";
  expected << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n\r";
  UserInput input;
  LibraryService services;
  Book first;
  first.name = "How";
  first.author = "Spunix";
  first.pages = 34;

  services.create_book(first);
  input.GetInput("create JsontestFiles/testfile.json");
  Command command = input.ParseInput();

  std::stringstream reality = services.execute_command(command);

  EXPECT_EQ(expected.str(), reality.str());
}
