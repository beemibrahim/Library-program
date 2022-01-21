#include "Userinput.hpp"

Command UserInput::ParseInput() {
  Command command = Command();
  string input = this->input;
  vector<string> errors;
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
      errors.push_back("File doesnt exist");
    }
    // Is The File json ??
    if (sub.substr(sub.size() - 4) != "json") {
      errors.push_back("File isnt json");
    }
    // Check for errors
    if (errors.size() != 0) {
      throw errors;
    }
    // Converting file into string
    string raw_json = this->readFileIntoString(sub);

    // Is the Json Valid ??
    if (!json::accept(raw_json)) {
      errors.push_back("File isnt a valid json File");
      throw errors;
    }
    command.command = json::parse(raw_json);

    // Are there three entries (name,author,pages)
    if (command.command.size() != 3) {
      errors.push_back("File doesnt have tree entries");
      throw errors;
    }
    // The Entries are this
    if (!command.command.contains("name") ||
        !command.command.contains("author") ||
        !command.command.contains("pages")) {
      errors.push_back("File doesnt contain book propeties");
      throw errors;
    }
    // The Entries are of this type
    if (!command.command["name"].is_string() ||
        !command.command["author"].is_string() ||
        !command.command["pages"].is_number_integer()) {
      errors.push_back("Files book propeties are the wrong type");
      throw errors;
    }
    // Are The Pages Non Zero , is the name/author empty ??
    if (command.command["pages"] == 0 || command.command["name"] == "" ||
        command.command["author"] == "") {
      errors.push_back("Files book propeties for empty / page number is zero");
      throw errors;
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
      errors.push_back("The Author must at least have one letter to be valid");
      throw errors;
    }
    return command;
  }

  if (input == "delete") {
    command.type = 3;
    cout << "Are You Sure About This [Y/n]";
    getline(cin, input);
    cout << "\n\r";
    if (input == "Y") {
      return command;
    }
    if (input != "Y") {
      command.warning_log.push_back("Delete Aborted");
      return command;
    }
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
      errors.push_back("File doesnt exist");
    }
    // Is The File json ??
    if (sub.substr(sub.size() - 4) != "json") {
      errors.push_back("File isnt json");
    }
    // Check for errors
    if (errors.size() != 0) {
      throw errors;
    }

    // Converting file into string
    string raw_json = this->readFileIntoString(sub);

    // Is the Json Valid ??
    if (!json::accept(raw_json)) {
      errors.push_back("File isnt a valid json File");
      throw errors;
    }
    command.command = json::parse(raw_json);

    // Are there three entries (name,author,pages)
    if (command.command.size() != 3) {
      errors.push_back("File doesnt have tree entries");
      throw errors;
    }
    // The Entries are this
    if (!command.command.contains("name") ||
        !command.command.contains("author") ||
        !command.command.contains("pages")) {
      errors.push_back("File doesnt contain book propeties");
      return command;
    }
    // The Entries are of this type
    if (!command.command["name"].is_string() ||
        !command.command["author"].is_string() ||
        !command.command["pages"].is_number_integer()) {
      errors.push_back("Files book propeties are the wrong type");
      throw errors;
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
        errors.push_back("You must give an id of a book");
        throw errors;
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

      errors.push_back("File doesnt exist");
    }
    // Is The File json ??
    if (sub.substr(sub.size() - 4) != "json") {
      errors.push_back("File isnt json");
    }
    // Check for errors
    if (errors.size() != 0) {
      throw errors;
    }
    // Converting file into string
    string raw_json = this->readFileIntoString(sub);

    // Is the Json Valid ??
    if (!json::accept(raw_json)) {
      errors.push_back("File isnt a valid json File");
      throw errors;
    }
    command.command = json::parse(raw_json);

    // Are there three entries (name,author,pages)
    if (command.command.size() != 3) {
      errors.push_back("File doesnt have tree entries");
      throw errors;
    }
    // The Entries are this
    if (!command.command.contains("name") ||
        !command.command.contains("author") ||
        !command.command.contains("pages")) {
      errors.push_back("File doesnt contain book propeties");
      throw errors;
    }
    // The Entries are of this type
    if (!command.command["name"].is_string() ||
        !command.command["author"].is_string() ||
        !command.command["pages"].is_number_integer()) {
      errors.push_back("Files book propeties are the wrong type");
      throw errors;
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
        errors.push_back("You must give an id of a book");
        throw errors;
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

      errors.push_back("File doesnt exist");
    }
    // Is The File json ??
    if (sub.substr(sub.size() - 4) != "json") {
      errors.push_back("File isnt json");
    }
    // Check for errors
    if (errors.size() != 0) {
      throw errors;
    }
    // Converting file into string
    string raw_json = this->readFileIntoString(sub);

    // Is the Json Valid ??
    if (!json::accept(raw_json)) {
      errors.push_back("File isnt a valid json File");
      throw errors;
    }

    command.command = json::parse(raw_json);

    if (!command.command.contains("id") || command.command.size() < 2) {
      errors.push_back("Patch propeties not specified");
      throw errors;
    }

    if (!command.command["id"].is_number_integer()) {
      errors.push_back("Files book propeties are the wrong type");
      throw errors;
    }
    command.id = command.command["id"];
    if (!command.command.contains("name") &&
        !command.command.contains("author") &&
        !command.command.contains("pages")) {
      errors.push_back("Patch propeties not specified");
      throw errors;
    }

    int exsize = 1;
    if (command.command.contains("name")) {
      if (!command.command["name"].is_string()) {
        errors.push_back("Files book propeties are the wrong type");
        throw errors;
      }
      if (command.command["name"] == "") {
        errors.push_back("Book propeties are empty");
        throw errors;
      }
      exsize += 1;
    }
    if (command.command.contains("author")) {
      if (!command.command["author"].is_string()) {
        errors.push_back("Files book propeties are the wrong type");
        throw errors;
      }
      if (command.command["author"] == "") {
        errors.push_back("Book propeties are empty");
        throw errors;
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
        errors.push_back(
            "The Author must at least have one letter to be valid");
        throw errors;
      }

      exsize += 1;
    }
    if (command.command.contains("pages")) {
      if (!command.command["pages"].is_number_integer()) {
        errors.push_back("Files book propeties are the wrong type");
        throw errors;
      }
      if (command.command["pages"] <= 0) {
        errors.push_back("The number of pages are invalid");
        throw errors;
      }

      exsize += 1;
    }

    if (exsize == 4) {
      command.warning_log.push_back("Use The \"Update\" command instead");
    }
    if (command.command.size() != exsize) {
      errors.push_back("Patch propeties are invalid");
      throw errors;
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

      errors.push_back("File doesnt exist");
    }
    // Is The File json ??
    if (sub.substr(sub.size() - 4) != "json") {
      errors.push_back("File isnt json");
    }
    // Check for errors
    if (errors.size() != 0) {
      throw errors;
    }
    // Converting file into string
    string raw_json = this->readFileIntoString(sub);

    // Is the Json Valid ??
    if (!json::accept(raw_json)) {
      errors.push_back("File isnt a valid json File");
      throw errors;
    }

    command.command = json::parse(raw_json);

    // Are there four entries (name,author,pages,id)
    if (command.command.size() != 4) {
      errors.push_back("File doesnt have four entries");

      throw errors;
    }
    // The Entries are this
    if (!command.command.contains("name") ||
        !command.command.contains("author") ||
        !command.command.contains("pages") || !command.command.contains("id")) {
      errors.push_back("Update propeties not specified");

      throw errors;
    }
    // The Entries are of this type
    if (!command.command["name"].is_string() ||
        !command.command["author"].is_string() ||
        !command.command["pages"].is_number_integer() ||
        !command.command["id"].is_number_integer()) {
      errors.push_back("Files book propeties are the wrong type");

      throw errors;
    }
    command.id = command.command["id"];
    // Are The Pages Negative
    if (command.command["pages"] < 0) {
      errors.push_back("Pages are negative");
      throw errors;
    }
    if (command.command["pages"] == 0 || command.command["name"] == "" ||
        command.command["author"] == "") {
      errors.push_back("Book Propeties are empty");

      throw errors;
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
      errors.push_back("The Author must at least have one letter to be valid");

      throw errors;
    }
    return command;
  }
  errors.push_back("Command not found");
  throw errors;
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
