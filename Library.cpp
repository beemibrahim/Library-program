#include "Library.hpp"
#include <iostream>
#include <stdlib.h> // randomizer functions....
// 1  /create
// 3  /delete everything;
Command UserInput::GetInput(vector<book> books) {
  Command command;
  bool if_evry_zero = true;
  cout << "Type your command:";
  getline(cin, this->input_store);
  cout << endl;
  Remove_All_Spaces();
  string input = this->input_store;

  if (input == "c" || input == "create") {
    string pages;
    command.command_type = 2;
    cout << "Name:";
    getline(cin, command.name);
    cout << endl;
    cout << "Author:";
    getline(cin, command.author);
    cout << endl;
    cout << "pages:";
    getline(cin, pages);
    cout << endl;

    for (int i = 0; i < pages.size(); i++) {
      if (pages[i] < 47 || pages[i] > 58) {
        int chance = (rand() % 100);
        if (chance >= 0 && chance <= 10) {
          printf("A page is a number , so no letters should be here");
          printf("\n");
        }
        if (chance >= 11 && chance <= 20) {
          printf("NO LETTERS SHOULD BE OVER HERE");
          printf("\n");
        }
        if (chance >= 21 && chance <= 30) {
          printf("pages must be a number");
          printf("\n");
        }
        if (chance >= 31 && chance <= 40) {
          printf("letters in the page line is overrated >:(");
          printf("\n");
        }
        if (chance >= 41 && chance <= 50) {
          printf("yOuR PrObAbLy A rObOt FoR PuTtIng LeTtErS In PaGe");
          printf("\n");
        }
        if (chance >= 51 && chance <= 60) {
          printf("Invalid Page Number (there were letters....)");
          printf("\n");
        };
        if (chance >= 61 && chance <= 70) {
          printf("Recheck the 'page' and youll see a miskate");
          printf("\n");
        };
        if (chance >= 71 && chance <= 80) {
          printf("A page is a number of things , it shouldnt have letters");
          printf("\n");
        }
        if (chance >= 81 && chance <= 90) {
          printf(" every page digit must be over 47 and less then 58 :)");
          printf("\n");
        }
        if (chance >= 91 && chance <= 100) {
          printf("Invalid Page Number , recheck it plz");
          printf("\n");
        }
        command.worked = false;
        return command;
      }
      if (pages[i] > 48 && pages[i] < 58) {
        if_evry_zero = false;
      }
      if (if_evry_zero == true && i == pages.size() - 1 && pages[i] == '0') {
        int chance = (rand() % 100);
        if (chance >= 0 && chance <= 10) {
          printf("LOL how are gonna read this book with no pages");
          printf("\n");
        }
        if (chance >= 11 && chance <= 20) {
          printf("the pages were ripped :(");
          printf("\n");
        }
        if (chance >= 21 && chance <= 30) {
          printf("The Book is empty");
          printf("\n");
        }
        if (chance >= 31 && chance <= 40) {
          printf("The Page Number should be over then 0");
          printf("\n");
        }
        if (chance >= 41 && chance <= 50) {
          printf("I cant see no page");
          printf("\n");
        }
        if (chance >= 51 && chance <= 60) {
          printf("A book cant have zero pages lol");
          printf("\n");
        }
        if (chance >= 61 && chance <= 70) {
          printf("No one can read this , it has no page");
          printf("\n");
        }
        if (chance >= 71 && chance <= 80) {
          printf("You need to input a number in the page section");
          printf("\n");
        }
        if (chance >= 81 && chance <= 90) {
          printf("No PaGeS HeRe");
          printf("\n");
        }
        if (chance >= 91 && chance <= 100) {
          printf("Invalid Page Number , it should be higher then zero");
          printf("\n");
        }
        command.worked = false;
        return command;
      }
    }
    command.pages = stoi(pages);
    command.id = ++this->last_id;

  } else if (input == "f" || input == "find") {
    command.command_type = 3;
    command.worked = true;
    return command;
    ;
  } else if (input == "d" || input == "delete") {
    command.command_type = 5;
    command.worked = true;
    return command;
    ;
  } else if (input[0] == 'd') {
    command.command_type = 6;
    int i = 1;
    if (input[0] == 'd' && input[1] == 'e' && input[2] == 'l' &&
        input[3] == 'e' && input[4] == 't' && input[5] == 'e') {
      i = 6;
    }
    string id;
    for (; i < input.size(); i++) {
      if (input[i] < 48 || input[i] > 58) {
        int chance = (rand() % 50);
        if (chance >= 0 && chance <= 10) {
          printf("invalid id, try again");
          printf("\n");
        }
        if (chance >= 11 && chance <= 20) {
          printf("The Id isnt valid");
          printf("\n");
        }
        if (chance >= 21 && chance <= 30) {
          printf("That Book doesnt exist");
          printf("\n");
        }
        if (chance >= 31 && chance <= 40) {
          printf("You havent created a book with that id");
          printf("\n");
        }
        if (chance >= 41 && chance <= 50) {
          printf("there is no book with that id");
          printf("\n");
        }
        command.worked = false;
        return command;
      }
    }
    i--;
    id.push_back(input[i]);

    command.id = stoi(id);
    command.worked = true;
    return command;

  } else if (input == "update" || input == "u") {
    int chance = (rand() % 50);
    if (chance >= 0 && chance <= 10) {
      printf("Update need an Id");
      printf("\n");
    }
    if (chance >= 11 && chance <= 20) {
      printf("What are you updating ?");
      printf("\n");
    }
    if (chance >= 21 && chance <= 30) {
      printf("You cant update nothing");
      printf("\n");
    }
    if (chance >= 31 && chance <= 40) {
      printf("input the id of a book for update");
      printf("\n");
    }
    if (chance >= 41 && chance <= 50) {
      printf("Update need an ID to execute");
      printf("\n");
    }
    command.worked = false;
    return command;
  } else if (input[0] == 'u') {
    command.command_type = 4;
    int i = 1;
    if (input[0] == 'u' && input[1] == 'p' && input[2] == 'd' &&
        input[3] == 'a' && input[4] == 't' && input[5] == 'e') {
      i = 6;
    }
    string id;
    for (; i < input.size(); i++) {
      if (input[i] < 48 || input[i] > 58) {
        int chance = (rand() % 50);
        if (chance >= 0 && chance <= 10) {
          printf("invalid id, try again");
          printf("\n");
        }
        if (chance >= 11 && chance <= 20) {
          printf("The Id isnt valid");
          printf("\n");
        }
        if (chance >= 21 && chance <= 30) {
          printf("You typed letter in the id");
          printf("\n");
        }
        if (chance >= 31 && chance >= 40) {
          printf("Id's shouldnt have letters");
          printf("\n");
        }
        if (chance >= 41 && chance >= 50) {
          printf("Invalid id");
          printf("\n");
        }
        command.worked = false;
        return command;
      }
      id.push_back(input[i]);
    }
    if (books.size() == 0) {
      printf("You havent created any book yet");
      printf("\n");
      command.worked = false;
      return command;
    }

    command.id = stoi(id);
    string update_sec;
    cout << "what do you wanna update(you can have more then "
            "one)[name/n,author/a,page/p] :";
    getline(cin, update_sec);
    printf("\n");
    update_sec = this->SpaceRemover_for_update(update_sec);
    int var = 0;
    for (;;) {
      if (update_sec[var] == 'n') {
        if (command.name2 == true) {
          printf("I cant update two names");
          printf("\n");

          command.worked = false;
          return command;
        }
        command.name2 = true;

        if (var == update_sec.size() - 1) {
          command.worked = true;
          goto NameInt;
        }
        if (update_sec[var] == 'n' && update_sec[var + 1] == 'a' &&
            update_sec[var + 2] == 'm' && update_sec[var + 3] == 'e') {
          var += 3;
        }
        if (var == update_sec.size() - 1) {
          command.worked = true;
          goto NameInt;
        }
        var += 1;
        if (update_sec[var] != ',') {
          printf("You forgot a comma");
          printf("\n");

          command.worked = false;
          return command;
        }
        ++var;
        continue;
      }

      if (update_sec[var] == 'a') {
        if (command.author2 == true) {
          printf("I cant update two authors");
          printf("\n");

          command.worked = false;
          return command;
        }
        command.author2 = true;
        if (var == update_sec.size() - 1) {
          command.worked = true;
          goto NameInt;
        }

        if (update_sec[var] == 'a' && update_sec[var + 1] == 'u' &&
            update_sec[var + 2] == 't' && update_sec[var + 3] == 'h' &&
            update_sec[var + 4] == 'o' && update_sec[var + 5] == 'r') {
          var += 5;
        }
        if (var == update_sec.size() - 1) {
          command.worked = true;
          goto NameInt;
        }
        var += 1;
        if (update_sec[var] != ',') {
          printf("You forgot a comma");
          printf("\n");

          command.worked = false;
          return command;
        }
        ++var;
        continue;
      }
      if (update_sec[var] == 'p') {
        if (command.pages2 == true) {
          printf("I cant update two pages");
          printf("\n");
          command.worked = false;
          return command;
        }
        command.pages2 = true;
        if (var == update_sec.size() - 1) {
          command.worked = true;
          goto NameInt;
        }
        if (update_sec[var] == 'p' && update_sec[var + 1] == 'a' &&
            update_sec[var + 2] == 'g' && update_sec[var + 3] == 'e') {
          var += 3;
        }
        if (var == update_sec.size() - 1) {
          command.worked = true;
          goto NameInt;
        }
        var += 1;
        if (update_sec[var] != ',') {
          printf("You forgot a comma");
          printf("\n");

          command.worked = false;
          return command;
        }
        ++var;
        continue;
      } else {
        printf("You didnt write a name , page or author");
        printf("\n");
        command.worked = false;
        return command;
      }
    }
  NameInt:
    string pages_ch;
    if (command.name2 == true) {
      cout << "Name :";
      getline(cin, command.name);
      printf("\n");
    }
    if (command.author2 == true) {
      cout << "Author :";
      getline(cin, command.author);
      printf("\n");
    }
    if (command.pages2 == true) {
      cout << "Page :";
      getline(cin, pages_ch);
      printf("\n");
    }
    for (int i = 0; i < pages_ch.size(); i++) {
      if (pages_ch[i] < 47 || pages_ch[i] > 58) {
        printf("Invalid Page Number");
        printf("\n");
        command.worked = false;
        return command;
      }
    }
    command.worked = true;
    return command;
  } else if (input[0] == 'f') {
    command.command_type = 1;
    int i = 1;
    if (books.size() == 0) {
      printf("Nothing has been created yet");
      printf("\n");
      command.worked = false;
      return command;
    }
    if (input[0] == 'f' && input[1] == 'i' && input[2] == 'n' &&
        input[3] == 'd') {
      i = 4;
    }
    string namef;
    string pagesf;
    int paged = 0;
    string authorf;
    string idb;
    int ida = 0;
    bool successful = false;
    bool breakin = false;
    // gon variables

    for (;;) {
      // if it enters the if below then it could possibly be the name or n
      if (input[i] == 'n') {
        if (command.name_gon == true) {
          printf("hey you cant type two names into a find,its impossible for "
                 "a book to have two names");
          printf("\n");

          command.worked = false;
          return command;
        }
        command.name_gon = true;
        i += 1;
        if (input[i - 1] == 'n' && input[i] == 'a' && input[i + 1] == 'm' &&
            input[i + 2] == 'e') {
          i += 3;
        }
        if (input[i] != ':') {
          // INVALID CHECKING
          printf("invalid find input you missed the ':'");
          printf("\n");
          command.worked = false;
          return command;
        }
        if (input[i + 1] != '"') {
          // INVALID CHECKING
          printf("you didnt put the double quotes propely");
          printf("\n");
          command.worked = false;
          return command;
        }
        i++;
        i++;
        bool cool = false;
        for (;; i++) {
          if (i == input.size()) {
            // INVALID CHECKING
            printf("you didnt put a ':' propely");
            printf("\n");
            cool = true;
            command.worked = false;
            return command;
          }
          if (input[i] == '"') {
            i++;
            if (i == input.size()) {
              // finised the whole loop now to find the books that match those
              // conditions
              breakin = true;
              break;
            }
            break;
          }
          command.name.push_back(input[i]);
        }
        if (breakin == true) {
          command.worked = true;
          return command;
          ;
        }
        if (cool == true) {
          continue;
        }
        // f name:"iber,author:"hello"
        // f name:"Peace"author:"Ibrahim Collins"
      }
      // There could possibly be an author in here or an a
      if (input[i] == 'a') {
        if (command.author_gon == true) {
          printf(
              "a single book cant have two authors well no collabs here lol");
          printf("\n");
          command.worked = false;
          return command;
        }
        command.author_gon = true;
        i += 1;
        if (input[i - 1] == 'a' && input[i - 1 + 1] == 'u' &&
            input[i - 1 + 2] == 't' && input[i - 1 + 3] == 'h' &&
            input[i - 1 + 4] == 'o' && input[i - 1 + 5] == 'r') {
          i += 5;
        }
        if (input[i] != ':') {
          printf("invalid find input you missed the ':'");
          printf("\n");
          command.worked = false;
          return command;
        }
        if (input[i + 1] != '"') {
          printf("you didnt put the double quotes propely");
          printf("\n");
          command.worked = false;
          return command;
        }
        i++;
        i++;

        for (;; i++) {
          if (i == input.size()) {
            printf("you didnt put a ':' propely");
            printf("\n");
            command.worked = false;
            return command;
          }
          if (input[i] == '"') {
            i++;
            if (i == input.size()) {
              breakin = true;
              break;
            }
            break;
          }
          command.author.push_back(input[i]);
        }
        if (breakin == true) {
          command.worked = true;
          return command;
          ;
        }
      }
      // there could be a page number
      if (input[i] == 'p') {
        if (command.page_gon == true) {
          printf("lol two page numbers thats no possible");
          printf("\n");
          command.worked = false;
          return command;
        }
        command.page_gon = true;
        i++;
        if (input[i - 1] == 'p' && input[i] == 'a' && input[i + 1] == 'g' &&
            input[i + 2] == 'e') {
          i += 3;
        }
        if (input[i] != ':') {
          if (input[i] != '"' && input[i] < 48 && input[i] > 57) {
            printf("you confused me lol its page not page with some extra "
                   "letters");
            printf("\n");
            command.worked = false;
            return command;
          }
          printf("you didnt put a ':' propely");
          printf("\n");
          command.worked = false;
          return command;
        }
        i++;
        if (input[i] != '"') {
          printf("you didnt put the double quotes propely");
          printf("\n");
          command.worked = false;
          return command;
        }
        i++;
        for (;; i++) {
          if (input[i] == input.size()) {
            printf("sooooooo you forgot to add the end double quote for pages");
            printf("\n");
            command.worked = false;
            return command;
          }
          if (input[i] == '"') {
            i++;
            if (i == input.size()) {
              command.pages = stoi(pagesf);
              breakin = true;
              break;
            }
            command.pages = stoi(pagesf);
            break;
          }
          if (input[i] < 48 || input[i] > 57) {
            printf("so now you enter the page number wrong, sorry but no "
                   "book is created with an invalid page number");
            printf("\n");
            command.worked = false;
            return command;
          }
          pagesf.push_back(input[i]);
        }
        if (breakin == true) {
          command.worked = true;
          return command;
          ;
        }
        command.pages = stoi(pagesf);
      }
      if (breakin == true) {
        command.worked = true;
        return command;
        ;
      }
      // checking to see if an id exists in the input var
      if (input[i] == 'i' && input[i + 1] == 'd') {
        if (command.id_gon == true) {
          printf("any book cant have two ids");
          printf("\n");
          command.worked = false;
          return command;
        }
        command.id_gon = true;
        i += 2;
        if (input[i] != ':') {
          printf("you didnt put a ':' propely");
          printf("\n");

          command.worked = false;
          return command;
        }
        i++;
        if (input[i] != '"') {
          printf("you didnt put the double quote propely");
          printf("\n");
          command.worked = false;
          return command;
        }
        i++;
        for (;; i++) {
          if (input[i] == input.size()) {
            printf("sooooooo you forgot to add the end double quote for id");
            printf("\n");
            command.worked = false;
            return command;
          }
          if (input[i] == '"') {
            i++;
            if (i == input.size()) {
              command.id = stoi(idb);
              breakin = true;
              break;
            }
            command.id = stoi(idb);
            break;
          }
          if (input[i] < 48 || input[i] > 57) {
            printf("so now you enter the id number wrong, sorry but no book "
                   "is created with an invalid id");
            printf("\n");
            command.worked = false;
            return command;
          }

          idb.push_back(input[i]);
        }

        if (breakin == true) {
          command.worked = true;
          return command;
          ;
        }
      } else {
        printf("you typed find then typed invalid stuff");
        printf("\n");
        command.worked = false;
        return command;
      }
    }
  } else {
    printf("this is not a command , try typing 'create'");
    printf("\n");
    command.worked = false;
    return command;
  }
  command.worked = true;
  return command;
}

void UserInput::Remove_All_Spaces() {
  string new_input;
  for (int i = 0; i < this->input_store.size(); i++) {
    if (this->input_store[i] == ' ') {
      continue;
    }
    new_input.push_back(this->input_store[i]);
  }
  this->input_store = new_input;
}

void Library::library_intro() {
  printf("Made my beem systems 2021");
  printf("\n");
  printf("Welcome to ibers library");
  printf("\n");
  printf("You have six commands : \n \n create/c (type name,pages,author and "
         "it gives you an ID) \n \n  find/f  \n or  \n  find/f (condition) "
         "(comma) (condition2) etc \n \n update/u (book name or ID) \n \n  "
         "delete/d(delete everything) \n or  \n  or delete/d (deleting books "
         "with matching conditions) \n example for create : c \n  example for "
         "find : f Title/t:iber,Author/a:ibahim,Pages/p:63 or id  \n Note that "
         "you must apply this /'find/' example with delete and update too");
  printf("\n");
  printf("\n");
}

void Library::create() {
  book booky;
  booky.id = this->command.id;
  booky.author = this->command.author;
  booky.pages = this->command.pages;
  booky.name = this->command.name;
  this->books.push_back(booky);
  printf("A book has now been created with an ID of %d", booky.id);
  printf("\n");
}

void Library::delete_everything() {
  vector<book> booky;
  string delete_y_or_n;

  if (this->books.size() == 0) {
    printf("You Have Nothing to delete (create a book first)");
    printf("\n");
    return;
  }
  cout << "ARE YOU SURE ABOUT DELETING EVERY SINGLE BOOK IN YOUR LIBRARY [y/n]";
  getline(cin, delete_y_or_n);
  if (delete_y_or_n.size() != 1) {
    printf("You can only type y or n (Failed)");
    printf("\n");
    return;
  }
  if (delete_y_or_n == "y") {
    this->books = booky;
    return;
  } else if (delete_y_or_n == "n") {
    printf("I will come back for you later....");
    printf("\n");
    return;
  } else {
    printf("Invalid you must type y or n");
    printf("\n");
    return;
  }
}

void Library::find_everything() {
  int a = 1;
  int number = 1;
  if (books.size() == 0) {
    printf("create a book first");
    printf("\n");
    return;
  }
  for (int i = 0; i < this->books.size(); i++) {
    printf("%d.", number);
    printf("\n \n");
    printf("Id : %d", this->books[i].id);
    printf("\n \n");
    printf("Name : %s", this->books[i].name.c_str());
    printf("\n \n");
    printf("Author : %s", this->books[i].author.c_str());
    printf("\n \n");
    printf("Pages : %d", this->books[i].pages);
    printf("\n \n");
    number++;
  }
}

void Library::delete_() {
  if (this->books.size() == 0) {
    printf("Nothing is created yet");
    printf("\n");
    return;
  }
  vector<book> booky;
  bool found;
  for (int i = 0; i < this->books.size(); i++) {
    if (this->books[i].id == this->command.id) {
      found = true;
      continue;
    }
    booky.push_back(books[i]);
  }
  if (found == false) {
    printf("that ID doesnt exist");
    printf("\n");
    return;
  }
  this->books = booky;
}
void Library::find() {
  bool valid = true;
  int number = 1;
  for (int i = 0; i < books.size(); i++) {
    if (command.name_gon == true) {
      if (command.name != books[i].name) {
        valid = false;
      } else {
        valid = true;
      }
    }
    if (command.author_gon == true) {
      if (command.author != books[i].author) {
        valid = false;
      } else {
        valid = true;
      }
    }
    if (command.page_gon == true) {
      if (command.pages != books[i].pages) {
        valid = false;
      } else {
        valid = true;
      }
    }
    if (command.id_gon == true) {
      if (command.id != books[i].id) {
        valid = false;
      } else {
        valid = true;
      }
    }
    if (valid == true) {
      printf("%d.", number);
      printf("\n \n");
      printf("Id : %d", books[i].id);
      printf("\n \n");
      printf("Name : %s", books[i].name.c_str());
      printf("\n \n");
      printf("Author : %s", books[i].author.c_str());
      printf("\n \n");
      printf("Pages : %d", books[i].pages);
      printf("\n \n");
      number++;
    }
    if (valid == false) {
      printf("There is no book matching those conditions");
      printf("\n \n");
    }
  }
}

void Library::update() {
  for (int i = 0; i < this->books.size(); i++) {
    if (this->command.id == this->books[i].id) {
      if (this->command.name2) {
        this->books[i].name = this->command.name;
      }
      if (this->command.author2) {
        this->books[i].author = this->command.author;
      }
      if (this->command.pages2) {
        this->books[i].pages = this->command.pages;
      }
      break;
    }
  }
}

string UserInput::SpaceRemover_for_update(string once) {
  string coolian;
  for (int i = 0; i < once.size(); i++) {
    if (once[i] != ' ') {
      coolian.push_back(once[i]);
    }
  }
  return coolian;
}
