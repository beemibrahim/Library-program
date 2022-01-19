#include "Userinput.hpp"

Command UserInput::ParseInput() {
  Command command = Command();
  string input = this->input;

  // Create implementation
  if (input[0] == 'c' && input[1] == 'r' && input[2] == 'e' &&
      input[3] == 'a' && input[4] == 't' && input[5] == 'e' &&
      input.substr(input.size() - 4) == "json") {
    command.type = 1;
    string sub = input.substr(6);
    fstream jsonfile;
    jsonfile.open(sub);

    // Does The File Exist
    if (jsonfile.fail()) {
      command.fail = true;

      command.error_log.push_back("File doesnt exist");
    }
    // Is The File json ??
    if (sub.substr(sub.size() - 4) != "json") {
      command.fail = true;
      command.error_log.push_back("File isnt json");
    }
    // Check for errors
    if (command.error_log.size() != 0) {
      return command;
    }
    // Converting file into string
    string raw_json = this->readFileIntoString(sub);

    // Is the Json Valid ??
    if (!json::accept(raw_json)) {
      command.fail = true;
      command.error_log.push_back("File isnt a valid json File");
      return command;
    }
    command.command = json::parse(raw_json);

    // Are there three entries (name,author,pages)
    if (command.command.size() != 3) {
      command.fail = true;
      command.error_log.push_back("File doesnt have tree entries");
      return command;
    }
    // The Entries are this
    if (!command.command.contains("name") ||
        !command.command.contains("author") ||
        !command.command.contains("pages")) {
      command.fail = true;
      command.error_log.push_back("File doesnt contain book propeties");
      return command;
    }
    // The Entries are of this type
    if (!command.command["name"].is_string() ||
        !command.command["author"].is_string() ||
        !command.command["pages"].is_number_integer()) {
      command.fail = true;
      command.error_log.push_back("Files book propeties are the wrong type");
      return command;
    }
    // Are The Pages Non Zero , is the name/author empty ??
    if (command.command["pages"] == 0 || command.command["name"] == "" ||
        command.command["author"] == "") {
      command.fail = true;
      command.error_log.push_back(
          "Files book propeties for empty / page number is zero");
      return command;
    }
    string author = command.command["author"];

    // Are there Letters In Author ??
    bool fail = true;
    for (int i = 0; i < author.size(); i++) {
      if ((author[i] > 96 && author[i] < 123) ||
          (author[i] > 64 && author[i] < 91)) {
        fail = false;
      }
    }
    if (fail == true) {
      command.fail = true;
      command.error_log.push_back(
          "The Author must at least have one letter to be valid");

      return command;
    }
    return command;
  }

  if (input == "delete") {
    command.type = 3;
    return command;
  }

  if (input[0] == 'd' && input[1] == 'e' && input[2] == 'l' &&
      input[3] == 'e' && input[4] == 't' && input[5] == 'e' &&
      input.substr(input.size() - 4) == "json") {
    command.type = 4;
    string sub = input.substr(6);
    fstream jsonfile;
    jsonfile.open(sub);

    // Does The File Exist
    if (jsonfile.fail()) {
      command.fail = true;
      command.error_log.push_back("File doesnt exist");
    }
    // Is The File json ??
    if (sub.substr(sub.size() - 4) != "json") {
      command.fail = true;
      command.error_log.push_back("File isnt json");
    }
    // Check for errors
    if (command.error_log.size() != 0) {
      return command;
    }

    // Converting file into string
    string raw_json = this->readFileIntoString(sub);

    // Is the Json Valid ??
    if (!json::accept(raw_json)) {
      command.fail = true;
      command.error_log.push_back("File isnt a valid json File");
      return command;
    }
    command.command = json::parse(raw_json);

    // Are there three entries (name,author,pages)
    if (command.command.size() != 3) {
      command.fail = true;
      command.error_log.push_back("File doesnt have tree entries");
      return command;
    }
    // The Entries are this
    if (!command.command.contains("name") ||
        !command.command.contains("author") ||
        !command.command.contains("pages")) {
      command.fail = true;
      command.error_log.push_back("File doesnt contain book propeties");
      return command;
    }
    // The Entries are of this type
    if (!command.command["name"].is_string() ||
        !command.command["author"].is_string() ||
        !command.command["pages"].is_number_integer()) {
      command.fail = true;
      command.error_log.push_back("Files book propeties are the wrong type");
      return command;
    }

    return command;
  }

  if (input[0] == 'd' && input[1] == 'e' && input[2] == 'l' &&
      input[3] == 'e' && input[4] == 't' && input[5] == 'e') {
    command.type = 2;
    string sub = input.substr(6);

    // Everything in "string sub" should be a digit :
    for (int i = 0; i < sub.size(); i++) {
      if (sub[i] < 48 || sub[i] > 57) {
        command.fail = true;
        command.error_log.push_back("You must give an id of a book");
        return command;
      }
    }
    command.id = stoi(sub);
    return command;
  }

  if (input == "find") {
    command.type = 6;
    return command;
  }

  if (input[0] == 'f' && input[1] == 'i' && input[2] == 'n' &&
      input[3] == 'd' && input.substr(input.size() - 4) == "json") {
    command.type = 7;
    string sub = input.substr(4);
    fstream jsonfile;
    jsonfile.open(sub);

    // Does The File Exist
    if (jsonfile.fail()) {
      command.fail = true;

      command.error_log.push_back("File doesnt exist");
    }
    // Is The File json ??
    if (sub.substr(sub.size() - 4) != "json") {
      command.fail = true;
      command.error_log.push_back("File isnt json");
    }
    // Check for errors
    if (command.error_log.size() != 0) {
      return command;
    }
    // Converting file into string
    string raw_json = this->readFileIntoString(sub);

    // Is the Json Valid ??
    if (!json::accept(raw_json)) {
      command.fail = true;
      command.error_log.push_back("File isnt a valid json File");
      return command;
    }
    command.command = json::parse(raw_json);

    // Are there three entries (name,author,pages)
    if (command.command.size() != 3) {
      command.fail = true;
      command.error_log.push_back("File doesnt have tree entries");
      return command;
    }
    // The Entries are this
    if (!command.command.contains("name") ||
        !command.command.contains("author") ||
        !command.command.contains("pages")) {
      command.fail = true;
      command.error_log.push_back("File doesnt contain book propeties");
      return command;
    }
    // The Entries are of this type
    if (!command.command["name"].is_string() ||
        !command.command["author"].is_string() ||
        !command.command["pages"].is_number_integer()) {
      command.fail = true;
      command.error_log.push_back("Files book propeties are the wrong type");
      return command;
    }
    if (command.command["name"] == 0 && command.command["author"] == "" &&
        command.command["pages"] == "") {
      command.warning_log.push_back(
          "You Should use the \"find\" command to list everything");
    }
    return command;
  }

  if (input[0] == 'f' && input[1] == 'i' && input[2] == 'n' &&
      input[3] == 'd') {
    command.type = 5;
    string sub = input.substr(4);

    // Everything in "string sub" should be a digit :
    for (int i = 0; i < sub.size(); i++) {
      if (sub[i] < 48 || sub[i] > 57) {
        command.fail = true;
        command.error_log.push_back("You must give an id of a book");

        return command;
      }
    }
    command.id = stoi(sub);
    return command;
  }

  if (input[0] == 'p' && input[1] == 'a' && input[2] == 't' &&
      input[3] == 'c' && input[4] == 'h' &&
      input.substr(input.size() - 4) == "json") {
    command.type = 9;
    string sub = input.substr(6);
    fstream jsonfile;
    jsonfile.open(sub);

    // Does The File Exist
    if (jsonfile.fail()) {
      command.fail = true;

      command.error_log.push_back("File doesnt exist");
    }
    // Is The File json ??
    if (sub.substr(sub.size() - 4) != "json") {
      command.fail = true;
      command.error_log.push_back("File isnt json");
    }
    // Check for errors
    if (command.error_log.size() != 0) {
      return command;
    }
    // Converting file into string
    string raw_json = this->readFileIntoString(sub);

    // Is the Json Valid ??
    if (!json::accept(raw_json)) {
      command.fail = true;
      command.error_log.push_back("File isnt a valid json File");
      return command;
    }

    command.command = json::parse(raw_json);

    if (!command.command.contains("id") || command.command.size() < 2) {
      command.error_log.push_back("Patch propeties not specified");
      command.fail = true;
      return command;
    }

    if (!command.command["id"].is_number_integer()) {
      command.fail = true;
      command.error_log.push_back("Files book propeties are the wrong type");
      return command;
    }
    if (!command.command.contains("name") &&
        !command.command.contains("author") &&
        !command.command.contains("pages")) {
      command.error_log.push_back("Patch propeties not specified");
      command.fail = true;
      return command;
    }

    int exsize = 1;
    if (command.command.contains("name")) {
      if (!command.command["name"].is_string()) {
        command.fail = true;
        command.error_log.push_back("Files book propeties are the wrong type");
        return command;
      }
      if (command.command["name"] == "") {
        command.fail = true;
        command.error_log.push_back("Book propeties are empty");
        return command;
      }
      exsize += 1;
    }
    if (command.command.contains("author")) {
      if (!command.command["author"].is_string()) {
        command.fail = true;
        command.error_log.push_back("Files book propeties are the wrong type");
        return command;
      }
      if (command.command["author"] == "") {
        command.fail = true;
        command.error_log.push_back("Book propeties are empty");
        return command;
      }

      string author = command.command["author"];
      // Are there Letters In Author ??
      bool fail = true;
      for (int i = 0; i < author.size(); i++) {
        if ((author[i] > 96 && author[i] < 123) ||
            (author[i] > 64 && author[i] < 91)) {
          fail = false;
        }
      }
      if (fail == true) {
        command.fail = true;
        command.error_log.push_back(
            "The Author must at least have one letter to be valid");
        return command;
      }

      exsize += 1;
    }
    if (command.command.contains("pages")) {
      if (!command.command["pages"].is_number_integer()) {
        command.fail = true;
        command.error_log.push_back("Files book propeties are the wrong type");
        return command;
      }
      if (command.command["pages"] <= 0) {
        command.fail = true;
        command.error_log.push_back("The number of pages are invalid");
        return command;
      }

      exsize += 1;
    }

    if (exsize == 4) {
      command.warning_log.push_back("Use The \"Update\" command instead");
    }
    if (command.command.size() != exsize) {
      command.error_log.push_back("Patch propeties are invalid");
      command.fail = true;
      return command;
    }
    return command;
  }
  if (input[0] == 'u' && input[1] == 'p' && input[2] == 'd' &&
      input[3] == 'a' && input[4] == 't' && input[5] == 'e' &&
      input.substr(input.size() - 4) == "json") {
    command.type = 8;
    string sub = input.substr(6);
    fstream jsonfile;
    jsonfile.open(sub);

    // Does The File Exist
    if (jsonfile.fail()) {
      command.fail = true;

      command.error_log.push_back("File doesnt exist");
    }
    // Is The File json ??
    if (sub.substr(sub.size() - 4) != "json") {
      command.fail = true;
      command.error_log.push_back("File isnt json");
    }
    // Check for errors
    if (command.error_log.size() != 0) {
      return command;
    }
    // Converting file into string
    string raw_json = this->readFileIntoString(sub);

    // Is the Json Valid ??
    if (!json::accept(raw_json)) {
      command.fail = true;
      command.error_log.push_back("File isnt a valid json File");
      return command;
    }

    command.command = json::parse(raw_json);

    // Are there four entries (name,author,pages,id)
    if (command.command.size() != 4) {
      command.fail = true;
      command.error_log.push_back("File doesnt have four entries");

      return command;
    }
    // The Entries are this
    if (!command.command.contains("name") ||
        !command.command.contains("author") ||
        !command.command.contains("pages") || !command.command.contains("id")) {
      command.fail = true;
      command.error_log.push_back("Update propeties not specified");

      return command;
    }
    // The Entries are of this type
    if (!command.command["name"].is_string() ||
        !command.command["author"].is_string() ||
        !command.command["pages"].is_number_integer() ||
        !command.command["id"].is_number_integer()) {
      command.fail = true;
      command.error_log.push_back("Files book propeties are the wrong type");

      return command;
    }
    // Are The Pages Negative
    if (command.command["pages"] < 0) {
      command.error_log.push_back("Pages are negative");
      command.fail = true;
      return command;
    }
    if (command.command["pages"] == 0 || command.command["name"] == "" ||
        command.command["author"] == "") {
      command.fail = true;
      command.error_log.push_back("Book Propeties are empty");

      return command;
    }
    string author = command.command["author"];
    // Are there Letters In Author ??
    bool fail = true;
    for (int i = 0; i < author.size(); i++) {
      if ((author[i] > 96 && author[i] < 123) ||
          (author[i] > 64 && author[i] < 91)) {
        fail = false;
      }
    }
    if (fail == true) {
      command.fail = true;
      command.error_log.push_back(
          "The Author must at least have one letter to be valid");

      return command;
    }
    return command;
  }
  command.fail = true;
  return command;
}

void UserInput::GetInput(string testing) {
  if (testing == "") {
    cout << "Type your command : ";
    getline(cin, this->input);
    Remove_Spaces();
    return;
  }
  this->input = testing;
  Remove_Spaces();
}

void UserInput::Remove_Spaces() {
  string input = this->input;
  string newinput;
  for (int i = 0; i < input.size(); i++) {
    if (input[i] != ' ') {
      newinput.push_back(input[i]);
    }
  }
  this->input = newinput;
}

string UserInput::readFileIntoString(const string &path) {
  ifstream input_file(path);
  if (!input_file.is_open()) {
    cerr << "Could not open the file - '" << path << "'" << endl;
    exit(EXIT_FAILURE);
  }
  return string((std::istreambuf_iterator<char>(input_file)),
                std::istreambuf_iterator<char>());
}
